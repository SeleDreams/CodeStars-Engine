add_library(core-graphics
Graphics.c
Mesh.c
)
target_include_directories(core-graphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${INCLUDE_DIRS})
if (NintendoDS)
    set_arm9_compile_options(core-graphics)
endif ()
target_link_libraries(${PROJECT_NAME}_core INTERFACE core-graphics)
