find_package(Eigen3 REQUIRED)
find_package(GTest REQUIRED)

if(wheel_strongly_typed_matrix_BUILD_DOCS OR PROJECT_IS_TOP_LEVEL)
  find_package(Doxygen REQUIRED)
endif()

include(FetchContent)

FetchContent_Declare(libwheel_metaprogramming
  GIT_REPOSITORY git@github.com:adamlm/libwheel-metaprogramming.git
  GIT_TAG main
)

FetchContent_MakeAvailable(libwheel_metaprogramming)
