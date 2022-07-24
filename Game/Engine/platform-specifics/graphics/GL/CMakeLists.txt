find_package (GLEW REQUIRED)
find_package (glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
add_library(gl-graphics
GLGraphics.c
GLFWFunctions.c
)
target_include_directories(gl-graphics PRIVATE ${GLEW_INCLUDE_DIR} ${glfw3_INCLUDE_DIR})
set(LINK_TARGETS ${LINK_TARGETS} gl-graphics OpenGL32 glew32 glfw3 m PARENT_SCOPE)
target_link_libraries(gl-graphics core-graphics)