add_library(core-maths
mat.c)
target_include_directories(core-maths PUBLIC ${INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME}_core INTERFACE core-maths)
