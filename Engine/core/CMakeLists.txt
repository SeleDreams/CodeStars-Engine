add_library(${PROJECT_NAME}_core INTERFACE)
add_subdirectory(graphics)
target_link_libraries(${PROJECT_NAME} INTERFACE ${PROJECT_NAME}_core)