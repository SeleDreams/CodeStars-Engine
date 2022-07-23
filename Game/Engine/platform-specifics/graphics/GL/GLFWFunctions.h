#ifndef CS_GLFWFUNCTIONS_H
#define CS_GLFWFUNCTIONS_H 
#include "GLGraphics.h"
int csGLGraphicsRemoveWindow(csGLGraphicsContext *context,int window_id);
int csGLGraphicsAddWindow(csGLGraphicsContext *context, int width, int height, const char *name);
int csGLGraphicsInitGLFW(csGLGraphicsContext *context, int width, int height, const char *name);
int csGLGraphicsTerminateGLFW(csGLGraphicsContext *context);
#endif