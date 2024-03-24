#ifndef LIBWHEEL_BOOST_GRAPH_EXTENSIONS_VISITORS_HPP
#define LIBWHEEL_BOOST_GRAPH_EXTENSIONS_VISITORS_HPP

#include <boost/graph/visitors.hpp>

#include "libwheel/boost_graph_extensions/concepts.hpp"

namespace wheel::boost_graph_extensions {

template <typename VertexOrEdge>
struct predicate_satisfied {
  public:
    explicit predicate_satisfied(VertexOrEdge vertex_or_edge) : vertex_or_edge_{vertex_or_edge} {}

    auto get_satisfying_descriptor() const noexcept { return vertex_or_edge_; }

  private:
    VertexOrEdge vertex_or_edge_;
};

template <typename Predicate, typename EventTag>
struct predicate_checker : boost::base_visitor<predicate_checker<Predicate, EventTag>> {
    using event_filter = EventTag;

    explicit predicate_checker(Predicate p) : predicate_{p} {}

    auto operator()(auto vertex_or_edge, boost_graph auto const &graph) const -> void {
        if (predicate_(vertex_or_edge, graph)) {
            throw predicate_satisfied{vertex_or_edge};
        }
    }

    Predicate predicate_;
};

template <typename Predicate, typename EventTag>
auto check_predicate(Predicate p, EventTag /* t */) {
    return predicate_checker<Predicate, EventTag>{p};
}

} // namespace wheel::boost_graph_extensions

#endif // LIBWHEEL_BOOST_GRAPH_EXTENSIONS_VISITORS_HPP
