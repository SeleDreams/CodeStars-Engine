#ifndef CODESTARS_DS_GRAPHICS_H
#define CODESTARS_DS_GRAPHICS_H
#include <core/graphics/Graphics.h>
#include <core/maths/includes.h>
typedef enum csDSScreenFlags {
    IS_PRIMARY_SCREEN
} csDSScreenFlags;

typedef struct csGraphicsWindow {
    unsigned int id;
    csDSScreenFlags flags;
    unsigned int width;
    unsigned int height;
} csGraphicsWindow;

typedef struct csDSGraphicsContext
{
    csGraphicsWindow **windows;
    unsigned int window_count;
    unsigned int main_window;
    unsigned int framerate;
    csFixed delta;
} csDSGraphicsContext;
int csDSGraphicsContextCreate(csGraphicsContext *context, int width, int height, const char *name);
void csDSGraphicsContextDestroy(csGraphicsContext *context);
int csDSGraphicsRemoveWindow(csGraphicsContext context, int window_id);
int csDSGraphicsCreateWindow(csGraphicsContext context, unsigned int width, unsigned int height, const char *name);
int csDSGraphicsCreate(csGraphicsContext context, unsigned int width, unsigned int height, const char *name);
void csDSGraphicsTerminate(csGraphicsContext context);
void csDSGraphicsFrameStart(csGraphicsContext context);
void csDSGraphicsFrameEnd(csGraphicsContext context);
int csDSGraphicsUpdate(csGraphicsContext context);
void csDSGraphicsInit(void);
void csDSGraphicsContextSetTargetFramerate(csGraphicsContext context, int framerate);
int csDSGraphicsContextGetTargetFramerate(const csGraphicsContext context);
float csDSGraphicsContextGetDelta(const csGraphicsContext context);
#endif