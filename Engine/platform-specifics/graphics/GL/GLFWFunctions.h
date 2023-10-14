#ifndef CS_GLFWFUNCTIONS_H
#define CS_GLFWFUNCTIONS_H 
#include "GLGraphics.h"
int csGLFWGraphicsContextCreate(csGraphicsContext *context, int width, int height, const char *name);
void csGLFWGraphicsContextDestroy(csGraphicsContext *context);
int csGLFWGraphicsRemoveWindow(csGraphicsContext context,int window_id);
int csGLFWGraphicsCreateWindow(csGraphicsContext context, unsigned int width,unsigned int height, const char *name);
int csGLFWGraphicsCreate(csGraphicsContext context,unsigned int width, unsigned int height, const char *name);
void csGLFWGraphicsTerminate(csGraphicsContext context);
void csGLFWGraphicsFrameStart(csGraphicsContext context);
void csGLFWGraphicsFrameEnd(csGraphicsContext context);
int csGLFWGraphicsUpdate(csGraphicsContext context);
#endif