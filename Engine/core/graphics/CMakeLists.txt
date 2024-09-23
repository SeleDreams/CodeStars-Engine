add_library(core-graphics
Graphics.c
Mesh.c
)
target_include_directories(core-graphics PUBLIC ${INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}_core INTERFACE core-graphics)