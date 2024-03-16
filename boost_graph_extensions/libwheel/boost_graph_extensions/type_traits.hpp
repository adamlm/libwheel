#ifndef LIBWHEEL_BOOST_GRAPH_EXTENSIONS_TYPE_TRAITS_HPP
#define LIBWHEEL_BOOST_GRAPH_EXTENSIONS_TYPE_TRAITS_HPP

#include <boost/graph/graph_traits.hpp>

#if __cpp_concepts
#include "libwheel/boost_graph_extensions/concepts.hpp"
#endif

namespace wheel::boost_graph_extensions {

#if __cpp_concepts
template <boost_graph Graph>
#else
template <typename Graph>
#endif
using vertex_descriptor_t = typename boost::graph_traits<Graph>::vertex_descriptor;

#if __cpp_concepts
template <boost_graph Graph>
#else
template <typename Graph>
#endif
using edge_descriptor_t = typename boost::graph_traits<Graph>::edge_descriptor;

#if __cpp_concepts
template <boost_graph Graph>
#else
template <typename Graph>
#endif
using vertex_bundle_t = typename boost::vertex_bundle_type<Graph>::type;

#if __cpp_concepts
template <boost_graph Graph>
#else
template <typename Graph>
#endif
using edge_bundle_t = typename boost::edge_bundle_type<Graph>::type;

} // namespace wheel::boost_graph_extensions

#endif // LIBWHEEL_BOOST_GRAPH_EXTENSIONS_TYPE_TRAITS_HPP
