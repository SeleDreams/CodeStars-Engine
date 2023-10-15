list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
if (WIN32)
option(USE_GL "Build the OpenGL section of the engine" ON)
option(USE_GLEW "Use GLEW to load gles2 natively on the GPU, else ANGLE is used" ON)
option(USE_SDL "Use SDL for windows" ON)
endif()