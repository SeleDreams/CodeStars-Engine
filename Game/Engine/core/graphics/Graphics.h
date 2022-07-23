#ifndef CS_GRAPHICS_H
#define CS_GRAPHICS_H
typedef void *csGraphicsContext;
typedef void *csGraphicsWindow;

//int csGraphicsCreateWindow(csGraphicsWindow *window, int width, int height, const char *name);
int csGraphicsContextInit(csGraphicsContext *context, int width, int height, const char *name);
int csGraphicsContextTerminate(csGraphicsContext *context);
int csGraphicsFrameStart(csGraphicsContext *context);
int csGraphicsFrameEnd(csGraphicsContext *context);
int csGraphicsMainLoop(csGraphicsContext *context);
#endif