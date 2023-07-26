include(GNUInstallDirs)

add_library(wheel_geometryLibrary INTERFACE)
add_library(libwheel::geometry ALIAS wheel_geometryLibrary)

target_include_directories(wheel_geometryLibrary
  INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
)

target_link_libraries(wheel_geometryLibrary
  INTERFACE
    Eigen3::Eigen
)

target_compile_features(wheel_geometryLibrary
  INTERFACE
    cxx_std_20
)

set_target_properties(wheel_geometryLibrary PROPERTIES
  EXPORT_NAME geometry
)

install(TARGETS wheel_geometryLibrary
  EXPORT wheel_geometryTargets
  INCLUDES
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/>
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/libwheel/geometry
  FILES_MATCHING PATTERN "*.hpp"
)

install(FILES ${PROJECT_SOURCE_DIR}/cmake/libwheel_geometryConfig.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libwheel_geometry
)

install(EXPORT wheel_geometryTargets
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libwheel_geometry
  FILE libwheel_geometryTargets.cmake
  NAMESPACE libwheel::
)
