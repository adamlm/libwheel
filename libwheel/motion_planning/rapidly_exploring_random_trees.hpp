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

    typename GraphType::vertex_descriptor nearest_vertex{0U};
    auto nearest_distance{std::numeric_limits<double>::max()};

    for (auto [it, end] = boost::vertices(graph); it < end - 1; ++it) {
        using namespace wheel;
        const auto distance{euclidean_distance(graph[*it].config, target)};
        if (distance < nearest_distance) {
            nearest_vertex = *it;
            nearest_distance = distance;
        }
    }

    return nearest_vertex;
}

template <typename GraphType, typename SamplerType>
auto expandTree(GraphType &graph, SamplerType &sampler, std::size_t num_samples) -> void {
    for (auto i{0U}; i < num_samples; ++i) {
        const auto sampled_config = sampler.next_sample();

        auto nearest_vertex = nearestElementTo(graph, sampled_config);
        using namespace wheel;
        const auto configs = interpolate(graph[nearest_vertex].config, sampled_config, 100);

        for (const auto &config : configs) {
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
        using namespace wheel;
        if (const auto dist = euclidean_distance(graph[*vertex].config, target); dist < 1.0) {
            return true;
        } else {
            min_dist = std::min(min_dist, dist);
        }
    }

    return false;
}

template <typename GraphType, typename VertexType>
auto findPath(const GraphType &graph, const VertexType &source, const VertexType &target)
    -> std::optional<std::vector<VertexType>> {
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
auto findRrtPath(SamplerType &sampler, const typename SamplerType::vector_type &source,
                 const typename SamplerType::vector_type target, std::size_t max_samples = 1000U)
    -> std::optional<typename SamplerType::space_type::PathType> {

    struct VertexProperties {
        typename SamplerType::vector_type config;
    };

    using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, VertexProperties>;

    Graph graph;
    const auto source_vertex = boost::add_vertex(VertexProperties{source}, graph);

    std::size_t num_samples{0U};
    while (num_samples < max_samples) {
        detail::expandTree(graph, sampler, 100);
        num_samples += 100U;

        if (detail::pathExists(graph, target)) {
            const auto nearest_vertex = detail::nearestElementTo(graph, target);
            const auto target_vertex = boost::add_vertex(VertexProperties{target}, graph);

            boost::add_edge(target_vertex, nearest_vertex, graph);

            const auto vertices = detail::findPath(graph, source_vertex, target_vertex);
            if (vertices) {
                typename SamplerType::space_type::PathType path;
                path.reserve(std::size(vertices.value()));
                std::ranges::transform(vertices.value(), std::back_inserter(path),
                                       [&graph](const auto &vertex) { return graph[vertex].config; });

                return path;
            }

            return std::nullopt;
        }
    }

    return std::nullopt;
}

} // namespace wheel

#endif // WHEEL_MOTION_RAPIDLY_EXPLORING_RANDOM_TREES_HPP
