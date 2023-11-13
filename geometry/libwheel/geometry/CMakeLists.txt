include(GNUInstallDirs)

add_library(wheel_geometry INTERFACE)
add_library(libwheel::geometry ALIAS wheel_geometry)

target_include_directories(wheel_geometry
  INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/geometry>
)

target_link_libraries(wheel_geometry
  INTERFACE
    Eigen3::Eigen
    range-v3::range-v3
)

target_compile_features(wheel_geometry
  INTERFACE
    cxx_std_20
)

set_target_properties(wheel_geometry PROPERTIES
  EXPORT_NAME geometry
)

install(TARGETS wheel_geometry
  EXPORT wheel_geometryTargets
  INCLUDES
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/>
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/libwheel/geometry
  FILES_MATCHING PATTERN "*.hpp"
)

install(FILES ${PROJECT_SOURCE_DIR}/geometry/cmake/libwheel_geometryConfig.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libwheel_geometry
)

install(EXPORT wheel_geometryTargets
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libwheel_geometry
  FILE libwheel_geometryTargets.cmake
  NAMESPACE libwheel::
)
