#ifndef CS_GLGRAPHICS_H
#define CS_GLGRAPHICS_H
#include <core/graphics/Graphics.h>
struct {
    int window_count;
    void **windows;
    int main_window;
} typedef csGLGraphicsContext;
int csGLGraphicsInitGLEW(csGLGraphicsContext *context);

#endif