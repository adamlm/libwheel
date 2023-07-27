# The Wheel Motion Planning Library

## Using in your project

1. Add Wheel Motion Planning as a dependency in your project

   ```cmake
   find_package(libwheel_motion_planning REQUIRED)
   ```

2. Link against it in your project

   ```cmake
   target_link_libraries(your_project
     PRIVATE
       libwheel::motion_planning
   )
   ```
