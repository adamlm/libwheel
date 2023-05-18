add_executable(rrt rrt.cpp)

target_include_directories(rrt
  PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
)

target_link_libraries(rrt
  PRIVATE
    libwheel::motion_planning
)

target_compile_options(rrt
  PRIVATE
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

add_executable(custom_space custom_space.cpp)

target_include_directories(custom_space
  PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
)

target_link_libraries(custom_space
  PRIVATE
    libwheel::motion_planning
)
