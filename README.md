# Introduction

The Wheel Metaprogramming library (`libwheel_metaprogramming`) contains various metaprogramming facilities, such as
meta-functions, concepts, and type traits.


# What is the Wheel project?

A play on the phrase, "Don't reinvent the wheel," the Wheel project (`libwheel`) implements various algorithms and data
structures. Some contributions follow existing libraries but with modern designs and techniques. Others are novel and
built from scratch. The Wheel project's structure roughly resembles the Boost Library's, separating software
collections into different libraries. One notable difference is that Wheel libraries version themselves independently
compared to Boost's project-wide versioning.


# Building the library

This library is header only, so you can embed it directly into your project. You can also build it using CMake and
import it using CMake's `find_package(...)` functionality.

## Project CMake options

| Option | Default Value | Description|
|--------|---------------|------------|
| `wheel_metaprogramming_ENABLE_TESTING` | `TRUE` if top-level project; `FALSE` otherwise | Enable unit tests. Unit tests in this project are compile-time `static_assert`s, so the test code will only compile if the tests pass. |
| `wheel_metaprogramming_EXPORT_COMPILE_COMMANDS` | `ON` | Export CMake compile commands. This helps VS Code provide accurate IntelliSense features while editing (_e.g._, code completion).

## Build steps (with default options)

1. Configure the CMake project

    ```shell
    $ cmake -B build .
    ```

2. Build the library

    ```shell
    $ cmake --build build
    ```

3. (Optional) Install the library

    ```shell
    $ sudo cmake --install build  # Install to /usr/local/
    ```
    or
    ```shell
    $ cmake --install build --prefix=<install_path>  # Install to custom location
    ```


# Using Wheel Metaprogramming in your project

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
