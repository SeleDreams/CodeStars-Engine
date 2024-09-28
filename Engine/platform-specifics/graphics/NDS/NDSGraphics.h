#ifndef CS_GLGRAPHICS_H
#define CS_GLGRAPHICS_H
#include <core/graphics/Graphics.h>
#include <nds.h>
typedef struct csGraphicsWindow
{
    unsigned int screen;
    int width;
    int height;
    const char *name;

} csGraphicsWindow;

typedef struct csNDSGraphicsContext
{
    int framerate;
    float delta;
} csNDSGraphicsContext;

void csNDSGraphicsContextSetTargetFramerate(csGraphicsContext *context, int framerate);
int csNDSGraphicsContextGetTargetFramerate(const csGraphicsContext *context);
float csNDSGraphicsContextGetDelta(const csGraphicsContext *context);
#endif
