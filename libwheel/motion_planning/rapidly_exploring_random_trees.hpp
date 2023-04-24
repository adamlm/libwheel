#ifndef WHEEL_MOTION_RAPIDLY_EXPLORING_RANDOM_TREES_HPP
#define WHEEL_MOTION_RAPIDLY_EXPLORING_RANDOM_TREES_HPP

#include <algorithm>
#include <cmath>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>

namespace wheel {

namespace detail {

template <typename GraphType, typename VectorType>
auto nearestElementTo(const GraphType &graph, const VectorType &target) -> typename GraphType::vertex_descriptor {
    if (boost::num_vertices(graph) == 1) {
        return *boost::vertices(graph).first;
    }

    typename GraphType::vertex_descriptor nearest_vertex;
    auto nearest_distance{std::numeric_limits<double>::max()};

    for (auto [it, end] = boost::vertices(graph); it < end - 1; ++it) {
        const auto distance{VectorType::distance(graph[*it].config, target)};
        if (distance < nearest_distance) {
            nearest_vertex = *it;
            nearest_distance = distance;
        }
    }

    return nearest_vertex;
}

template <typename GraphType, typename SamplerType>
auto expandTree(GraphType &graph, SamplerType &sampler, std::size_t num_samples) -> void {
    for (auto i{0}; i < num_samples; ++i) {
        const auto sampled_config = sampler.nextSample();

        auto nearest_vertex = nearestElementTo(graph, sampled_config);
        const auto configs = SamplerType::VectorType::interpolate(graph[nearest_vertex].config, sampled_config, 100);

        for (const auto config : configs) {
            const auto vertex = boost::add_vertex(typename boost::vertex_bundle_type<GraphType>::type{config}, graph);
            boost::add_edge(nearest_vertex, vertex, graph);

            // The target vertex from the previous iteration becomes the source for the next one
            nearest_vertex = vertex;
        }
    }
}

template <typename GraphType, typename VectorType>
auto pathExists(const GraphType &graph, const VectorType &target) -> bool {
    double min_dist = std::numeric_limits<double>::max();

    for (auto [vertex, end] = boost::vertices(graph); vertex != end; ++vertex) {
        if (const auto dist = VectorType::distance(graph[*vertex].config, target); dist < 1.0) {
            return true;
        } else {
            min_dist = std::min(min_dist, dist);
        }
    }

    return false;
}

template <typename GraphType, typename VertexType>
auto findPath(const GraphType &graph, const VertexType &source, const VertexType &target) -> std::optional<std::vector<VertexType>> {
    std::vector<VertexType> predecessors(boost::num_vertices(graph), std::numeric_limits<VertexType>::max());
    predecessors[source] = source;

    auto property_map =
        boost::make_iterator_property_map(std::begin(predecessors), boost::get(boost::vertex_index, graph));
    auto visitor = boost::make_bfs_visitor(boost::record_predecessors(property_map, boost::on_tree_edge{}));

    boost::breadth_first_search(graph, boost::vertex(source, graph), boost::visitor(visitor));

    auto predecessor_index = target;
    std::vector<VertexType> path{target};

    while (predecessors[predecessor_index] != predecessor_index) {
        if (predecessor_index == std::numeric_limits<VertexType>::max()) {
            return std::nullopt;
        }

        path.push_back(predecessors[predecessor_index]);
        predecessor_index = predecessors[predecessor_index];
    }

    std::ranges::reverse(path);

    return path;
}

} // namespace detail

template <typename SamplerType>
auto findRrtPath(SamplerType &sampler, const typename SamplerType::VectorType &source, const typename SamplerType::VectorType target)
    -> std::optional<typename SamplerType::SpaceType::PathType> {

    struct VertexProperties { typename SamplerType::VectorType config; };

    using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, VertexProperties>;
    using Vertex = typename Graph::vertex_descriptor;
    using Edge = typename Graph::edge_descriptor;

    Graph graph;
    const auto source_vertex = boost::add_vertex(VertexProperties{source}, graph);

    while (true) {
        detail::expandTree(graph, sampler, 100);

        if (detail::pathExists(graph, target)) {
            const auto nearest_vertex = detail::nearestElementTo(graph, target);
            const auto target_vertex = boost::add_vertex(VertexProperties{target}, graph);

            boost::add_edge(target_vertex, nearest_vertex, graph);

            const auto vertices = detail::findPath(graph, source_vertex, target_vertex);
            if (vertices) {
                std::vector<R2Vector> path;
                path.reserve(std::size(vertices.value()));
                std::ranges::transform(vertices.value(), std::back_inserter(path),
                                       [&graph](const auto &vertex) { return graph[vertex].config; });

                return path;
            }

            return std::nullopt;
        }
    }
}

} // namespace wheel

#endif // WHEEL_MOTION_RAPIDLY_EXPLORING_RANDOM_TREES_HPP
