add_library(wheel_angleLibrary INTERFACE)
add_library(libwheel::angle ALIAS wheel_angleLibrary)

target_include_directories(wheel_angleLibrary
  INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
)

target_compile_features(wheel_angleLibrary
  INTERFACE
    cxx_std_20
)

target_compile_options(wheel_angleLibrary
  INTERFACE
    -Wall
    -Wextra
    -Wshadow
    -Wnon-virtual-dtor
    -Wpedantic
    -Wold-style-cast
    -Wunused
    -Wconversion
    -Wsign-conversion
    -Wcast-align
    -Woverloaded-virtual
    -Wdouble-promotion
    -Wformat=2
    -Wimplicit-fallthrough
    -Werror
)

set_target_properties(wheel_angleLibrary PROPERTIES
  EXPORT_NAME angle
)

install(TARGETS wheel_angleLibrary
  EXPORT wheel_angleTargets
  INCLUDES
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/>
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/libwheel/angle
  FILES_MATCHING PATTERN "*.hpp"
)

install(EXPORT wheel_angleTargets
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libwheel_angle
  FILE libwheel_angleTargets.cmake
  NAMESPACE libwheel::
)
