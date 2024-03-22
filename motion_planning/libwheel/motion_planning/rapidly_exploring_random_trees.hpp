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
#include "libwheel/motion_planning/param_types.hpp"
#include "libwheel/motion_planning/sampling.hpp"
#include "libwheel/motion_planning/type_traits.hpp"

namespace wheel::motion_planning {

namespace detail {

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
