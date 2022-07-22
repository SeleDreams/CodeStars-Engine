#include "GLGraphics.h"
#include <stdlib.h>

int csGraphicsContextInit(csGraphicsContext *context)
{
    if (!context)
    {
        return 1;
    }
    *context = malloc(sizeof(csGLGraphicsContext));
    return *context == NULL;
}

int csGraphicsContextFree(csGraphicsContext *context)
{
    if (!context)
    {
        return 1;
    }
    csGLGraphicsContext *glContext = (csGLGraphicsContext*)*context;
    free(glContext);
    *context = NULL;
    return 0;
}