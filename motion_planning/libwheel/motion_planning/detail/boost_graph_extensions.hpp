#ifndef LIBWHEEL_MOTION_PLANNING_DETAIL_BOOST_GRAPH_EXTENSIONS_HPP
#define LIBWHEEL_MOTION_PLANNING_DETAIL_BOOST_GRAPH_EXTENSIONS_HPP

#include <boost/graph/graph_traits.hpp>

namespace wheel::motion_planning::detail {

template <typename T>
concept boost_graph = requires {
    typename boost::graph_traits<T>::vertex_descriptor;
    typename boost::graph_traits<T>::edge_descriptor;
    typename boost::graph_traits<T>::directed_category;
    typename boost::graph_traits<T>::edge_parallel_category;
    typename boost::graph_traits<T>::traversal_category;
};

template <boost_graph Graph>
using vertex_descriptor_t = typename boost::graph_traits<Graph>::vertex_descriptor;

template <boost_graph Graph>
using edge_descriptor_t = typename boost::graph_traits<Graph>::edge_descriptor;

template <boost_graph Graph>
using vertex_bundle_t = typename boost::vertex_bundle_type<Graph>::type;

template <boost_graph Graph>
class early_search_termination : public std::runtime_error {
  public:
    explicit early_search_termination(std::string const &what_arg, vertex_descriptor_t<Graph> vertex)
        : early_search_termination{what_arg.c_str(), vertex} {}

    explicit early_search_termination(char const *what_arg, vertex_descriptor_t<Graph> vertex)
        : std::runtime_error{what_arg}, vertex_{vertex} {}

    auto get_last_vertex() const noexcept -> vertex_descriptor_t<Graph> { return vertex_; }

  private:
    vertex_descriptor_t<Graph> vertex_;
};

} // namespace wheel::motion_planning::detail

#endif // LIBWHEEL_MOTION_PLANNING_DETAIL_BOOST_GRAPH_EXTENSIONS_HPP
