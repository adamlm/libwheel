#[=======================================================================[.rst:
libwheel_add_to_build
---------------------

This module defines a function to add a Wheel Library to the build tree. Some
Wheel libraries may be built as standalone libraries while also being included
as dependencies for other Wheel libraries simultanesouly being built. Using
the add_subdirectory() function can lead to issues in this case because the
contained targets would be defined multiple times. Instead, we can use
``FetchContent``, which provides the end-results we are looking for but without
the management headache.

.. command:: libwheel_add_to_build

  Add specified Wheel Library package's directory to the buld tree using
  ``FetchContent``:
  functions::

    libwheel_add_to_build(package)

  ``libwheel_add_to_build()`` adds the specified Wheel Library package's
  containing subdirectory to the build tree using ``FetchContent``. Note
  that this function makes several implicit assumptions:

    1. Argument ``package`` uses the naming convention ``libwheel_<library>``,
       where ``<library>`` is the name of the Wheel Library library of interest.
    2. The containing subdirectory of ``<library>`` uses the name ``<library>``.

  The options are:

  ``package``
    Specifies the Wheel Library package name that will be added. The name
    specified in this option is the same name that would be used in a
    ``find_pacakge()`` call.

#]=======================================================================]

include(FetchContent)

function(libwheel_add_to_build package)

  string(REPLACE "libwheel_" "" package_no_prefix ${package})

  FetchContent_Declare(${package}
    SOURCE_DIR ${PROJECT_SOURCE_DIR}/${package_no_prefix}
  )

  FetchContent_MakeAvailable(${package})

endfunction()
