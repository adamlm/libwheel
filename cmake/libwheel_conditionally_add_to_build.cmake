include(libwheel_add_to_build)

function(libwheel_conditionally_add_to_build package condition)

  if(condition)

    libwheel_add_to_build(${package})

  else()

  endif()

endfunction()
