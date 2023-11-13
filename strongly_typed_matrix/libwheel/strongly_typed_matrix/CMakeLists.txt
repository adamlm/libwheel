add_library(wheel_strongly_typed_matrix INTERFACE)
add_library(libwheel::strongly_typed_matrix ALIAS wheel_strongly_typed_matrix)

target_include_directories(wheel_strongly_typed_matrix
  INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/strongly_typed_matrix>
)

target_link_libraries(wheel_strongly_typed_matrix
  INTERFACE
    libwheel::metaprogramming
    Eigen3::Eigen
)

target_compile_features(wheel_strongly_typed_matrix
  INTERFACE
    cxx_std_20
)

set_target_properties(wheel_strongly_typed_matrix PROPERTIES
  EXPORT_NAME strongly_typed_matrix
)

install(TARGETS wheel_strongly_typed_matrix
  EXPORT wheel_strongly_typed_matrixTargets
  INCLUDES
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/>
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/libwheel/strongly_typed_matrix
  FILES_MATCHING PATTERN "*.hpp"
)

install(EXPORT wheel_strongly_typed_matrixTargets
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libwheel_strongly_typed_matrix
  FILE libwheel_strongly_typed_matrixTargets.cmake
  NAMESPACE libwheel::
)
