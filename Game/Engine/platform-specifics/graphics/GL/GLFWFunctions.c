#include <stdio.h>
#include <stdlib.h>
#include "GLFWFunctions.h"
#include "GLGraphics.h"
#include <GLFW/glfw3.h>
#include <math.h>
#include <time.h>

int csGLFWGraphicsCreateWindow(csGraphicsContext *context, unsigned int width, unsigned int height, const char *name)
{
    if (!context)
    {
        printf("The context provided is null, cannot create new window\n");
        return 1;
    }

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    csGraphicsWindow *window = malloc(sizeof(csGraphicsWindow));

    window->window = glfwCreateWindow(width, height, name, NULL, NULL);
    window->height = height;
    window->width = width;
    window->name = name;
    glfwGetFramebufferSize(window->window,&window->buffer_width,&window->buffer_height);
    glViewport(0,0, window->buffer_width,window->buffer_height);
    if (!window || !window->window)
    {
        printf("An error occurred while creating the GLFW window!\n");
        return 2;
    }
    context->window_count += 1;
    context->windows = realloc(context->windows, (int)sizeof(csGraphicsWindow) * context->window_count);
    if (context->windows == NULL)
    {
        printf("An error occurred when calling realloc\n");
        return 3;
    }
    context->windows[context->window_count - 1] = window;
    return 0;
}

int csGLFWGraphicsRemoveWindow(csGraphicsContext *context, unsigned int window_id)
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
    csGraphicsWindow *window = context->windows[window_id];
    if (!window)
    {
        printf("The window cannot be null!\n");
        return 3;
    }
    glfwDestroyWindow(window->window);
    free(window);
    context->window_count -= 1;
    context->windows[window_id] = context->windows[context->window_count];
    context->windows = realloc(context->windows, sizeof(csGraphicsWindow *) * context->window_count);
    printf("Window %i successfully freed, the new window count is %i!\n", window_id, context->window_count);
}

int csGLFWGraphicsInit(csGraphicsContext *context, unsigned int width, unsigned int height, const char *name)
{
    if (!context)
    {
        printf("The context provided to GLUT is null, the allocation might have failed\n");
        return 1;
    }
    glfwWindowHint(GLFW_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    if (!glfwInit())
    {
        printf("GLFW failed to init!\n");
        return 2;
    }

    context->window_count = 0;
    context->main_window = 0;
    context->windows = NULL;
    context->framerate = 60;
    
    int window = csGLFWGraphicsCreateWindow(context, width, height, name);
    if (window)
    {
        glfwTerminate();
        printf("An error occurred while creating the GLFW window!\n");
        return 3;
    }
    glfwMakeContextCurrent(context->windows[0]->window);
    return 0;
}

void csGLFWGraphicsTerminate(csGraphicsContext *context)
{
    if (context)
    {
        if (context->window_count > 0)
        {

            for (int i = context->window_count - 1; i >= 0; i--)
            {
                csGLFWGraphicsRemoveWindow(context, i);
            }
        }
        free(context);
        context = NULL;
        printf("freed context\n");
    }
    glfwTerminate();
    printf("Terminated GLFW\n");
}

void csGraphicsFrameStart(csGraphicsContext *context)
{
    for (int i = 0; i < context->window_count; i++)
    {
        glfwMakeContextCurrent(context->windows[i]->window);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    glfwMakeContextCurrent(context->windows[0]->window);
}

void csGraphicsFrameEnd(csGraphicsContext *context)
{
    for (int i = 0; i < context->window_count; i++)
    {
        glfwSwapBuffers(context->windows[i]->window);
    }
    glfwPollEvents();
    csGraphicsWaitForNextFrame(context->framerate);
}

int csGraphicsUpdate(csGraphicsContext *context)
{
    if (!context)
    {
        printf("The graphics context provided to csGraphicsUpdate is null!\n");
        return 0;
    }
    if (!glfwWindowShouldClose(context->windows[context->main_window]->window))
    {
        for (int i = 0; i < context->window_count; i++)
        {
            if (glfwWindowShouldClose(context->windows[i]->window))
            {
                csGLFWGraphicsRemoveWindow(context, i);
            }
        }
        return 1;
    }
    else
    {
        return 0;
    }
}

void csGraphicsContextDestroy(csGraphicsContext **context)
{
    if (*context)
    {
        csGLFWGraphicsTerminate(*context);
    }
    *context = NULL;
}

int csGraphicsContextCreate(csGraphicsContext **context, int width, int height, const char *name)
{
    static int initialized = 0;
    if (initialized)
    {
        printf("Attempted to initialize the context twice, this is not allowed\n");
        return 0;
    }
    if (*context)
    {
        printf("The graphics context provided to csGraphicsContextCreate isn't null! something's wrong\n");
        return 1;
    }
    *context = malloc(sizeof(csGraphicsContext));
    if (!*context)
    {
        printf("context is null after allocation, something's wrong!\n");
        return 2;
    }
    printf("Initialized context\n");
    if (csGLFWGraphicsInit(*context, width, height, name))
    {
        printf("An error occurred while initializing GLFW\n");
        return 3;
    }
    printf("Initialized GLFW\n");
    if (csGLGraphicsInitGLEW())
    {
        printf("An error occurred while initializing GLEW\n");
        return 4;
    }
    printf("Initialized GLEW\n");
    initialized = 1;
    return 0;
}