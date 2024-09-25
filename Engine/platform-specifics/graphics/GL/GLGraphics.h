#ifndef CS_GLGRAPHICS_H
#define CS_GLGRAPHICS_H
#include <core/graphics/Graphics.h>
#include <gles/gl.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
typedef struct csGraphicsWindow
{
    void *window;
    void *glContext;
    void *renderer;
    int width;
    int height;
    int buffer_width;
    int buffer_height;
    const char *name;

} csGraphicsWindow;

typedef struct csGLGraphicsContext
{
    csGraphicsWindow **windows;
    int window_count;
    int main_window;
    int framerate;
    float delta;
} csGLGraphicsContext;

void csGLGraphicsInit(void);
void csGLGraphicsContextSetTargetFramerate(csGraphicsContext *context, int framerate);
int csGLGraphicsContextGetTargetFramerate(const csGraphicsContext *context);
float csGLGraphicsContextGetDelta(const csGraphicsContext *context);
#endif
