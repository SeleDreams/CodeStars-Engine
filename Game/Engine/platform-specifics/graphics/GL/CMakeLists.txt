find_package (glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
add_library(gl-graphics
GLGraphics.c
GLShader.c
GLMesh.c
GLFWFunctions.c
glad/src/glad.c
)
target_include_directories(gl-graphics PRIVATE glad/include)
set(LINK_TARGETS ${LINK_TARGETS} gl-graphics glfw m PARENT_SCOPE)
target_link_libraries(gl-graphics core-graphics)