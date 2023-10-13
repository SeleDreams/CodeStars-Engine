function(set_arm9_compile_options name)
set(ARCH_FLAGS -march=armv5te -mtune=arm946e-s)
target_compile_definitions(${name} PRIVATE __NDS__ ARM9)
target_compile_options(${name} PRIVATE ${ARCH_FLAGS} -mthumb -mthumb-interwork -ffunction-sections -fdata-sections -fomit-frame-pointer)

target_compile_options(${name} PRIVATE
    $<$<COMPILE_LANGUAGE:ASM>:-x assembler-with-cpp>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions -fno-rtti>
)

target_link_options(${name} PRIVATE -mthumb -mthumb-interwork -Wl,-Map,${name}.map -Wl,--gc-sections -nostdlib -T${BLOCKSDS}/sys/crts/ds_arm9.mem -T${BLOCKSDS}/sys/crts/ds_arm9.ld -Wl,--no-warn-rwx-segments)
target_include_directories(${name} SYSTEM PRIVATE ${BLOCKSDS_INCLUDES} ${WONDERFUL_INCLUDES})
target_link_directories(${name} PRIVATE ${BLOCKSDS_LIBRARIES})
target_link_libraries(${name} -Wl,--start-group nds9 c gcc -Wl,--end-group)
endfunction()

function(add_arm9_executable name src)
add_executable(${name} ${src} ${BLOCKSDS}/sys/crts/ds_arm9_crt0.o)
set_arm9_compile_options(${name})
set_property(TARGET ${name} PROPERTY SUFFIX "9.elf")
endfunction()

function(add_arm9_library name src)
add_library(${name} STATIC ${src})
set_arm9_compile_options(${name})
set_property(TARGET ${name} PROPERTY SUFFIX "9.a")
endfunction()
