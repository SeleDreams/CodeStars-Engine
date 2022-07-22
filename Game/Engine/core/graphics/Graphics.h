#ifndef CS_GRAPHICS_H
#define CS_GRAPHICS_H
typedef void *csGraphicsContext;
int csGraphicsContextInit(csGraphicsContext *context);
int csGraphicsContextFree(csGraphicsContext *context);
#endif