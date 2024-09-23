#include "Graphics.h"
#include <time.h>
#include <assert.h>
#include "../maths/includes.h"
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

csFixed csGraphicsWaitForNextFrame(int framerate)
{
    static csFixed last_frame_seconds = 0;
    static csFixed current_frame_seconds = 0;
    static csFixed delta;
    static const csFixed CLOCKS_PER_SEC_FIXED = CLOCKS_PER_SEC * fix16_one;
    static int clk;

    delta = csFixedFromFloat(0.001);

    if (last_frame_seconds == 0)
    {
        clk = clock();
        last_frame_seconds = csFixedDiv(csFixedFromInt(clk)  ,CLOCKS_PER_SEC_FIXED);
    }

    while (csFixedToInt(csFixedDiv(1 << 16, delta)) > framerate)
    {
        clk = clock();
        current_frame_seconds = csFixedDiv(csFixedFromInt(clk) ,CLOCKS_PER_SEC_FIXED);
        delta = current_frame_seconds - last_frame_seconds;
        if (delta == 0) {
            delta = csFixedFromFloat(0.0001);
        }
    }
    last_frame_seconds = current_frame_seconds;
    return delta;
}