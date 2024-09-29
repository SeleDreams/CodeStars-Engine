#include "Graphics.h"
#include <time.h>
#include <assert.h>
#include <stdio.h>
#include "../os_functions.h"
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

void csGraphicsContextSetTargetFramerate(csGraphicsContext *context, int framerate)
{
    assert(backend.SetTargetFramerate);
    backend.SetTargetFramerate(context,framerate);
}

int csGraphicsContextGetTargetFramerate(const csGraphicsContext *context)
{
    assert(backend.GetTargetFramerate);
    return backend.GetTargetFramerate(context);
}

float csGraphicsContextGetDelta(const csGraphicsContext *context)
{
    assert(backend.GetDelta);
    return backend.GetDelta(context);
}

void csGraphicsFrameStart(csGraphicsContext *context)
{
    assert(backend.FrameStart);
    backend.FrameStart(context);
}

void csGraphicsFrameEnd(csGraphicsContext *context)
{
    assert(backend.FrameEnd);
    backend.FrameEnd(context);
}

int csGraphicsUpdate(csGraphicsContext *context)
{
    assert(backend.Update);
    return backend.Update(context);
}

csFixed csGraphicsWaitForNextFrame(int framerate)
{
#if __NDS__
    return csFixedFromFloat(0.0167f);
#else
    static clock_t last_frame_ticks = 0;
    clock_t current_frame_ticks = 0;
    csFixed delta = csFixedFromFloat(0.0);
    clock_t clk;
    if (last_frame_ticks == 0)
    {
        clk = clock();
        last_frame_ticks = clk;
    }
    const csFixed targetDelta = csFixedDiv(csFixedFromInt(CLOCKS_PER_SEC), csFixedFromInt(framerate));
    while (delta < targetDelta)
    {
        clk =  clock();

        current_frame_ticks = clk;
        uint32_t result = current_frame_ticks - last_frame_ticks;

        delta = csFixedFromInt(result);
    }
    last_frame_ticks = current_frame_ticks;
    return csFixedDiv(delta, csFixedFromInt(CLOCKS_PER_SEC));
#endif
}

