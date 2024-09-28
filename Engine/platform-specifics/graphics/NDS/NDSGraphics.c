#include <core/graphics/Mesh.h>
#include "NDSGraphics.h"

void csNDSGraphicsContextSetTargetFramerate(csGraphicsContext *context, int framerate)
{
    ((csNDSGraphicsContext*)context)->framerate = framerate;
}

int csNDSGraphicsContextGetTargetFramerate(const csGraphicsContext *context)
{
    return ((csNDSGraphicsContext*)context)->framerate;
}

float csNDSGraphicsContextGetDelta(const csGraphicsContext *context)
{
    return ((csNDSGraphicsContext*)context)->delta;
}
