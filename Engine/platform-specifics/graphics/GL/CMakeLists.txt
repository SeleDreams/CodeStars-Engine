add_compile_definitions(USE_SDL)
find_package(SDL2 REQUIRED)
if (USE_GLEW)
    message(STATUS "GLEW used")
    add_compile_definitions(USE_GLEW)
    find_package(GLEW REQUIRED)
endif ()
find_package(OpenGL REQUIRED)
add_library(gl-graphics
        GLGraphics.c
        GLMesh.c
        SDLFunctions.c
)
#set_target_properties(gl-graphics PROPERTIES LANGUAGE CXX)
target_include_directories(gl-graphics PUBLIC ${PROJECT_SOURCE_DIR} ${SDL2_INCLUDE_DIRS} ${INCLUDE_DIRS})

#[[if (USE_GLEW)
    target_include_directories(gl-graphics PUBLIC ${GLEW_INCLUDE_DIRS})
    target_link_libraries(gl-graphics OpenGL::GL GLEW::glew_s)
else ()
    target_link_libraries(gl-graphics GLESv2 EGL)
endif ()]]
target_link_libraries(gl-graphics GLESv2 EGL)
target_link_libraries(${PLATFORM_SPECIFICS}_graphics INTERFACE SDL2 ${PROJECT_NAME}_core gl-graphics)

target_link_libraries(core-graphics gl-graphics)
#[[
find_program(GLSLC_COMPILER glslc)
add_custom_command(
        TARGET gl-graphics
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin/shaders
        COMMAND ${GLSLC_COMPILER} ${PROJECT_SOURCE_DIR}/shaders/vertex.vert -o ${CMAKE_BINARY_DIR}/bin/shaders/vertex.spv
        COMMAND ${GLSLC_COMPILER} ${PROJECT_SOURCE_DIR}/shaders/fragment.frag -o ${CMAKE_BINARY_DIR}/bin/shaders/fragment.spv
)]]
