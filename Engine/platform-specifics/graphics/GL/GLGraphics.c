#include "GLGraphics.h"
#include "GLFWFunctions.h"
#include <core/graphics/Mesh.h>

void csGLGraphicsContextSetTargetFramerate(csGraphicsContext context, int framerate)
{
    ((csGLGraphicsContext*)context)->framerate = framerate + 1;
}

int csGLGraphicsContextGetTargetFramerate(const csGraphicsContext context)
{
    return ((csGLGraphicsContext*)context)->framerate;
}

float csGLGraphicsContextGetDelta(const csGraphicsContext context)
{
    return ((csGLGraphicsContext*)context)->delta;
}
