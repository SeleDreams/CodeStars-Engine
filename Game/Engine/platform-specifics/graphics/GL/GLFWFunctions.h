#ifndef CS_GLFWFUNCTIONS_H
#define CS_GLFWFUNCTIONS_H 
#include "GLGraphics.h"
int csGLFWGraphicsRemoveWindow(csGraphicsContext *context,unsigned int window_id);
int csGLFWGraphicsCreateWindow(csGraphicsContext *context, unsigned int width,unsigned int height, const char *name);
int csGLFWGraphicsInit(csGraphicsContext *context,unsigned int width, unsigned int height, const char *name);
void csGLFWGraphicsTerminate(csGraphicsContext *context);
#endif