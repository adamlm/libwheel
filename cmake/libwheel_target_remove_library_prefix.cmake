#[=======================================================================[.rst:
libwheel_target_remove_library_prefix
-------------------------------------

This module defines a function to remove a library's name prefix. Linux- and
Unix-based systems normally prefix libraries with ``lib``, which can lead to
clunky names for libraries whose names already start with ``lib``.

.. command:: libwheel_target_remove_library_prefix

  Remove a library's name prefix:
  functions::

    libwheel_target_remove_library_prefix(target)

  ``libwheel_target_remove_library_prefix()`` removes a library's prefix by
  setting the ``PREFIX`` property to an empty string.

  The options are:

  ``target``
    Specifies the target that will have its prefix removed.

#]=======================================================================]

function(libwheel_target_remove_library_prefix target)

  set_target_properties(${target} PROPERTIES
    PREFIX ""
  )

endfunction()
