add_library(core-maths
mat.c
quat.c
vec.c)
target_include_directories(core-maths PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${INCLUDE_DIRS})
if (NintendoDS)
    set_arm9_compile_options(core-maths)
endif ()
target_link_libraries(${PROJECT_NAME}_core INTERFACE core-maths)
