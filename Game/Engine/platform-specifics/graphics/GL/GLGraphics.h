#ifndef CS_GLGRAPHICS_H
#define CS_GLGRAPHICS_H
#include <core/graphics/Graphics.h>
#include <GL/glew.h>
struct csGraphicsWindow
{
    void *window;
    int width;
    int height;
    int buffer_width;
    int buffer_height;
    const char *name;

} typedef csGraphicsWindow;
struct csGraphicsContext
{
    csGraphicsWindow **windows;
    unsigned int window_count;
    int main_window;
    int framerate;
} typedef csGraphicsContext;

int csGLGraphicsInitGLEW();
int csGLGraphicsLoadShader(csGraphicsContext *context, const char *shader_data, GLenum shader_type, unsigned int *output);
int csGLCreateShaderProgram(GLuint *output);
#endif