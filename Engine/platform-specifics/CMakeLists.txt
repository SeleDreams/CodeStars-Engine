set(PLATFORM_SPECIFICS ${PROJECT_NAME}_platform-specifics)
add_library(${PLATFORM_SPECIFICS} INTERFACE)
add_subdirectory(graphics)
target_link_libraries(${PROJECT_NAME} INTERFACE ${PLATFORM_SPECIFICS})