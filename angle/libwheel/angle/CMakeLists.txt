include(libwheel_target_set_install_rules)

add_library(libwheel_angle INTERFACE)
add_library(libwheel::angle ALIAS libwheel_angle)

target_include_directories(libwheel_angle
  INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/angle>
)

target_compile_features(libwheel_angle
  INTERFACE
    cxx_std_20
)

target_compile_options(libwheel_angle
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

libwheel_target_set_install_rules(libwheel_angle)
