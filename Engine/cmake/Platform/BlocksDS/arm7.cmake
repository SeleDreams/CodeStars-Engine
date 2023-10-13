function(set_arm7_compile_options name)
set(ARCH_FLAGS -mcpu=arm7tdmi -mtune=arm7tdmi)
target_compile_definitions(${name} PRIVATE __NDS__ ARM7)
target_compile_options(${name} PRIVATE ${ARCH_FLAGS} -mthumb -mthumb-interwork -ffunction-sections -fdata-sections -fomit-frame-pointer)

target_compile_options(${name} PRIVATE
    $<$<COMPILE_LANGUAGE:ASM>:-x assembler-with-cpp>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions -fno-rtti>
)
target_link_options(${name} PRIVATE -mthumb -mthumb-interwork -Wl,-Map,${name}.map -Wl,--gc-sections -nostdlib -T${BLOCKSDS}/sys/crts/ds_arm7.ld -Wl,--no-warn-rwx-segments )
target_include_directories(${name} SYSTEM PRIVATE ${BLOCKSDS_INCLUDES} SYSTEM ${WONDERFUL_INCLUDES})
target_link_directories(${name} PRIVATE ${BLOCKSDS_LIBRARIES})
target_link_libraries(${name} -Wl,--start-group nds7 -lc -lgcc -Wl,--end-group)
endfunction()

function(add_arm7_executable name src)
add_executable(${name} ${src} ${BLOCKSDS}/sys/crts/ds_arm7_crt0.o)
set_arm7_compile_options(${name})
set_property(TARGET ${name} PROPERTY SUFFIX "7.elf")
endfunction()

function(add_arm7_library name src)
add_library(${name} STATIC ${src})
set_arm7_compile_options(${name})
set_property(TARGET ${name} PROPERTY SUFFIX "7.a")
endfunction()