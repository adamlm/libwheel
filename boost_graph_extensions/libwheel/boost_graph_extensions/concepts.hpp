#ifndef LIBWHEEL_BOOST_GRAPH_EXTENSIONS_CONCEPTS_HPP
#define LIBWHEEL_BOOST_GRAPH_EXTENSIONS_CONCEPTS_HPP

#include <concepts>

#include <boost/graph/graph_traits.hpp>

namespace wheel::boost_graph_extensions {

template <typename T>
concept boost_graph = requires {
    typename boost::graph_traits<T>::vertex_descriptor;
    typename boost::graph_traits<T>::edge_descriptor;
    typename boost::graph_traits<T>::directed_category;
    typename boost::graph_traits<T>::edge_parallel_category;
    typename boost::graph_traits<T>::traversal_category;
};

} // namespace wheel::boost_graph_extensions

#endif // LIBWHEEL_BOOST_GRAPH_EXTENSIONS_CONCEPTS_HPP
