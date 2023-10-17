

add_compile_definitions(USE_SDL)
find_package(SDL2 REQUIRED)
if (USE_GLEW)
message("GLEW used")
add_compile_definitions(USE_GLEW)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
endif()
add_library(gl-graphics
GLShaderConverter.cpp
GLGraphics.c
GLShader.c
GLMesh.c
SDLFunctions.c
)
set_target_properties(gl-graphics PROPERTIES LANGUAGE CXX)
target_include_directories(gl-graphics PUBLIC ${PROJECT_SOURCE_DIR} ${SDL2_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})
target_link_libraries(gl-graphics core-graphics core-maths SDL2 spirv-cross-cpp spirv-cross-core spirv-cross-glsl stdc++ ${PROJECT_NAME}_libs)
if (USE_GLEW)
target_link_libraries(gl-graphics OpenGL::GL GLEW::glew_s)
else()
target_link_libraries(gl-graphics GLESv2 EGL)
endif()
if (WIN32)
target_link_libraries(gl-graphics dwmapi)
endif()
target_link_libraries(${PLATFORM_SPECIFICS}_graphics INTERFACE gl-graphics)

find_program(GLSLC_COMPILER glslc)
add_custom_command(
    TARGET gl-graphics
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin/shaders
    COMMAND ${GLSLC_COMPILER} ${PROJECT_SOURCE_DIR}/shaders/vertex.vert -o ${CMAKE_BINARY_DIR}/bin/shaders/vertex.spv
    COMMAND ${GLSLC_COMPILER} ${PROJECT_SOURCE_DIR}/shaders/fragment.frag -o ${CMAKE_BINARY_DIR}/bin/shaders/fragment.spv
)