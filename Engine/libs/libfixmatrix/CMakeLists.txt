add_subdirectory(libfixmath)
file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
add_library(libfixmatrix
    ${SRC_FILES}
)
get_target_property(INCLUDE_DIRS libfixmath INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(libfixmatrix PUBLIC ${INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(libfixmatrix libfixmath)
target_link_libraries(${PROJECT_NAME}_libs INTERFACE libfixmatrix)