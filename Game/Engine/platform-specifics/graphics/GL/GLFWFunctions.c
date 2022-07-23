#include <stdio.h>
#include <stdlib.h>
#include "GLFWFunctions.h"
#include "GLGraphics.h"
#include <GLFW/glfw3.h>
#include <math.h>

int csGLGraphicsAddWindow(csGLGraphicsContext *context, int width, int height, const char *name)
{
    if (!context)
    {
        printf("The context provided is null, cannot create new window\n");
        return 1;
    }
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    GLFWwindow *window = glfwCreateWindow(width, height, name, NULL, NULL);
    if (!window)
    {
        printf("An error occurred while creating the GLFW window!\n");
        return 2;
    }
    context->window_count += 1;
    context->windows = realloc(context->windows, sizeof(GLFWwindow *) * context->window_count);
    if (context->windows == NULL)
    {
        printf("An error occurred when calling realloc\n");
        return 3;
    }
    context->windows[context->window_count - 1] = window;
    return 0;
}

int csGLGraphicsRemoveWindow(csGLGraphicsContext *context, int window_id)
{
    if (!context)
    {
        printf("The context provided is null, cannot create new window\n");
        return 1;
    }
    if (window_id >= context->window_count)
    {
        printf("The window ID cannot be greater than the windows count\n");
        return 2;
    }
    GLFWwindow *window = context->windows[window_id];
    if (!window)
    {
        printf("The window cannot be null!\n");
        return 3;
    }
    glfwDestroyWindow(window);
    context->window_count -= 1;
    context->windows[window_id] = context->windows[context->window_count];
    context->windows = realloc(context->windows, sizeof(GLFWwindow *) * context->window_count);
    printf("Window %i successfully freed, the new window count is %i!\n", window_id, context->window_count);
}


int csGLGraphicsInitGLFW(csGLGraphicsContext *context, int width, int height, const char *name)
{
    if (!context)
    {
        printf("The context provided to GLUT is null, the allocation might have failed\n");
        return 1;
    }

    if (!glfwInit())
    {
        printf("GLFW failed to init!\n");
        return 2;
    }
    int window = csGLGraphicsAddWindow(context, width, height, name);
    if (window)
    {
        glfwTerminate();
        printf("An error occurred while creating the GLFW window!\n");
        return 3;
    }
    context->main_window = 0;
    glfwMakeContextCurrent(context->windows[0]);
    return 0;
}


int csGLGraphicsTerminateGLFW(csGLGraphicsContext *context)
{
    if (context)
    {
        if (context->window_count > 0)
        {
            for (int i = context->window_count - 1; i >= 0; i--)
            {
                csGLGraphicsRemoveWindow(context, i);
            }
        }
        free(context);
        context = NULL;
        printf("freed context\n");
    }
    glfwTerminate();
    printf("Terminated GLFW\n");
    return 0;
}