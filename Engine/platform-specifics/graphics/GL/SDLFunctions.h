#ifndef CS_SDLFUNCTIONS_H
#define CS_SDLFUNCTIONS_H 
#include "GLGraphics.h"
int csSDLGraphicsContextCreate(csGraphicsContext *context, int width, int height, const char *name);
void csSDLGraphicsContextDestroy(csGraphicsContext *context);
int csSDLGraphicsRemoveWindow(csGraphicsContext context,int window_id);
int csSDLGraphicsCreateWindow(csGraphicsContext context, unsigned int width,unsigned int height, const char *name);
int csSDLGraphicsCreate(csGraphicsContext context,unsigned int width, unsigned int height, const char *name);
void csSDLGraphicsTerminate(csGraphicsContext context);
void csSDLGraphicsFrameStart(csGraphicsContext context);
void csSDLGraphicsFrameEnd(csGraphicsContext context);
int csSDLGraphicsUpdate(csGraphicsContext context);
#endif