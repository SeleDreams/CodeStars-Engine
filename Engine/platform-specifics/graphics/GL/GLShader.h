#ifndef CS_GLSHADER_H
#define CS_GLSHADER_H
#include "GLGraphics.h"
#include <spirv_cross/spirv_cross_c.h>
typedef struct glShader{
    GLuint uModelTransform;
    GLuint program;
} glShader;
#endif