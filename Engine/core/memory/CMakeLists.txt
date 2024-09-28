add_library(core-memory pool_allocator.c)
target_include_directories(core-memory PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME}_core INTERFACE core-memory)