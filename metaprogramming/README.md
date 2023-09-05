# The Wheel Metaprogramming Library

This library contains several type traits and metafunctions to supplement the Standard Library's metaprogramming
features.

## Using in your project

1. Add Wheel Metaprogramming as a dependency in your project

   ```cmake
   find_package(libwheel_metaprogramming REQUIRED)
   ```

2. Link against it in your project

   ```cmake
   target_link_libraries(your_project
     PRIVATE
       libwheel::metaprogramming
   )
   ```

## Library-specific CMake options

| Option                                    | Default value                | Description                               |
|-------------------------------------------|------------------------------|-------------------------------------------|
| `libwheel_metaprogramming_BUILD_LIB`      | `${libwheel_BUILD_LIBS}`     | Build the library                         |
| `libwheel_metaprogramming_BUILD_TESTS`    | `${libwheel_BUILD_TESTS}`    | Build the library's tests                 |
| `libwheel_metaprogramming_BUILD_INSTALL`  | `${libwheel_BUILD_INSTALL}`  | Build the library's CMake install targets |
| `libwheel_metaprogramming_BUILD_DOCS`     | `${libwheel_BUILD_DOCS}`     | Build the library's documentation         |
| `libwheel_metaprogramming_BUILD_EXAMPLES` | `${libwheel_BUILD_EXAMPLES}` | Build the library's examples              |
