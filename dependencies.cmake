include(FetchContent)


# Library dependencies
find_package(Boost COMPONENTS Graph REQUIRED)

FetchContent_Declare(libwheel_metaprogramming
  GIT_REPOSITORY git@github.com:adamlm/libwheel-metaprogramming.git
  GIT_TAG main
)

FetchContent_MakeAvailable(libwheel_metaprogramming)


# Unit testing dependencies
if(wheel_motion_planning_ENABLE_TESTING OR PROJECT_IS_TOP_LEVEL)
  find_package(GTest REQUIRED)
endif()


# Example code dependencies
if(wheel_motion_planning_BUILD_EXAMPLES OR PROJECT_IS_TOP_LEVEL)
  find_package(Eigen3 REQUIRED)

  FetchContent_Declare(libwheel_strongly_typed_matrix
    GIT_REPOSITORY git@github.com:adamlm/libwheel-strongly_typed_matrix.git
    GIT_TAG main
  )

  FetchContent_MakeAvailable(libwheel_strongly_typed_matrix)
endif()
