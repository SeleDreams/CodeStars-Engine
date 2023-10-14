add_library(${PROJECT_NAME}_libs INTERFACE)
add_subdirectory(libfixmatrix)
target_link_libraries(${PROJECT_NAME} INTERFACE ${PROJECT_NAME}_libs)