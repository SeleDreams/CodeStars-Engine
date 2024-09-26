add_library(${PROJECT_NAME}_core INTERFACE)
add_subdirectory(graphics)
add_subdirectory(memory)
add_subdirectory(maths)
add_subdirectory(scene)

target_link_libraries(${PROJECT_NAME} INTERFACE ${PROJECT_NAME}_core)