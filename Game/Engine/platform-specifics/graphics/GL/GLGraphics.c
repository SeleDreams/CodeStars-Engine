#include "GLGraphics.h"
#include <stdlib.h>
#include <stdio.h>
#include "GLFWFunctions.h"
#include <core/graphics/Mesh.h>
#include <string.h>

void csGraphicsContextSetTargetFramerate(csGraphicsContext *context, int framerate)
{
    context->framerate = framerate + 1;
}

int csGraphicsContextGetTargetFramerate(const csGraphicsContext *context)
{
    return context->framerate;
}

float csGraphicsContextGetDelta(const csGraphicsContext *context)
{
    return context->delta;
}
