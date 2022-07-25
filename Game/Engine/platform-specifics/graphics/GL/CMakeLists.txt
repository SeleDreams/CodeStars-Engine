find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
add_library(gl-graphics
GLGraphics.c
GLShader.c
GLMesh.c
GLFWFunctions.c
)
if(WIN32)
set(glew_lib glew32)
set(glfw_lib glfw3)
else()
set(glew_lib GLEW)
set(glfw_lib glfw)
endif()

set(LINK_TARGETS ${LINK_TARGETS} gl-graphics ${glfw_lib} ${glew_lib} ${OPENGL_LIBRARIES} m PARENT_SCOPE)
target_link_libraries(gl-graphics core-graphics)