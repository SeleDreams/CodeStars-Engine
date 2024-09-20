add_library(core-maths
mat.c)
message("core maths " ${INCLUDE_DIRS})
target_include_directories(core-maths PUBLIC ${INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME}_core INTERFACE core-maths)
