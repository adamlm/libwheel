#[=======================================================================[.rst:
libwheel_target_set_install_rules
---------------------------------

This module defines a function to set the installation rules for a library. A
library must have installation rules to be installable after being built, but
the necessary CMake commands create a lot of duplicate boilerplate code.

.. command:: libwheel_target_set_install_rules

  Set the installation rules for a CMake library and its associated header,
  package configuration, and imported targets files:
  functions::

    libwheel_target_set_install_rules(target)

  ``libwheel_target_set_install_rules()`` sets a library's installation rules
  using the conventional structure for the Wheel Library.

  The options are:

  ``target``
  Specifies the target that will have installation rules specified for it.

#]=======================================================================]

include(GNUInstallDirs)
include(libwheel_target_remove_export_name_prefix)
include(libwheel_target_remove_library_prefix)

function(libwheel_target_set_install_rules target)

  libwheel_target_remove_library_prefix(${target})
  libwheel_target_remove_export_name_prefix(${target} "wheel_")

  install(TARGETS ${target}
    EXPORT ${target}Targets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )

  install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.hpp"
  )

  string(REPLACE "libwheel_" "" target_no_prefix ${target})

  install(FILES ${PROJECT_SOURCE_DIR}/${target_no_prefix}/cmake/${target}Config.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${target}
  )

  install(EXPORT ${target}Targets
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${target}
    FILE ${target}Targets.cmake
    NAMESPACE libwheel::
  )

endfunction()
