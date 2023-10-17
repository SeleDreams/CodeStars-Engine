#ifndef CS_GLSHADER_H
#define CS_GLSHADER_H
#include "GLGraphics.h"
#include <spirv_cross/spirv_cross_c.h>
typedef struct glShader{
    GLint uModelTransform;
    GLint uProjection;
    GLuint program;
} glShader;
#endif