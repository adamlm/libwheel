include(GNUInstallDirs)

add_library(wheel_metaprogramming INTERFACE)
add_library(libwheel::metaprogramming ALIAS wheel_metaprogramming)

target_include_directories(wheel_metaprogramming
  INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/metaprogramming>
)

target_compile_features(wheel_metaprogramming
  INTERFACE
    cxx_std_20
)

set_target_properties(wheel_metaprogramming PROPERTIES
  EXPORT_NAME metaprogramming
)

install(TARGETS wheel_metaprogramming
  EXPORT wheel_metaprogrammingTargets
  INCLUDES
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/>
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/libwheel/metaprogramming
  FILES_MATCHING PATTERN "*.hpp"
)

install(EXPORT wheel_metaprogrammingTargets
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libwheel_metaprogramming
  FILE libwheel_metaprogrammingConfig.cmake
  NAMESPACE libwheel::
)
