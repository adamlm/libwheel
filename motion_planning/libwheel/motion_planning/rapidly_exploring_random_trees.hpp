#ifndef WHEEL_MOTION_RAPIDLY_EXPLORING_RANDOM_TREES_HPP
#define WHEEL_MOTION_RAPIDLY_EXPLORING_RANDOM_TREES_HPP

#include <algorithm>
#include <cmath>
#include <ranges>

#include <range/v3/view/iota.hpp>

#include <boost/geometry/algorithms/distance.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>

#include "libwheel/motion_planning/detail/boost_graph_extensions.hpp"
#include "libwheel/motion_planning/find_path.hpp"
#include "libwheel/motion_planning/is_within.hpp"
#include "libwheel/motion_planning/iteration_count.hpp"
#include "libwheel/motion_planning/sampling.hpp"
#include "libwheel/motion_planning/type_traits.hpp"

namespace wheel::motion_planning {

namespace detail {

auto get_nearest_vertex(auto const &point, boost_graph auto const &graph, auto const &distance_metric) {
    auto const [graph_cbegin, graph_cend] = boost::vertices(graph);
    return *std::ranges::min_element(graph_cbegin, graph_cend,
                                     [&graph = std::as_const(graph), &distance_metric = std::as_const(distance_metric),
                                      &point = std::as_const(point)](auto const &a, auto const &b) {
                                         return distance_metric(point, graph[a]) < distance_metric(point, graph[b]);
                                     });
}

auto get_nearest_vertex(auto const &point, boost_graph auto const &graph) {
    return get_nearest_vertex(point, graph,
                              [](auto const &a, auto const &b) { return boost::geometry::distance(a, b); });
}

template <typename Region, typename Tag>
class is_within_goal_checker : public boost::base_visitor<is_within_goal_checker<Region, Tag>> {
  public:
    using event_filter = Tag;

    explicit is_within_goal_checker(Region const &r) : region_{r} {}

    template <detail::boost_graph Graph>
    auto operator()(edge_descriptor_t<Graph> e, Graph const &g) const -> void {
        if (auto const v{boost::target(e, g)}; motion_planning::is_within(g[v], region_)) {
            throw detail::early_search_termination<Graph>("found goal region", v);
        }
    }

  private:
    Region region_;
};

template <typename Region, typename Tag>
auto check_is_within_goal(Region const &region, Tag /* tag */) noexcept -> is_within_goal_checker<Region, Tag> {
    return is_within_goal_checker<Region, Tag>{region};
}

template <detail::boost_graph Graph>
using VertexPath = std::vector<vertex_descriptor_t<Graph>>;

template <detail::boost_graph Graph, typename GoalRegion>
    requires std::same_as<vector_type_t<GoalRegion>, detail::vertex_bundle_t<Graph>>
[[nodiscard]]
auto find_path_in_graph(Graph const &graph, vertex_descriptor_t<Graph> const &source,
                        GoalRegion const &goal_region) noexcept -> std::optional<VertexPath<Graph>> {
    using PredecessorList = std::vector<std::optional<vertex_descriptor_t<Graph>>>;
    PredecessorList predecessors(boost::num_vertices(graph), std::nullopt);

    auto const predecessor_recorder{boost::record_predecessors(predecessors.data(), boost::on_tree_edge{})};
    auto const goal_checker{check_is_within_goal(goal_region, boost::on_tree_edge{})};
    auto const visitor{boost::make_bfs_visitor(std::make_pair(predecessor_recorder, goal_checker))};

    try {
        boost::breadth_first_search(graph, boost::vertex(source, graph), boost::visitor(visitor));
    } catch (detail::early_search_termination<Graph> const &result) {
        VertexPath<Graph> path;
        for (std::optional<vertex_descriptor_t<Graph>> predecessor{result.get_last_vertex()};
             predecessor != std::nullopt;) {
            path.push_back(predecessor.value());
            predecessor = predecessors.at(predecessor.value());
        }

        std::ranges::reverse(path);

        return path;
    }

    return std::nullopt;
}

struct MaxStepSize {
    double value{1U};
};

template <typename Point>
auto interpolate_between(Point const &source, Point const &target, MaxStepSize max_step_size) noexcept
    -> std::vector<Point> {

    auto const num_steps{std::ceil(boost::geometry::distance(source, target) / max_step_size.value)};
    auto const normalized_step_size{1.0 / num_steps};

    std::vector<Point> points;
    for (auto i{0.0}; i < 1.0; i += normalized_step_size) {
        auto scaled_source{source};
        boost::geometry::multiply_value(scaled_source, 1 - i);

        auto scaled_target{target};
        boost::geometry::multiply_value(scaled_target, i);

        boost::geometry::add_point(scaled_source, scaled_target);
        points.push_back(scaled_source);
    }

    return points;
}

template <std::ranges::input_range Range, typename UnaryPredicate>
constexpr auto find_stopping_point(Range &&r, UnaryPredicate should_stop) noexcept
    -> std::optional<std::ranges::range_value_t<Range>> {
    if (auto const one_past_stop{std::find_if(std::ranges::begin(r), std::ranges::end(r), should_stop)};
        one_past_stop != std::cbegin(r)) {
        return *std::prev(one_past_stop);
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

} // namespace wheel::motion_planning

#endif // WHEEL_MOTION_RAPIDLY_EXPLORING_RANDOM_TREES_HPP
