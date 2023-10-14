#include <stdio.h>
#include <stdlib.h>
#include "SDLFunctions.h"
#include "GLGraphics.h"
#include <math.h>
#include <time.h>
#include <assert.h>

static const csGraphicsContextImpl csGLGraphicsContextImpl = {
    .Create = csSDLGraphicsContextCreate,
    .Destroy = csSDLGraphicsContextDestroy,
    .GetDelta = csGLGraphicsContextGetDelta,
    .SetTargetFramerate = csGLGraphicsContextSetTargetFramerate,
    .GetTargetFramerate = csGLGraphicsContextGetTargetFramerate,
    .FrameStart = csSDLGraphicsFrameStart,
    .FrameEnd = csSDLGraphicsFrameEnd,
    .Update = csSDLGraphicsUpdate
};

int csSDLGraphicsCreateWindow(csGraphicsContext context, unsigned int width, unsigned int height, const char *name)
{
    if (!context)
    {
        printf("The context provided is null, cannot create new window\n");
        return 1;
    }

    csGraphicsWindow *window = malloc(sizeof(csGraphicsWindow));
    
    window->window = SDL_CreateWindow(name,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    window->height = height;
    window->width = width;
    window->name = name;
    window->glContext = SDL_GL_CreateContext(window->window);
    assert(window->glContext != NULL);
    window->renderer = SDL_CreateRenderer(window->window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

    SDL_GL_GetDrawableSize(window->window,&window->buffer_width,&window->buffer_height);
    if (!window || !window->window)
    {
        printf("An error occurred while creating the SDL window! : %s\n",SDL_GetError());
        return 2;
    }
    ((csGLGraphicsContext*)context)->window_count += 1;
    ((csGLGraphicsContext*)context)->windows = realloc(((csGLGraphicsContext*)context)->windows, (int)sizeof(csGraphicsWindow) * ((csGLGraphicsContext*)context)->window_count);
    if (((csGLGraphicsContext*)context)->windows == NULL)
    {
        printf("An error occurred when calling realloc\n");
        return 3;
    }
    ((csGLGraphicsContext*)context)->windows[((csGLGraphicsContext*)context)->window_count - 1] = window;
    return 0;
}

int csSDLGraphicsRemoveWindow(csGraphicsContext context, int window_id)
{
    if (!context)
    {
        printf("The context provided is null, cannot create new window\n");
        return 1;
    }
    if (window_id >= ((csGLGraphicsContext*)context)->window_count)
    {
        printf("The window ID cannot be greater than the windows count\n");
        return 2;
    }
    csGraphicsWindow *window = ((csGLGraphicsContext*)context)->windows[window_id];
    if (!window)
    {
        printf("The window cannot be null!\n");
        return 3;
    }
    SDL_DestroyWindow(window->window);
    SDL_GL_DeleteContext(window->glContext);
    SDL_DestroyRenderer(window->renderer);
    free(window);
    ((csGLGraphicsContext*)context)->window_count -= 1;
    ((csGLGraphicsContext*)context)->windows[window_id] = ((csGLGraphicsContext*)context)->windows[((csGLGraphicsContext*)context)->window_count];
    ((csGLGraphicsContext*)context)->windows = realloc(((csGLGraphicsContext*)context)->windows, sizeof(csGraphicsWindow *) * ((csGLGraphicsContext*)context)->window_count);
    printf("Window %i successfully freed, the new window count is %i!\n", window_id, ((csGLGraphicsContext*)context)->window_count);
    return 0;
}

int csSDLGraphicsCreate(csGraphicsContext context, unsigned int width, unsigned int height, const char *name)
{
    if (!context)
    {
        printf("The context provided is null\n");
        return 1;
    }
    SDL_SetMainReady();
    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetHint(SDL_HINT_OPENGL_ES_DRIVER, "1");
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    ((csGLGraphicsContext*)context)->window_count = 0;
    ((csGLGraphicsContext*)context)->main_window = 0;
    ((csGLGraphicsContext*)context)->windows = NULL;
    ((csGLGraphicsContext*)context)->framerate = 60;

    int window = csSDLGraphicsCreateWindow(context, width, height, name);
    if (window)
    {
        SDL_Quit();
        printf("An error occurred while creating the SDL window!\n");
        return 3;
    }
    SDL_GL_MakeCurrent(((csGLGraphicsContext*)context)->windows[0]->window,((csGLGraphicsContext*)context)->windows[0]->glContext);
    assert(SDL_GL_GetCurrentContext() != NULL);
    //printf("SDL2 version : %s\n",SDL_VERSION);
    printf("gl version : %s\n",glGetString(GL_VERSION));
    return 0;
}

void csSDLGraphicsTerminate(csGraphicsContext context)
{
    if (context)
    {
        if (((csGLGraphicsContext*)context)->window_count > 0)
        {

            for (int i = ((csGLGraphicsContext*)context)->window_count - 1; i >= 0; i--)
            {
                csSDLGraphicsRemoveWindow(context, i);
            }
        }
        free(context);
        context = NULL;
        printf("freed context\n");
    }
    SDL_Quit();
    printf("Terminated SDL\n");
}

void csSDLGraphicsFrameStart(csGraphicsContext context)
{
    for (int i = 0; i < ((csGLGraphicsContext*)context)->window_count; i++)
    {
        SDL_GL_MakeCurrent(((csGLGraphicsContext*)context)->windows[i]->window,((csGLGraphicsContext*)context)->windows[i]->glContext);
    }
    csGraphicsWindow *current_window = ((csGLGraphicsContext*)context)->windows[((csGLGraphicsContext*)context)->main_window];
    SDL_GL_MakeCurrent(current_window->window,current_window->glContext);
    glViewport(0,0,current_window->buffer_width,current_window->buffer_height);
    glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void csSDLGraphicsFrameEnd(csGraphicsContext context)
{
    for (int i = 0; i < ((csGLGraphicsContext*)context)->window_count; i++)
    {
        SDL_GL_SwapWindow(((csGLGraphicsContext*)context)->windows[i]->window);
    }
}

int csSDLGraphicsUpdate(csGraphicsContext context)
{
    if (!context)
    {
        printf("The graphics context provided to csGraphicsUpdate is null!\n");
        return 0;
    }
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT){
            for (int i = 0;i < ((csGLGraphicsContext*)context)->window_count;i++)
            {
                csSDLGraphicsRemoveWindow(context,i);
            }
            return 0;
        }
    }
        return 1;
}

void csSDLGraphicsContextDestroy(csGraphicsContext *context)
{
    if (*context)
    {
        csSDLGraphicsTerminate(*context);
    }
    *context = NULL;
}
void csGLGraphicsInit(void)
{
    csGraphicsInit(&csGLGraphicsContextImpl);
}

int csSDLGraphicsContextCreate(csGraphicsContext *context, int width, int height, const char *name)
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
    *context = malloc(sizeof(csGLGraphicsContext));
    if (!*context)
    {
        printf("context is null after allocation, something's wrong!\n");
        return 2;
    }
    printf("Initialized context\n");
    if (csSDLGraphicsCreate(*context, width, height, name))
    {
        printf("An error occurred while initializing SDL\n");
        return 3;
    }
    printf("Initialized SDL\n");
    initialized = 1;
    return 0;
}