function(create_nds name arm9)
set (extra_args ${ARGN})
list(LENGTH extra_args extra_count)
if (${extra_count} GREATER 0)
list(GET extra_args 0 arm7)
endif ()
if (NOT arm7)
message(${CMAKE_BINARY_DIR}/${name}.nds)
add_custom_command(
    TARGET ${arm9}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin
    COMMAND ${NDSTOOL} -c ${CMAKE_BINARY_DIR}/bin/${name}.nds -7 ${BLOCKSDS}/sys/default_arm7/arm7.elf -9 $<TARGET_FILE:${arm9}>
    BYPRODUCTS ${CMAKE_BINARY_DIR}/bin/${name}.nds
)
else()
add_custom_command(
    TARGET ${arm9}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin
    COMMAND ${NDSTOOL} -c ${CMAKE_BINARY_DIR}/bin/${name}.nds -7 $<TARGET_FILE:${arm7}> -9 $<TARGET_FILE:${arm9}>
    DEPENDS ${arm7}
    BYPRODUCTS ${CMAKE_BINARY_DIR}/bin/${name}.nds
)
endif()
endfunction()