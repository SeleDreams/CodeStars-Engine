#include "GLGraphics.h"
#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include "GLFWFunctions.h"

int csGLGraphicsInitGLEW(csGLGraphicsContext *context)
{
    if (!context)
    {
        printf("The context provided to glew is null, the allocation might have failed\n");
        return 1;
    }
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        return 2;
    }

    return 0;
}

int csGraphicsContextInit(csGraphicsContext *context, int width, int height, const char *name)
{
    if (!context)
    {
        printf("The graphics context provided to csGraphicsContextInit is null!\n");
        return 1;
    }
    *context = malloc(sizeof(csGLGraphicsContext));
    printf("Initialized context\n");
    if (csGLGraphicsInitGLFW((csGLGraphicsContext *)*context, width, height, name))
    {
        printf("An error occurred while initializing GLFW\n");
        return 2;
    }
    printf("Initialized GLFW\n");
    if (csGLGraphicsInitGLEW((csGLGraphicsContext *)*context))
    {
        printf("An error occurred while initializing GLEW\n");
        return 3;
    }
    printf("Initialized GLEW\n");
    return 0;
}

int csGraphicsContextTerminate(csGraphicsContext *context)
{
    if (context)
    {
        return csGLGraphicsTerminateGLFW(*context);
    }
}

int csGraphicsFrameStart(csGraphicsContext *context)
{
    if (!context)
    {
        printf("The graphics context provided to csGraphicsFrameStart is null!");
        return 1;
    }
    csGLGraphicsContext *gl_context = (csGLGraphicsContext *)*context;
    for (int i = 0; i < gl_context->window_count; i++)
    {
        glfwMakeContextCurrent(gl_context->windows[i]);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    glfwMakeContextCurrent(gl_context->windows[0]);
    return 0;
}

int csGraphicsFrameEnd(csGraphicsContext *context)
{
    if (!context)
    {
        printf("The graphics context provided to csGraphicsFrameStart is null!");
        return 1;
    }
    csGLGraphicsContext *gl_context = (csGLGraphicsContext *)*context;
    for (int i = 0; i < gl_context->window_count; i++)
    {
        glfwSwapBuffers(gl_context->windows[i]);
    }
    glfwPollEvents();
    return 0;
}

int csGraphicsMainLoop(csGraphicsContext *context)
{
    if (!context)
    {
        printf("The graphics context provided to csGraphicsFrameStart is null!");
        return 1;
    }
    csGLGraphicsContext *gl_context = (csGLGraphicsContext *)*context;

    while (!glfwWindowShouldClose(gl_context->windows[gl_context->main_window]))
    {
        for (int i = 0; i < gl_context->window_count; i++)
        {
            if (glfwWindowShouldClose(gl_context->windows[i]))
            {
                csGLGraphicsRemoveWindow(gl_context, i);
            }
        }
        int result = csGraphicsFrameStart(context);
        if (result)
        {
            csGraphicsContextTerminate(context);
            return result;
        }
        result = csGraphicsFrameEnd(context);
        if (result)
        {
            csGraphicsContextTerminate(context);
            return result;
        }
    }
    csGraphicsContextTerminate(context);
    return 0;
}
