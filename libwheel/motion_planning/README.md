# Wheel Motion Planning Library

This is my motion planning library. More information coming soon!

## Where to go

Want to learn more? Peruse the
[documentation](adamlm.github.io/libwheel-motion_planning).

Want to contribute? Check out the
[Wiki](https://github.com/adamlm/libwheel-motion_planning/wiki) tab.

Need some help or want to chat about things? Head to the
[Discussions](https://github.com/adamlm/libwheel-motion_planning/discussions)
tab.

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
