find_package(Eigen3 REQUIRED)
find_package(GTest REQUIRED)

include(FetchContent)

FetchContent_Declare(libwheel_metaprogramming
  GIT_REPOSITORY git@github.com:adamlm/libwheel-metaprogramming.git
  GIT_TAG main
)

FetchContent_MakeAvailable(libwheel_metaprogramming)
