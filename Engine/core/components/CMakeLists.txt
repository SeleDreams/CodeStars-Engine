add_library(core-components transform.c)
target_include_directories(core-components PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}_core INTERFACE core-components)