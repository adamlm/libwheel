find_package(Boost COMPONENTS Graph REQUIRED)

if(wheel_motion_planning_ENABLE_TESTING OR PROJECT_IS_TOP_LEVEL)
  find_package(GTest REQUIRED)
endif()

include(FetchContent)

FetchContent_Declare(libwheel_metaprogramming
  GIT_REPOSITORY git@github.com:adamlm/libwheel-metaprogramming.git
  GIT_TAG main
)

FetchContent_MakeAvailable(libwheel_metaprogramming)
