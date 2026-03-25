#include "DSGraphics.h"
#include <core/memory/pool_allocator.h>
#include <nds.h>

static const csGraphicsContextImpl csDSGraphicsContextImpl = {
    .Create = csDSGraphicsContextCreate,
    .Destroy = csDSGraphicsContextDestroy,
    .GetDelta = csDSGraphicsContextGetDelta,
    .SetTargetFramerate = csDSGraphicsContextSetTargetFramerate,
    .GetTargetFramerate = csDSGraphicsContextGetTargetFramerate,
    .FrameStart = csDSGraphicsFrameStart,
    .FrameEnd = csDSGraphicsFrameEnd,
    .Update = csDSGraphicsUpdate
};

int csDSGraphicsCreate(csGraphicsContext context, unsigned int width, unsigned int height, const char *name)
{
    if (!context)
    {
        nocashMessage("The context provided is null\n");
        return 1;
    }
    
    ((csDSGraphicsContext*)context)->main_window = 0;
    ((csDSGraphicsContext*)context)->windows = NULL;
    ((csDSGraphicsContext*)context)->framerate = 60;
    ((csDSGraphicsContext*)context)->window_count = 1;

    lcdMainOnTop();
    videoSetMode(MODE_0_3D);
    glInit();
    glViewport(0,0,width,height);
    return 0;
}

void csDSGraphicsContextDestroy(csGraphicsContext *context)
{
    csFree(context,sizeof(csDSGraphicsContext));
}

int csDSGraphicsContextCreate(csGraphicsContext *context, int width, int height, const char *name)
{
    static int initialized = 0;
    if (initialized)
    {
        nocashMessage("Attempted to initialize the context twice, this is not allowed\n");
        return 0;
    }
    if (*context)
    {
        nocashMessage("The graphics context provided to csGraphicsContextCreate isn't null! something's wrong\n");
        return 1;
    }
    *context = csMalloc(sizeof(csDSGraphicsContext));
    if (csDSGraphicsCreate(*context,width,height,name))
    {
        nocashMessage("An error occurred while initializing the DS's graphics\n");
    }
    nocashMessage("The context got initialized successfully!\n");
    initialized = 1;
    return 0;
}

void csDSGraphicsFrameStart(csGraphicsContext context)
{
    glClearColor(0,0,0,31);
    
}

void csDSGraphicsFrameEnd(csGraphicsContext context)
{
    glFlush(0);
}

int csDSGraphicsUpdate(csGraphicsContext context)
{
    if (!context)
    {
        nocashMessage("The graphics context provided to csGraphicsUpdate is null!\n");
        return 0;
    }
    static touchPosition touchXY;
    scanKeys();
    touchRead(&touchXY);
    if (keysDown() & KEY_START)
    {
        nocashMessage("Start key pressed. Exiting...\n");
        return 0;
    }
    return 1;
}

void csDSGraphicsInit(void)
{
    csGraphicsInit(&csDSGraphicsContextImpl);
}

void csDSGraphicsContextSetTargetFramerate(csGraphicsContext context, int framerate)
{

}
int csDSGraphicsContextGetTargetFramerate(const csGraphicsContext context)
{
    return 60;
}

float csDSGraphicsContextGetDelta(const csGraphicsContext context)
{
    return ((csDSGraphicsContext*)context)->delta;
}