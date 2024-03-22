#ifndef LIBWHEEL_MOTION_PLANNING_VERTEX_SELECTION_HPP
#define LIBWHEEL_MOTION_PLANNING_VERTEX_SELECTION_HPP

#include "libwheel/boost_graph_extensions/concepts.hpp"

namespace wheel::motion_planning {

template <typename Metric>
struct closest_vertex_selector {

    explicit closest_vertex_selector(Metric metric) : metric_{std::move(metric)} {}

    auto operator()(wheel::boost_graph_extensions::boost_graph auto const &graph, auto const &value) const {
        auto const vertex_range{boost::make_iterator_range(boost::vertices(graph))};
        return *std::ranges::min_element(vertex_range, std::ranges::less{},
                                         [this, &graph, &value](auto const &v) { return metric_(graph[v], value); });
    }

  private:
    Metric metric_;
};

} // namespace wheel::motion_planning

#endif // LIBWHEEL_MOTION_PLANNING_VERTEX_SELECTION_HPP
