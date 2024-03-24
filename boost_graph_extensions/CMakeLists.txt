include(options.cmake)

add_subdirectory(libwheel/boost_graph_extensions)

if(libwheel_boost_graph_extensions_BUILD_TESTS)
  add_subdirectory(test)
endif()
