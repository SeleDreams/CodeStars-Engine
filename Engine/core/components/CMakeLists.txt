add_library(core-components transform.c)
target_include_directories(core-components PUBLIC ${INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME}_core INTERFACE core-components)