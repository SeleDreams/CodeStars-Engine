add_library(${PROJECT_NAME}_core INTERFACE)
add_subdirectory(graphics)
add_subdirectory(memory)
add_subdirectory(maths)
target_link_libraries(${PROJECT_NAME} INTERFACE ${PROJECT_NAME}_core)