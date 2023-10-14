#ifndef CS_GRAPHICS_H
#define CS_GRAPHICS_H

typedef void* csGraphicsContext;

typedef struct csGraphicsContextImpl {
     int (*Create)(csGraphicsContext *context, int width, int height, const char *name);
    void (*SetTargetFramerate)(csGraphicsContext context, int framerate);
    void (*Destroy)(csGraphicsContext *context);
    float (*GetDelta)(const csGraphicsContext context);
    int (*GetTargetFramerate)(const csGraphicsContext context);
    void (*FrameStart)(csGraphicsContext context);
    void (*FrameEnd)(csGraphicsContext context);
    int (*Update)(csGraphicsContext context);
} csGraphicsContextImpl;

typedef struct Mesh Mesh;


void csGraphicsInit(const csGraphicsContextImpl *impl);
float csGraphicsWaitForNextFrame(int framerate);

int csGraphicsContextCreate(csGraphicsContext *context, int width, int height, const char *name);
void csGraphicsContextDestroy(csGraphicsContext *context);

void csGraphicsContextSetTargetFramerate(csGraphicsContext context, int framerate);
int csGraphicsContextGetTargetFramerate(const csGraphicsContext context);

float csGraphicsContextGetDelta(const csGraphicsContext context);
void csGraphicsFrameStart(csGraphicsContext context);
void csGraphicsFrameEnd(csGraphicsContext context);
int csGraphicsUpdate(csGraphicsContext context);
float csGraphicsWaitForNextFrame(int framerate);
#endif
