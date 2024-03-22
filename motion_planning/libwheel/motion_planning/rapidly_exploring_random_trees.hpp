#ifndef WHEEL_MOTION_RAPIDLY_EXPLORING_RANDOM_TREES_HPP
#define WHEEL_MOTION_RAPIDLY_EXPLORING_RANDOM_TREES_HPP

#include <algorithm>
#include <cmath>
#include <ranges>

#include <boost/geometry/algorithms/distance.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <libwheel/boost_graph_extensions/exceptions.hpp>
#include <libwheel/boost_graph_extensions/type_traits.hpp>
#include <range/v3/view/iota.hpp>

#include "libwheel/motion_planning/detail/interpolate_between.hpp"
#include "libwheel/motion_planning/find_path.hpp"
#include "libwheel/motion_planning/is_within.hpp"
#include "libwheel/motion_planning/iteration_count.hpp"
#include "libwheel/motion_planning/sampling.hpp"
#include "libwheel/motion_planning/type_traits.hpp"

namespace wheel::motion_planning {

namespace detail {

auto get_nearest_vertex(auto const &point, wheel::boost_graph_extensions::boost_graph auto const &graph,
                        auto const &distance_metric) {
    auto const [graph_cbegin, graph_cend] = boost::vertices(graph);
    return *std::ranges::min_element(graph_cbegin, graph_cend,
                                     [&graph = std::as_const(graph), &distance_metric = std::as_const(distance_metric),
                                      &point = std::as_const(point)](auto const &a, auto const &b) {
                                         return distance_metric(point, graph[a]) < distance_metric(point, graph[b]);
                                     });
}

auto get_nearest_vertex(auto const &point, wheel::boost_graph_extensions::boost_graph auto const &graph) {
    return get_nearest_vertex(point, graph,
                              [](auto const &a, auto const &b) { return boost::geometry::distance(a, b); });
}

template <typename Region, typename Tag>
class is_within_goal_checker : public boost::base_visitor<is_within_goal_checker<Region, Tag>> {
  public:
    using event_filter = Tag;

    explicit is_within_goal_checker(Region const &r) : region_{r} {}

    template <wheel::boost_graph_extensions::boost_graph Graph>
    auto operator()(wheel::boost_graph_extensions::edge_descriptor_t<Graph> e, Graph const &g) const -> void {
        if (auto const v{boost::target(e, g)}; motion_planning::is_within(g[v], region_)) {
            throw wheel::boost_graph_extensions::early_search_termination<Graph>("found goal region", v);
        }
    }

  private:
    Region region_;
};

template <typename Region, typename Tag>
auto check_is_within_goal(Region const &region, Tag /* tag */) noexcept -> is_within_goal_checker<Region, Tag> {
    return is_within_goal_checker<Region, Tag>{region};
}

template <wheel::boost_graph_extensions::boost_graph Graph>
using VertexPath = std::vector<wheel::boost_graph_extensions::vertex_descriptor_t<Graph>>;

template <wheel::boost_graph_extensions::boost_graph Graph, typename GoalRegion>
    requires std::same_as<vector_type_t<GoalRegion>, wheel::boost_graph_extensions::vertex_bundle_t<Graph>>
[[nodiscard]]
auto find_path_in_graph(Graph const &graph, wheel::boost_graph_extensions::vertex_descriptor_t<Graph> const &source,
                        GoalRegion const &goal_region) noexcept -> std::optional<VertexPath<Graph>> {
    using PredecessorList = std::vector<std::optional<wheel::boost_graph_extensions::vertex_descriptor_t<Graph>>>;
    PredecessorList predecessors(boost::num_vertices(graph), std::nullopt);

    auto const predecessor_recorder{boost::record_predecessors(predecessors.data(), boost::on_tree_edge{})};
    auto const goal_checker{check_is_within_goal(goal_region, boost::on_tree_edge{})};
    auto const visitor{boost::make_bfs_visitor(std::make_pair(predecessor_recorder, goal_checker))};

    try {
        boost::breadth_first_search(graph, boost::vertex(source, graph), boost::visitor(visitor));
    } catch (wheel::boost_graph_extensions::early_search_termination<Graph> const &result) {
        VertexPath<Graph> path;
        for (std::optional<wheel::boost_graph_extensions::vertex_descriptor_t<Graph>> predecessor{
                 result.get_last_vertex()};
             predecessor != std::nullopt;) {
            path.push_back(predecessor.value());
            predecessor = predecessors.at(predecessor.value());
        }

        std::ranges::reverse(path);

        return path;
    }

    return std::nullopt;
}

template <wheel::boost_graph_extensions::boost_graph Graph, typename GoalRegion>
    requires std::same_as<vector_type_t<GoalRegion>, wheel::boost_graph_extensions::vertex_bundle_t<Graph>>
[[nodiscard]]
auto search_for_vertex_path(Graph const &graph, wheel::boost_graph_extensions::vertex_descriptor_t<Graph> const &source,
                            GoalRegion const &goal_region) noexcept -> std::optional<VertexPath<Graph>> {
    using PredecessorList = std::vector<std::optional<wheel::boost_graph_extensions::vertex_descriptor_t<Graph>>>;
    PredecessorList predecessors(boost::num_vertices(graph), std::nullopt);

    try {
        boost::breadth_first_search(graph, boost::vertex(source, graph),
                                    boost::visitor(boost::make_bfs_visitor(std::pair{
                                        boost::record_predecessors(predecessors.data(), boost::on_tree_edge{}),
                                        check_is_within_goal(goal_region, boost::on_tree_edge{})})));
    } catch (wheel::boost_graph_extensions::early_search_termination<Graph> const &result) {
        VertexPath<Graph> path;
        for (std::optional<wheel::boost_graph_extensions::vertex_descriptor_t<Graph>> predecessor{
                 result.get_last_vertex()};
             predecessor != std::nullopt;) {
            path.push_back(predecessor.value());
            predecessor = predecessors.at(predecessor.value());
        }

        std::ranges::reverse(path);

        return path;
    }

    return std::nullopt;
}

} // namespace detail

template <typename Value>
struct GraphNode {
    std::size_t index;
    Value value;
};

struct null_rrt_visitor {
    auto on_add_node(auto const & /* node */) const noexcept -> void {}
    auto on_add_edge(auto const & /* source */, auto const & /* target */) const noexcept -> void {}
};

struct SearchPeriod {
    std::size_t count;
};

struct MaxExpansions {
    std::size_t count;
};

class SimpleRrt {
  public:
    template <typename Space>
    using sampler_type = UniformSampler<Space>;

    constexpr explicit SimpleRrt(MaxExpansions const &max_expansions, SearchPeriod const &search_period)
        : max_expansions_{max_expansions}, search_period_{search_period} {}

    constexpr explicit SimpleRrt(MaxExpansions const &max_expansions) : max_expansions_{max_expansions} {}

    constexpr auto get_max_expansions() const noexcept -> MaxExpansions { return max_expansions_; }

    constexpr auto get_search_period() const noexcept -> SearchPeriod { return search_period_; }

    auto do_select_vertex(auto const &sample, auto const &tree) const noexcept {
        return detail::get_nearest_vertex(sample, tree);
    }

    template <typename Point>
    auto do_plan_local_path(Point const & /* source */, Point const &target) const -> std::vector<Point> {
        return {target};
    }

  private:
    MaxExpansions max_expansions_{0U};
    SearchPeriod search_period_{1U};
};

struct MaxDistance {
    double value;
};

class MaxDistanceRrt {
  public:
    template <typename Space>
    using sampler_type = UniformSampler<Space>;

    constexpr explicit MaxDistanceRrt(MaxExpansions max_expansions, SearchPeriod search_period,
                                      MaxDistance max_distance)
        : max_expansions_{max_expansions}, search_period_{search_period}, max_distance_{max_distance} {}

    constexpr explicit MaxDistanceRrt(MaxExpansions max_expansions) : max_expansions_{max_expansions} {}

    constexpr auto get_max_expansions() const noexcept -> MaxExpansions { return max_expansions_; }

    constexpr auto get_search_period() const noexcept -> SearchPeriod { return search_period_; }

    auto do_select_vertex(auto const &sample, auto const &tree) const noexcept {
        return detail::get_nearest_vertex(sample, tree);
    }

    template <typename Point>
    auto do_plan_local_path(Point const &source, Point const &target) const -> std::vector<Point> {
        auto const is_too_far_from_start = [&source = std::as_const(source), this](auto const &point) {
            return boost::geometry::distance(source, point) >= this->max_distance_.value;
        };

        auto const stopping_point{detail::find_stopping_point(
            detail::interpolate_between(source, target, detail::MaxStepSize{0.1}), is_too_far_from_start)};

        return {stopping_point.value()};
    }

  private:
    MaxExpansions max_expansions_{0U};
    SearchPeriod search_period_{1U};
    MaxDistance max_distance_{0.5};
};

template <typename Space>
class MaxDistanceHolesRrt {
  public:
    template <typename S = Space>
    using sampler_type = UniformSampler<S>;

    constexpr explicit MaxDistanceHolesRrt(MaxExpansions max_expansions, SearchPeriod search_period,
                                           MaxDistance max_distance, Space space)
        : max_expansions_{max_expansions}, search_period_{search_period}, max_distance_{max_distance}, space_{space} {}

    constexpr explicit MaxDistanceHolesRrt(MaxExpansions max_expansions, Space space)
        : max_expansions_{max_expansions}, space_{space} {}

    constexpr auto get_max_expansions() const noexcept -> MaxExpansions { return max_expansions_; }

    constexpr auto get_search_period() const noexcept -> SearchPeriod { return search_period_; }

    auto do_select_vertex(auto const &sample, auto const &tree) const noexcept {
        return detail::get_nearest_vertex(sample, tree);
    }

    template <typename Point>
    auto do_plan_local_path(Point const &source, Point const &target) const -> std::vector<Point> {
        auto const is_too_far_from_start = [&source = std::as_const(source), this](auto const &point) {
            return boost::geometry::distance(source, point) >= this->max_distance_.value ||
                   !is_within(point, this->space_);
        };

        auto const stopping_point{detail::find_stopping_point(
            detail::interpolate_between(source, target, detail::MaxStepSize{0.1}), is_too_far_from_start)};

        return {stopping_point.value()};
    }

  private:
    MaxExpansions max_expansions_{0U};
    SearchPeriod search_period_{1U};
    MaxDistance max_distance_{0.5};
    Space space_;
};

struct incremental_sample_and_search_algorithm_category {};

template <>
struct customization::search_algorithm_category_impl<SimpleRrt> {
    using type = incremental_sample_and_search_algorithm_category;
};

template <>
struct customization::search_algorithm_category_impl<MaxDistanceRrt> {
    using type = incremental_sample_and_search_algorithm_category;
};

template <typename Space>
struct customization::search_algorithm_category_impl<MaxDistanceHolesRrt<Space>> {
    using type = incremental_sample_and_search_algorithm_category;
};

template <>
struct customization::do_find_path<incremental_sample_and_search_algorithm_category> {
    template <typename Space, typename Strategy, typename Visitor>
    static auto _(Space const &space, vector_type_t<Space> const &start, auto const &goal_region,
                  Strategy const &strategy, Visitor const &visitor)
        -> std::optional<std::vector<vector_type_t<Space>>> {
        if (!is_within(start, space)) {
            throw std::invalid_argument("start point not within space");
        }

        if (!is_within(goal_region, space)) {
            throw std::invalid_argument("goal region not within space");
        }

        boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, vector_type_t<Space>> tree;
        auto const index_map{boost::get(boost::vertex_index, tree)};

        using Node = GraphNode<vector_type_t<Space>>;
        auto const source_vertex{boost::add_vertex(start, tree)};
        visitor.on_add_node(Node{index_map[source_vertex], tree[source_vertex]});

        typename Strategy::template sampler_type<Space> sampler{space};
        for (auto remaining_expansions{strategy.get_max_expansions().count}; remaining_expansions > 0;) {
            for (auto _{0U}; _ < std::min(strategy.get_search_period().count, remaining_expansions);
                 ++_, --remaining_expansions) {
                auto const sample{sampler.sample_space()};
                auto const selected_vertex{strategy.do_select_vertex(sample, tree)};
                auto const local_path{strategy.do_plan_local_path(tree[selected_vertex], sample)};

                auto const stopping_vertex{boost::add_vertex(*std::crbegin(local_path), tree)};
                visitor.on_add_node(Node{index_map[stopping_vertex], tree[stopping_vertex]});

                boost::add_edge(selected_vertex, stopping_vertex, tree);
                visitor.on_add_edge(Node{index_map[selected_vertex], tree[selected_vertex]},
                                    Node{index_map[stopping_vertex], tree[stopping_vertex]});
            }

            if (auto const vertex_path{detail::find_path_in_graph(tree, source_vertex, goal_region)}; vertex_path) {
                std::vector<vector_type_t<Space>> vector_path;
                for (auto const &vertex_descriptor : vertex_path.value()) {
                    vector_path.push_back(tree[vertex_descriptor]);
                }

                return vector_path;
            }
        }

        throw std::runtime_error("exceeded maximum number of expansions");
    }
};

namespace detail {

template <typename Graph>
auto make_point_path(auto const &vertex_path, Graph const &graph) {
    std::vector<wheel::boost_graph_extensions::vertex_bundle_t<Graph>> point_path;

    for (auto const &vertex_descriptor : vertex_path) {
        point_path.push_back(graph[vertex_descriptor]);
    }

    return point_path;
}

} // namespace detail

struct ExpansionsPerSearch {
    int value;
};

auto search_rrt(auto const &source, auto const &target, auto sampler, auto const &vertex_selector,
                auto const &local_planner, MaxExpansions max_expansions, ExpansionsPerSearch search_period,
                auto visitor) -> std::optional<std::vector<std::remove_cvref_t<decltype(source)>>> {

    // check for valid start and goal regions

    boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, std::remove_cvref_t<decltype(source)>> tree;
    auto const index_map{boost::get(boost::vertex_index, tree)};
    auto const source_vertex{boost::add_vertex(source, tree)};

    for (auto const &expansion_count : ranges::views::iota(0U, max_expansions.count)) {
        using Node = GraphNode<std::remove_cvref_t<decltype(source)>>;

        auto const sample{sampler.sample_space()};
        auto const selected_vertex{vertex_selector(tree, sample)};
        visitor.on_add_node(Node{index_map[source_vertex], tree[source_vertex]});

        auto const local_path{local_planner(tree[selected_vertex], sample)};
        auto const stopping_vertex{boost::add_vertex(local_path.back(), tree)};
        visitor.on_add_node(Node{index_map[stopping_vertex], tree[stopping_vertex]});

        boost::add_edge(selected_vertex, stopping_vertex, tree);
        visitor.on_add_edge(Node{index_map[selected_vertex], tree[selected_vertex]},
                            Node{index_map[stopping_vertex], tree[stopping_vertex]});

        if (static_cast<int>(expansion_count) % search_period.value == 0) {
            continue;
        }

        if (auto const vertex_path{detail::search_for_vertex_path(tree, source_vertex, target)}) {
            return detail::make_point_path(vertex_path.value(), tree);
        }
    }

    return std::nullopt;
}

} // namespace wheel::motion_planning

#endif // WHEEL_MOTION_RAPIDLY_EXPLORING_RANDOM_TREES_HPP
