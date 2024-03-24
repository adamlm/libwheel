#include <gtest/gtest.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <libwheel/boost_graph_extensions/type_traits.hpp>
#include <libwheel/boost_graph_extensions/visitors.hpp>

namespace wheel_bge = wheel::boost_graph_extensions;

TEST(BoostGraphExtensions, PredicateCheckerVertexFound) {
    boost::adjacency_list graph{};
    auto const vertex_u{boost::add_vertex(graph)};
    auto const vertex_v{boost::add_vertex(graph)};

    boost::add_edge(vertex_u, vertex_v, graph);

    auto const visitor{boost::make_bfs_visitor(wheel_bge::check_predicate(
        [vertex_v](auto vertex, auto const & /* graph */) { return vertex == vertex_v; }, boost::on_examine_vertex{}))};

    EXPECT_THROW(boost::breadth_first_search(graph, vertex_u, boost::visitor(visitor)),
                 wheel_bge::predicate_satisfied<wheel_bge::vertex_descriptor_t<decltype(graph)>>);

    try {
        boost::breadth_first_search(graph, vertex_u, boost::visitor(visitor));
    } catch (wheel_bge::predicate_satisfied<wheel_bge::vertex_descriptor_t<decltype(graph)>> const &result) {
        EXPECT_EQ(result.get_satisfying_descriptor(), vertex_v);
    }
}

TEST(BoostGraphExtensions, PredicateCheckerVertexNotFound) {
    boost::adjacency_list graph{};
    auto const vertex_u{boost::add_vertex(graph)};
    auto const vertex_v{boost::add_vertex(graph)};

    auto const visitor{boost::make_bfs_visitor(wheel_bge::check_predicate(
        [vertex_v](auto vertex, auto const & /* graph */) { return vertex == vertex_v; }, boost::on_examine_vertex{}))};

    EXPECT_NO_THROW(boost::breadth_first_search(graph, vertex_u, boost::visitor(visitor)));
}
