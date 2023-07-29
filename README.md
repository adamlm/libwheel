# The Wheel Library

A play on the phrase, "Don't reinvent the wheel," the Wheel Library (`libwheel`) implements various algorithms and data
structures. Some contributions follow existing libraries but with modern designs and techniques. Others are novel and
built from scratch. The Wheel project's structure roughly resembles the Boost Library's, separating software
collections into different libraries.

## Organization

The library comprises several software components grouped by category, similar to the Boost Library's structure. The
Wheel Library offers the following collections (See each collection's `README.md` file for more information.):

- [`angle`][libwheel_angle]: A type-safe angle abstraction that behaves as a circle group element.
- [`geometry`][libwheel_geometry]: A collection of geometry concepts.
- [`metaprogramming`][libwheel_metaprogramming]: A collection of various meta-functions, type traits, and C++ concepts.
- [`motion_planning`][libwheel_motion_planning]: A collection of sampling-based path and motion planning algorithms.
- [`strongly_typed_matrix`][libwheel_strongly_typed_matrix]: A compile-time type-safe compile-time wrapper around the
  Eigen Matrix library for dimensioned linear algebra.

## Building and installing

The Wheel Library is header only and uses CMake as its build system. It's designed to be integrated into other CMake
projects, so you can use `FetchContent` or another mechanism to embed `libwheel` into your project. If you want to
build and install `libwheel` by itself, there are several CMake customization options.

**Note:** The Wheel Library requires C++20 or newer.

### Required tools

- **CMake:** 3.25 or newer
- **If compiling with Clang:** 16.0.0 or newer
- **If compiling with GCC:** 11.3.0 or newer

### Build steps

For building the library with the default options, follow these steps:

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

### Wheel Library collection options

| CMake option                           | Default Value | Description                                    |
| -------------------------------------- | ------------- | ---------------------------------------------- |
| `libwheel_BUILD_ANGLE`                 | `TRUE`        | Build the Wheel Angle Library.                 |
| `libwheel_BUILD_GEOMETRY`              | `TRUE`        | Build the Wheel Geometry Library.              |
| `libwheel_BUILD_METAPROGRAMMING`       | `TRUE`        | Build the Wheel Metaprogramming Library.       |
| `libwheel_BUILD_MOTION_PLANNING`       | `TRUE`        | Build the Wheel Motion Planning Library.       |
| `libwheel_BUILD_STRONGLY_TYPED_MATRIX` | `TRUE`        | Build the Wheel Strongly-Typed Matrix Library. |

### Wheel Library general options

| CMake option                       | Default Value             | Description                                                                                                                    |
| ---------------------------------- | ------------------------- | ------------------------------------------------------------------------------------------------------------------------------ |
| `libwheel_EXPORT_COMPILE_COMMANDS` | `${PROJECT_IS_TOP_LEVEL}` | Export CMake compile commands. This helps IDEs provide accurate IntelliSense features while editing (_e.g._, code completion). |

## Scope and roadmap

The library does not have a well-defined scope, but it focuses on motion planning algorithms and supporting software
components. If there is a feature that you want to see added, create a new thread in the
[Discussions tab][discussions_tab].

## Support

Need some help or want to chat about the library? Head to the repository's [Discussions tab][discussions_tab] to
connect with someone.

## Contributing

Want to help improve the library? Check out the [contribution guidelines][contributions_file] to get started.

## License

See the [`LICENSE.md`][license_file] file for license information.

[libwheel_angle]: angle/README.md
[libwheel_geometry]: geometry/README.md
[libwheel_metaprogramming]: metaprogramming/README.md
[libwheel_motion_planning]: motion_planning/README.md
[libwheel_strongly_typed_matrix]: strongly_typed_matrix/README.md
[discussions_tab]: https://github.com/adamlm/libwheel/discussions
[contributions_file]: CONTRIBUTING.md
[license_file]: LICENSE.md
