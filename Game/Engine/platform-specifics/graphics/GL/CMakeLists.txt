find_package (glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
add_library(gl-graphics
GLGraphics.c
GLShader.c
GLMesh.c
GLFWFunctions.c
)
set(LINK_TARGETS ${LINK_TARGETS} gl-graphics glfw ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} m PARENT_SCOPE)
target_link_libraries(gl-graphics core-graphics)