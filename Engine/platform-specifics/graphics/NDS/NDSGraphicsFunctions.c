#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "core/memory/pool_allocator.h"
#include <nds.h>
#include "NDSGraphicsFunctions.h"
#include "NDSGraphics.h"

static const csGraphicsContextImpl csGLGraphicsContextImpl = {
    .Create = csNDSGraphicsContextCreate,
    .Destroy = csNDSGraphicsContextDestroy,
    .GetDelta = csNDSGraphicsContextGetDelta,
    .SetTargetFramerate = csNDSGraphicsContextSetTargetFramerate,
    .GetTargetFramerate = csNDSGraphicsContextGetTargetFramerate,
    .FrameStart = csNDSGraphicsFrameStart,
    .FrameEnd = csNDSGraphicsFrameEnd,
    .Update = csNDSGraphicsUpdate
};

int csNDSGraphicsCreateWindow(csGraphicsContext *context, unsigned int width, unsigned int height, const char *name)
{
    if (context == NULL)
    {
        printf("The context provided is null, cannot create new window\n");
        return 1;
    }


    return 0;
}

void csNDSGraphicsWindowDestroy(csGraphicsWindow *window) {
    csFree(window,sizeof(csGraphicsWindow));
}

int csNDSGraphicsRemoveWindow(csGraphicsContext *context, int window_id)
{
    return 0;
}

int csNDSGraphicsCreate(csGraphicsContext *context, unsigned int width, unsigned int height, const char *name)
{
    if (context == NULL)
    {
        printf("The context provided is null\n");
        return 1;
    }
    //put 3D on top
    lcdMainOnTop();

    //setup the sub screen for basic printing
    consoleDemoInit();

    // Setup the Main screen for 3D
    videoSetMode(MODE_0_3D);

    // initialize gl
    glInit();

    // enable antialiasing
    glEnable(GL_ANTIALIAS);

    // setup the rear plane
    glClearColor(10,10,25,31); // BG must be opaque for AA to work
    glClearPolyID(63); // BG must have a unique polygon ID for AA to work
    glClearDepth(0x7FFF);
    glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE);
    // Set our view port to be the same size as the screen
    glViewport(0,0,255,191);
    return 0;
}

void csNDSGraphicsTerminate(csGraphicsContext *context)
{
    if (context)
    {

        csFree(context,sizeof(csNDSGraphicsContext));
        context = NULL;
        printf("freed context\n");
    }
    

    printf("Terminated NDS\n");
}

void csNDSGraphicsFrameStart(csGraphicsContext *context)
{
    //printf("frame start\n");

}

void csNDSGraphicsFrameEnd(csGraphicsContext *context)
{

}

int csNDSGraphicsUpdate(csGraphicsContext *context)
{
    if (context == NULL)
    {
        printf("The graphics context provided to csGraphicsUpdate is null!\n");
        return 0;
    }
    scanKeys();
    int keys = keysDown();
    return !(keys & KEY_START);
}

void csNDSGraphicsContextDestroy(csGraphicsContext *context)
{
    if (context)
    {
        csNDSGraphicsTerminate(context);
    }
    context = NULL;
}

int csNDSGraphicsInit(void)
{
    csGraphicsInit(&csGLGraphicsContextImpl);
    return 0;
}

int csNDSGraphicsContextCreate(csGraphicsContext **context, int width, int height, const char *name)
{
    static int initialized = 0;
    if (context == NULL) {
        printf("The context pointer reference provided is null\n");
        return 1;
    }
    if (initialized)
    {
        printf("Attempted to initialize the context twice, this is not allowed\n");
        return 1;
    }
    if (*context)
    {
        printf("The graphics context provided to csGraphicsContextCreate isn't null! something's wrong\n");
        return 1;
    }
    *context = csMalloc(sizeof(csNDSGraphicsContext));
    if (*context == NULL)
    {
        printf("context is null after allocation, something's wrong!\n");
        return 2;
    }
    printf("Initialized context\n");
    if (csNDSGraphicsCreate(*context, width, height, name))
    {
        printf("An error occurred while initializing NDS\n");
        return 3;
    }
    printf("Initialized NDS\n");
    initialized = 1;
    return 0;
}