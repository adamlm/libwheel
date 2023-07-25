# Wheel Angle Library

## Introduction

This library module contains an angle class.

### What is the Wheel Library?

A play on the phrase, "Don't reinvent the wheel," the Wheel Library (`libwheel`) contains my implementations for
various algorithms and data structures. It also comprises several library re-implementations using modern techniques
and designs that I consider to be improvements on the originals. Occasionally, I may add some completely novel modules.
The Wheel Library's structure follows the Boost Library's, splitting components into separate modules and source code
repositories.

## Getting started

### Building from source

1. Install Conan dependencies

    ```shell
    $ conan install . --output-folder=build --build=missing
    ```

2. Configure the CMake project

    ```shell
    $ cmake -B build -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release .
    ```

3. Build the library

    ```shell
    $ cmake --build build
    ```

4. (Optional) Install the library

    ```shell
    $ sudo cmake --install build  # Install to /usr/local/
    ```
    or
    ```shell
    $ cmake --install build --prefix=<install_path>  # Install to custom location
    ```
