
if(USE_GLFW)
add_compile_definitions(USE_GLFW)
find_package(glfw3 REQUIRED)
endif()
if(USE_GLEW)
add_compile_definitions(USE_GLEW)
find_package(GLEW REQUIRED)
endif()

find_package(OpenGL REQUIRED)

add_library(gl-graphics
GLGraphics.c
GLShader.c
GLMesh.c
GLFWFunctions.c
)
target_include_directories(gl-graphics PRIVATE ${PROJECT_SOURCE_DIR})
target_link_libraries(gl-graphics core-graphics GLEW::GLEW glfw OpenGL::GL)
target_link_libraries(${PLATFORM_SPECIFICS}_graphics INTERFACE gl-graphics)