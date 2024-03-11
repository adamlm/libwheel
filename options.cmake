option(libwheel_EXPORT_COMPILE_COMMANDS
  "Export the Wheel Library CMake compile commands"
  ${PROJECT_IS_TOP_LEVEL}
)

option(libwheel_BUILD_LIBS
  "Build all Wheel Library libraries by default"
  ${PROJECT_IS_TOP_LEVEL}
)

option(libwheel_BUILD_TESTS
  "Build all Wheel Library tests by default"
  ${PROJECT_IS_TOP_LEVEL}
)

option(libwheel_BUILD_INSTALL
  "Build all Wheel Library CMake install targets by default"
  ${PROJECT_IS_TOP_LEVEL}
)

option(libwheel_BUILD_DOCS
  "Build all Wheel Library documentation by default"
  ${PROJECT_IS_TOP_LEVEL}
)

option(libwheel_BUILD_EXAMPLES
  "Build all Wheel Library examples by default"
  ${PROJECT_IS_TOP_LEVEL}
)

option(libwheel_BUILD_PACKAGING
  "Build all Wheel Library packaging artifacts by default"
  ${PROJECT_IS_TOP_LEVEL}
)

option(libwheel_BUILD_PACKAGING
  "Build all Wheel Library packaging artifacts by default"
  ${PROJECT_IS_TOP_LEVEL}
)

option(libwheel_algorithm_BUILD_LIB
  "Build the Wheel Algorithm library"
  ${libwheel_BUILD_LIBS}
)

option(libwheel_angle_BUILD_LIB
  "Build the Wheel Angle library"
  ${libwheel_BUILD_LIBS}
)

option(libwheel_boost_graph_extensions_BUILD_LIB
  "Build the Wheel Boost Graph Extensions library"
  ${libwheel_BUILD_LIBS}
)

option(libwheel_controls_BUILD_LIB
  "Build the Wheel Controls library"
  ${libwheel_BUILD_LIBS}
)

option(libwheel_dimensioned_algebra_BUILD_LIB
  "Build the Wheel Dimensioned Algebra library"
  ${libwheel_BUILD_LIBS}
)

option(libwheel_exception_BUILD_LIB
  "Build the Wheel Exception library"
  ${libwheel_BUILD_LIBS}
)

option(libwheel_geometry_BUILD_LIB
  "Build the Wheel Geometry library"
  ${libwheel_BUILD_LIBS}
)

option(libwheel_math_BUILD_LIB
  "Build the Wheel Math library"
  ${libwheel_BUILD_LIBS}
)

option(libwheel_metaprogramming_BUILD_LIB
  "Build the Wheel Metaprogramming library"
  ${libwheel_BUILD_LIBS}
)

option(libwheel_motion_planning_BUILD_LIB
  "Build the Wheel Motion Planning library"
  ${libwheel_BUILD_LIBS}
)

option(libwheel_optimization_BUILD_LIB
  "Build the Wheel Optimization library"
  ${libwheel_BUILD_LIBS}
)

option(libwheel_strongly_typed_matrix_BUILD_LIB
  "Build the Wheel Strongly-Typed Matrix library"
  ${libwheel_BUILD_LIBS}
)
