find_package (GLEW 2.1 REQUIRED)
find_package (glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
add_library(gl-graphics
GLGraphics.c
GLFWFunctions.c
)
target_include_directories(gl-graphics PRIVATE ${GLEW_INCLUDE_DIR} ${glfw3_INCLUDE_DIR})
set(LINK_TARGETS ${LINK_TARGETS} gl-graphics ${GLEW_LIBRARIES} glfw OpenGL m PARENT_SCOPE)