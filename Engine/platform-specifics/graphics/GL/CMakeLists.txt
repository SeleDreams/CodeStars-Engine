
if(USE_SDL)
add_compile_definitions(USE_SDL)
find_package(SDL2 REQUIRED)
endif()

add_library(gl-graphics
GLGraphics.c
GLShader.c
GLMesh.c
GLFWFunctions.c
)
target_include_directories(gl-graphics PRIVATE ${PROJECT_SOURCE_DIR} ${SDL2_INCLUDE_DIRS})
target_link_libraries(gl-graphics core-graphics core-maths SDL2 EGL GLESv2)
target_link_libraries(${PLATFORM_SPECIFICS}_graphics INTERFACE gl-graphics)