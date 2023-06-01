cmake_minimum_required(VERSION 3.22)
project(wheel_strongly_typed_matrix)
enable_testing()

option(wheel_strongly_typed_matrix_ENABLE_TESTING "Enable unit tests" ${PROJECT_IS_TOP_LEVEL})
option(wheel_strongly_typed_matrix_BUILD_EXAMPLES "Build examples" ${PROJECT_IS_TOP_LEVEL})
option(wheel_strongly_typed_matrix_BUILD_DOCS "Build doxumentation" ${PROJECT_IS_TOP_LEVEL})
option(wheel_strongly_typed_matrix_EXPORT_COMPILE_COMMANDS "Export compile commands" ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ${wheel_strongly_typed_matrix_EXPORT_COMPILE_COMMANDS})

include(dependencies.cmake)

add_subdirectory(libwheel/strongly_typed_matrix)

if(wheel_strongly_typed_matrix_ENABLE_TESTING OR PROJECT_IS_TOP_LEVEL)
  add_subdirectory(test)
endif()

if(wheel_strongly_typed_matrix_BUILD_EXAMPLES OR PROJECT_IS_TOP_LEVEL)
  add_subdirectory(examples)
endif()

if(wheel_strongly_typed_matrix_BUILD_DOCS OR PROJECT_IS_TOP_LEVEL)
  add_subdirectory(docs)
endif()
