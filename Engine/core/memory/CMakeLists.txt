add_library(${CMAKE_PROJECT_NAME}_memory pool_allocator.c)
target_link_libraries(${PROJECT_NAME}_core INTERFACE ${CMAKE_PROJECT_NAME}_memory)