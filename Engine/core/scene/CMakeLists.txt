add_library(core-scene scene.c camera.c)
target_include_directories(core-scene PUBLIC ${INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME}_core INTERFACE core-scene)