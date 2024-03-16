#ifndef LIBWHEEL_BOOST_GRAPH_EXTENSIONS_HPP
#define LIBWHEEL_BOOST_GRAPH_EXTENSIONS_HPP

#include <exception>

#include "libwheel/boost_graph_extensions/concepts.hpp"
#include "libwheel/boost_graph_extensions/type_traits.hpp"

namespace wheel::boost_graph_extensions {

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

} // namespace wheel::boost_graph_extensions

#endif // LIBWHEEL_BOOST_GRAPH_EXTENSIONS_HPP
