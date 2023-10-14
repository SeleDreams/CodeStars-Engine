add_library(core-maths
mat.c)

target_link_libraries(${PROJECT_NAME}_core INTERFACE core-maths)