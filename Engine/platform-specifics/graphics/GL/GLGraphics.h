#ifndef CS_GLGRAPHICS_H
#define CS_GLGRAPHICS_H
#include <core/graphics/Graphics.h>
#include <GL/glew.h>
typedef struct csGraphicsWindow
{
    void *window;
    int width;
    int height;
    int buffer_width;
    int buffer_height;
    const char *name;

} csGraphicsWindow;

typedef struct csGraphicsContext
{
    csGraphicsWindow **windows;
    int window_count;
    int main_window;
    int framerate;
    float delta;
} csGraphicsContext;


#endif