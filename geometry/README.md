# Wheel Geometry Library

## Using in your project

1. Add Wheel Geometry as a dependency in your project

   ```cmake
   find_package(libwheel_geometry REQUIRED)
   ```

2. Link against it in your project

   ```cmake
   target_link_libraries(your_project
     PRIVATE
       libwheel::geometry
   )
   ```
