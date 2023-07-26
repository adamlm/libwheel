include(CMakeFindDependencyMacro)

find_dependency(Boost COMPONENTS Graph REQUIRED)

include(${CMAKE_CURRENT_LIST_DIR}/libwheel_motion_planningTargets.cmake)
