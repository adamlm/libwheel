#ifndef WHEEL_MOTION_RAPIDLY_EXPLORING_RANDOM_TREES_HPP
#define WHEEL_MOTION_RAPIDLY_EXPLORING_RANDOM_TREES_HPP

#include <algorithm>
#include <cmath>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>

#include "libwheel/motion_planning/sampler.hpp"

namespace wheel {

template <typename VectorType>
struct EuclideanDistance {
    static auto distance(const VectorType & /* a */, const VectorType & /* b */) -> double;
};

template <typename VectorType>
struct Interpolator {
    static auto interpolate(const VectorType & /* start */, const VectorType & /* stop */, std::size_t /* count */)
        -> std::vector<VectorType>;
};

namespace detail {

template <typename GraphType, typename VectorType>
auto nearest_vertex_to(const GraphType &graph, const VectorType &target) -> typename GraphType::vertex_descriptor {
    if (boost::num_vertices(graph) == 1) {
        return *boost::vertices(graph).first;
    }

    typename GraphType::vertex_descriptor nearest_vertex{0U};
    auto nearest_distance{std::numeric_limits<double>::max()};

    for (auto [it, end] = boost::vertices(graph); it < end - 1; ++it) {
        // using wheel::euclidean_distance;
        const auto distance{EuclideanDistance<VectorType>::distance(graph[*it].config, target)};
        if (distance < nearest_distance) {
            nearest_vertex = *it;
            nearest_distance = distance;
        }
    }

    return nearest_vertex;
}

template <typename TreeType, typename SamplerType>
auto expand_tree(TreeType &tree, SamplerType &sampler, std::size_t num_samples) -> void {
    for (auto i{0U}; i < num_samples; ++i) {
        const auto sampled_config = sampler.next_sample();

        auto nearest_vertex = nearest_vertex_to(tree, sampled_config);
        // using wheel::interpolate;
        const auto configs = Interpolator<typename SamplerType::sample_type>::interpolate(tree[nearest_vertex].config,
                                                                                          sampled_config, 100);

        for (const auto &config : configs) {
            const auto vertex = boost::add_vertex(typename boost::vertex_bundle_type<TreeType>::type{config}, tree);
            boost::add_edge(nearest_vertex, vertex, tree);

            // The target vertex from the previous iteration becomes the source for the next one
            nearest_vertex = vertex;
        }
    }
}

template <typename GraphType, typename VectorType>
auto path_exists(const GraphType &graph, const VectorType &target) -> bool {
    double min_dist = std::numeric_limits<double>::max();

    for (auto [vertex, end] = boost::vertices(graph); vertex != end; ++vertex) {
        using namespace wheel;
        if (const auto dist = EuclideanDistance<VectorType>::distance(graph[*vertex].config, target); dist < 1.0) {
            return true;
        } else {
            min_dist = std::min(min_dist, dist);
        }
    }

    return false;
}

template <typename GraphType>
auto find_path_in_graph(const GraphType &graph, const typename GraphType::vertex_descriptor &source,
                        const typename GraphType::vertex_descriptor &target)
    -> std::optional<std::vector<typename GraphType::vertex_descriptor>> {
    std::vector<typename GraphType::vertex_descriptor> predecessors(
        boost::num_vertices(graph), std::numeric_limits<typename GraphType::vertex_descriptor>::max());
    predecessors[source] = source;

    auto property_map =
        boost::make_iterator_property_map(std::begin(predecessors), boost::get(boost::vertex_index, graph));
    auto visitor = boost::make_bfs_visitor(boost::record_predecessors(property_map, boost::on_tree_edge{}));

    boost::breadth_first_search(graph, boost::vertex(source, graph), boost::visitor(visitor));

    auto predecessor_index = target;
    std::vector<typename GraphType::vertex_descriptor> path{target};

    while (predecessors[predecessor_index] != predecessor_index) {
        if (predecessor_index == std::numeric_limits<typename GraphType::vertex_descriptor>::max()) {
            return std::nullopt;
        }

        path.push_back(predecessors[predecessor_index]);
        predecessor_index = predecessors[predecessor_index];
    }

    std::ranges::reverse(path);

    return path;
}

} // namespace detail

template <typename SpaceType>
auto find_path_rrt(const SpaceType &space, const typename SpaceType::vector_type &source,
                   const typename SpaceType::vector_type &target, std::size_t max_samples = 1000U)
    -> std::optional<std::vector<typename SpaceType::vector_type>> {

    struct VertexProperties {
        typename SpaceType::vector_type config;
    };

    using Tree = boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, VertexProperties>;

    Tree tree;
    const auto source_vertex = boost::add_vertex(VertexProperties{source}, tree);

    UniformSampler<SpaceType> sampler{space};
    for (auto sample_count{0U}; sample_count < max_samples; sample_count += 100U) {
        detail::expand_tree(tree, sampler, 100U);

        const auto nearest_vertex = detail::nearest_vertex_to(tree, target);
        const auto target_vertex = boost::add_vertex(VertexProperties{target}, tree);

        boost::add_edge(target_vertex, nearest_vertex, tree);
        const auto vertex_path = detail::find_path_in_graph(tree, source_vertex, target_vertex);

        if (vertex_path.has_value()) {
            std::vector<typename SpaceType::vector_type> path;
            std::ranges::transform(vertex_path.value(), std::back_inserter(path),
                                   [&tree](const auto &vertex) { return tree[vertex].config; });

            return path;
        }

        boost::remove_vertex(target_vertex, tree);
    }

    return std::nullopt;
}

} // namespace wheel

#endif // WHEEL_MOTION_RAPIDLY_EXPLORING_RANDOM_TREES_HPP
