add_library(${PROJECT_NAME}_memory pool_allocator.c)
target_link_libraries(${PROJECT_NAME}_core INTERFACE ${PROJECT_NAME}_memory)