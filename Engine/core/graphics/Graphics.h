#ifndef CS_GRAPHICS_H
#define CS_GRAPHICS_H

typedef struct csGraphicsContext csGraphicsContext;
typedef struct Mesh Mesh;
int csGraphicsContextCreate(csGraphicsContext **context, int width, int height, const char *name);
void csGraphicsContextSetTargetFramerate(csGraphicsContext *context, int framerate);
void csGraphicsContextDestroy(csGraphicsContext **context);
float csGraphicsContextGetDelta(const csGraphicsContext *context);
int csGraphicsContextGetTargetFramerate(const csGraphicsContext *context);
void csGraphicsFrameStart(csGraphicsContext *context);
void csGraphicsFrameEnd(csGraphicsContext *context);
int csGraphicsUpdate(csGraphicsContext *context);
float csGraphicsWaitForNextFrame(int framerate);
#endif