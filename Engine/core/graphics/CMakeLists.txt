add_library(core-graphics
Graphics.c
Mesh.c
)
target_link_libraries(${PROJECT_NAME}_core INTERFACE core-graphics)