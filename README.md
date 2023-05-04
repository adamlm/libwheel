# Wheel Metaprogramming Library

This is my metaprogramming library.


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
