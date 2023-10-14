#include "Graphics.h"
#include <time.h>
#include <assert.h>

csGraphicsContextImpl backend;

void csGraphicsInit(const csGraphicsContextImpl *impl) {
    backend = *impl;
}

int csGraphicsContextCreate(csGraphicsContext *context, int width, int height, const char *name){
    assert(backend.Create);
    return backend.Create(context,width,height,name);
}

void csGraphicsContextDestroy(csGraphicsContext *context)
{
    assert(backend.Destroy);
    backend.Destroy(context);
}

void csGraphicsContextSetTargetFramerate(csGraphicsContext context, int framerate)
{
    assert(backend.SetTargetFramerate);
    backend.SetTargetFramerate(context,framerate);
}

int csGraphicsContextGetTargetFramerate(const csGraphicsContext context)
{
    assert(backend.GetTargetFramerate);
    return backend.GetTargetFramerate(context);
}

float csGraphicsContextGetDelta(const csGraphicsContext context) 
{
    assert(backend.GetDelta);
    return backend.GetDelta(context);
}

void csGraphicsFrameStart(csGraphicsContext context)
{
    assert(backend.FrameStart);
    backend.FrameStart(context);
}

void csGraphicsFrameEnd(csGraphicsContext context)
{
    assert(backend.FrameEnd);
    backend.FrameEnd(context);
}

int csGraphicsUpdate(csGraphicsContext context)
{
    assert(backend.Update);
    return backend.Update(context);
}

float csGraphicsWaitForNextFrame(int framerate)
{
    static float last_frame_seconds = 0;
    static float current_frame_seconds = 0;
    static float delta;

    delta = 0.0f;

    if (last_frame_seconds == 0)
    {
        last_frame_seconds = ((float)clock()) / CLOCKS_PER_SEC;
    }

    while (1.0 / delta >= framerate)
    {
        double current_frame_seconds = ((float)clock()) / CLOCKS_PER_SEC;
        delta = current_frame_seconds - last_frame_seconds;
    }
    last_frame_seconds = current_frame_seconds;
    return delta;
}