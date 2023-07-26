include(GNUInstallDirs)

add_library(wheel_metaprogrammingLibrary INTERFACE)
add_library(libwheel::metaprogramming ALIAS wheel_metaprogrammingLibrary)

target_include_directories(wheel_metaprogrammingLibrary
  INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
)

target_compile_features(wheel_metaprogrammingLibrary
  INTERFACE
    cxx_std_20
)

set_target_properties(wheel_metaprogrammingLibrary PROPERTIES
  EXPORT_NAME metaprogramming
)

install(TARGETS wheel_metaprogrammingLibrary
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
