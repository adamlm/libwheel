#[=======================================================================[.rst:
libwheel_target_remove_export_name_prefix
-----------------------------------------

This module defines a function that removes the ``libwheel_`` prefix from a
specified Wheel Library target's ``EXPORT_NAME``. By convention, Wheel Library
names its CMake targets ``libwheel_<library>``, but this naming convention
makes a user's CMake configuration look like ``libwheel::libwheel_<library>``
when they want to link against that library.

.. command:: libwheel_target_remove_export_name_prefix

  Remove the ``libwheel_`` prefix from a target's ``EXPORT_NAME``:
  functions::

    libwheel_target_remove_export_name_prefix(target)

  ``libwheel_target_remove_export_name_prefix()`` removes the ``libwheel_``
  prefix from a specified target's ``EXPORT_NAME``.

  The options are:

  ``target``
    Specifies the target that will have its ``EXPORT_NAME`` modified.

#]=======================================================================]

function(libwheel_target_remove_export_name_prefix target prefix)

  if(target MATCHES "${prefix}*")
    string(REPLACE ${prefix} "" target_no_prefix ${target})

    set_target_properties(${target}
      PROPERTIES
        EXPORT_NAME ${target_no_prefix}
    )
  endif()

endfunction()
