#ifndef WHEEL_MOTION_RAPIDLY_EXPLORING_RANDOM_TREES_HPP
#define WHEEL_MOTION_RAPIDLY_EXPLORING_RANDOM_TREES_HPP

#include <algorithm>
#include <cmath>

#include <range/v3/view/iota.hpp>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>

#include "libwheel/motion_planning/detail/boost_graph_extensions.hpp"
#include "libwheel/motion_planning/is_within.hpp"
#include "libwheel/motion_planning/iteration_count.hpp"
#include "libwheel/motion_planning/sampling.hpp"
#include "libwheel/motion_planning/type_traits.hpp"

namespace wheel::motion_planning {

namespace detail {

auto get_nearest_vertex(auto const &point, boost_graph auto const &graph) {
    (void)point;
    auto const [graph_cbegin, graph_cend] = boost::vertices(graph);
    return *std::ranges::min_element(graph_cbegin, graph_cend, [](auto const &, auto const &) { return true; });
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

} // namespace detail

struct default_rrt_visitor {
    auto on_sample(auto const & /* dummy */) const noexcept -> void {}
};

class RapidlyExploringRandomTrees {
  public:
    explicit RapidlyExploringRandomTrees(IterationCount const &max_iterations) : max_iterations_{max_iterations} {}

    template <typename Space>
    constexpr auto operator()(Space const &space, vector_type_t<Space> const &start, auto const &goal_region) const {
        return this->operator()(space, start, goal_region, default_rrt_visitor{});
    }

    template <typename Space, typename Visitor>
    constexpr auto operator()(Space const &space, vector_type_t<Space> const &start, auto const &goal_region,
                              Visitor const &visitor) const -> std::optional<std::vector<vector_type_t<Space>>> {
        if (!is_within(start, space)) {
            throw std::invalid_argument("start point not within space");
        }

        if (!is_within(goal_region, space)) {
            throw std::invalid_argument("goal region not within space");
        }

        UniformSampler<Space> sampler{space};

        boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, vector_type_t<Space>> tree;
        auto const source_vertex{boost::add_vertex(start, tree)};

        for ([[maybe_unused]] auto const batch : ranges::views::iota(0U, 100U)) {
            for ([[maybe_unused]] auto const iteration : ranges::views::iota(0U, max_iterations_.count)) {
                try {
                    auto const sample{sampler.sample_space()};

                    auto const nearest_vertex{detail::get_nearest_vertex(sample, tree)};
                    auto const sample_vertex{boost::add_vertex(sample, tree)};

                    visitor.on_sample(sample);

                    boost::add_edge(nearest_vertex, sample_vertex, tree);
                } catch (SamplingError const &) {
                    return std::nullopt;
                }
            }

            if (auto const vertex_path{detail::find_path_in_graph(tree, source_vertex, goal_region)}; vertex_path) {
                std::vector<vector_type_t<Space>> vector_path;
                for (auto const &vertex_descriptor : vertex_path.value()) {
                    vector_path.push_back(tree[vertex_descriptor]);
                }

                return vector_path;
            }
        }

        return std::nullopt;
    }

  private:
    IterationCount max_iterations_{0U};
};

} // namespace wheel::motion_planning

#endif // WHEEL_MOTION_RAPIDLY_EXPLORING_RANDOM_TREES_HPP
