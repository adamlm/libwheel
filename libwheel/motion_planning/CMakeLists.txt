include(GNUInstallDirs)

add_library(wheel_motion_planningLibrary INTERFACE)
add_library(libwheel::motion_planning ALIAS wheel_motion_planningLibrary)

target_include_directories(wheel_motion_planningLibrary
  INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
)

target_link_libraries(wheel_motion_planningLibrary
  INTERFACE
    Boost::graph
    libwheel::metaprogramming
)

target_compile_features(wheel_motion_planningLibrary
  INTERFACE
    cxx_std_20
)

set_target_properties(wheel_motion_planningLibrary PROPERTIES
  EXPORT_NAME motion_planning
)

install(TARGETS wheel_motion_planningLibrary
  EXPORT wheel_motion_planningTargets
  INCLUDES
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/>
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/libwheel/motion_planning
  FILES_MATCHING PATTERN "*.hpp"
)

install(FILES ${PROJECT_SOURCE_DIR}/cmake/libwheel_motion_planningConfig.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libwheel_motion_planning
)

install(EXPORT wheel_motion_planningTargets
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libwheel_motion_planning
  FILE libwheel_motion_planningTargets.cmake
  NAMESPACE libwheel::
)
