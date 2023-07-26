set(DOXYGEN_INPUT_DIR ${PROJECT_SOURCE_DIR})
set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR})

configure_file(Doxyfile.in Doxyfile)

add_custom_target(wheel_strongly_typed_matrixDocumentation
  COMMAND Doxygen::doxygen ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
  COMMAND sphinx-build
    -b html
    -Dbreathe_projects.wheel_strongly_typed_matrix=${CMAKE_CURRENT_BINARY_DIR}/xml
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/sphinx
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
