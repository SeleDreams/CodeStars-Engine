#include "Graphics.h"
#include <time.h>
#include <assert.h>

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
csFixed delta;

csFixed csGetDeltaTime(void) {
    return delta;
}

csFixed csGraphicsWaitForNextFrame(int framerate)
{
    delta = csGetSystemDeltaTime();
    csFixed interval = csGetTimeInterval(framerate);
    while (delta < interval)
    {
        delta += csGetSystemDeltaTime();
    }
    return  delta;
}

