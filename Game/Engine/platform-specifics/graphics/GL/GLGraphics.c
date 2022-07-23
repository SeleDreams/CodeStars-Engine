#include "GLGraphics.h"
#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int csGLGraphicsInitGLFW(csGLGraphicsContext *context)
{
    if (!context)
    {
        printf("The context provided to GLUT is null, the allocation might have failed\n");
        return 1;
    }

    if (!glfwInit())
    {
        printf("An error occurred while initializing glfw !\n");
        return 2;
    }
    GLFWwindow *window = glfwCreateWindow(800, 600, "", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        printf("An error occurred while creating the GLFW window!");
        return 3;
    }
    context->window_count = 1;
    context->windows = malloc(sizeof(GLFWwindow *));
    context->windows[0] = window;
    glfwMakeContextCurrent(window);
    return 0;
}

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

int csGraphicsContextInit(csGraphicsContext *context)
{
    if (!context)
    {
        printf("The graphics context provided to csGraphicsContextInit is null!\n");
        return 1;
    }
    *context = malloc(sizeof(csGLGraphicsContext));
    if (csGLGraphicsInitGLFW((csGLGraphicsContext *)*context))
    {
        printf("An error occurred while initializing GLFW\n");
        return 2;
    }
    if (csGLGraphicsInitGLEW((csGLGraphicsContext *)*context))
    {
        printf("An error occurred while initializing GLEW\n");
        return 3;
    }
    return 0;
}

int csGraphicsContextTerminate(csGraphicsContext *context)
{
    if (context)
    {
        csGLGraphicsContext *gl_context = (csGLGraphicsContext *)*context;

        if (gl_context)
        {
            if (gl_context->windows)
            {
                free(gl_context->windows);
                gl_context->windows = NULL;
            }
            free(gl_context);
            gl_context = NULL;
        }
    }
    glfwTerminate();
    return 0;
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
    glfwSwapBuffers(gl_context->windows[0]);
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
    while (!glfwWindowShouldClose(gl_context->windows[0]))
    {
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
