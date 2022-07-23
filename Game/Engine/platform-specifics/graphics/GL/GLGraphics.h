#ifndef CS_GLGRAPHICS_H
#define CS_GLGRAPHICS_H
#include <core/graphics/Graphics.h>
struct {
    unsigned int window_count;
    void **windows;
    int main_window;
} typedef csGLGraphicsContext;
int csGLGraphicsInitGLFW(csGLGraphicsContext *context, int width, int height, const char *name);
int csGLGraphicsInitGLEW(csGLGraphicsContext *context);

#endif