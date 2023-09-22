#[=======================================================================[.rst:
libwheel_target_set_compiler_warnings
-------------------------------------

This module defines a function to set the compiler warning options for a
specified target. The function enables several warnings that alert to common
code issues. Note that there currently is no way to change the set of applied
options, but callers can specify if warnings should be treated as errors.

.. command:: libwheel_target_set_compiler_warnings

  Set the compiler warnings for a specified target:
  functions::

    libwheel_target_set_compiler_warnings(target scope as_error)

    ``libwheel_target_set_compiler_warnings()`` enables several compiler
    warnings for the specified target. The applied warning set covers common
    code issues that should be straightforward to prevent and resolve.

    The options are:

    ``target``
    Specifies the target that will have the compiler options enabled.

    ``scope``
    The ``INTERFACE``, ``PUBLIC``, and ``PRIVATE`` keywords are required to
    specify the scope of the compiler warnings.

    ``WARNINGS_AS_ERRORS``
    If specified, warnings raised by the compiler will be treated as errors.
    Specifying this argument will enable the ``-Werror`` warning for GCC/Clang
    and ``/WX`` for the Microsoft Visual C++ (MSVC) compiler.

#]=======================================================================]

function(libwheel_target_set_compiler_warnings target scope)

  set(noValues WARNINGS_AS_ERRORS)

  cmake_parse_arguments(
    PARSE_ARGV 2
    ARG
    "${noValues}"
    "" # Function has no single-value keyword arguments
    "" # Function has no multi-value keyword arguments
  )

  target_compile_options(${target} ${scope}
    # Common to Clang and GCC
    $<$<CXX_COMPILER_ID:Clang,AppleClang,GNU>:
      -Wall
      -Wextra
      -Wshadow
      -Wnon-virtual-dtor
      -Wold-style-cast
      -Wcast-align
      -Wunused
      -Woverloaded-virtual
      -Wpedantic
      -Wconversion
      -Wsign-conversion
      -Wnull-dereference
      -Wdouble-promotion
      -Wformat=2
      -Wimplicit-fallthrough
      $<$<BOOL:ARG_WARNINGS_AS_ERRORS>:-Werror>
    >

    # Specific to the GNU Compiler Collection (GCC)
    # Note: There is an issue when running clang-tidy beside the CMake build
    # and using GCC. These checks get enabled because we are using GCC,
    # but clang-tidy does not support them.
    # Related CMake issue: https://gitlab.kitware.com/cmake/cmake/-/issues/25257
    $<$<AND:$<CXX_COMPILER_ID:GNU>,$<NOT:$<OR:$<BOOL:CMAKE_CXX_CLANG_TIDY>,$<BOOL:CMAKE_C_CLANG_TIDY>>>>:
      -Wmisleading-indentation
      -Wduplicated-cond
      -Wduplicated-branches
      -Wlogical-op
      -Wuseless-cast
    >

    # Specific to Microsoft Visual C++ (MSVC) compiler
    $<$<CXX_COMPILER_ID:MSCV>:
      /W4
      /w14242
      /w14254
      /w14263
      /w14265
      /w14287
      /we4289
      /w14296
      /w14311
      /w14545
      /w14546
      /w14547
      /w14549
      /w14555
      /w14619
      /w14640
      /w14826
      /w14905
      /w14906
      /w14928
      /permissive-
      $<$<BOOL:ARG_WARNINGS_AS_ERRORS>:/WX>
    >
  )

endfunction()
