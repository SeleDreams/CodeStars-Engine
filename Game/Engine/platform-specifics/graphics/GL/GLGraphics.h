#ifndef CS_GLGRAPHICS_H
#define CS_GLGRAPHICS_H
#include <core/graphics/Graphics.h>
struct {
    unsigned int window_count;
    void **windows;
} typedef csGLGraphicsContext;
int csGLGraphicsInitGLFW(csGLGraphicsContext *context);
int csGLGraphicsInitGLEW(csGLGraphicsContext *context);

#endif