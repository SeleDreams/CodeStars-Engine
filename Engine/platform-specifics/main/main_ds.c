#include "main.h"
#include <nds.h>
#include <core/memory/pool_allocator.h>
#include <platform-specifics/graphics/DS/DSGraphics.h>
#include <core/graphics/Mesh.h>
int csMain(const csStartupInfos *infos)
{
    csMemPoolAllocatorInit(&csMemPoolAllocatorGlobal,8);
    csDSGraphicsInit();
    csGraphicsContext context = NULL;
    if (csDSGraphicsContextCreate(&context,SCREEN_WIDTH - 1,SCREEN_HEIGHT - 1,"Code Stars"))
    {
        nocashMessage("An error occurred while initializing the graphics context\n");
        return 1;
    }
    
    csMesh *mesh = NULL;
    csMeshCreatePrimitiveTriangle(&mesh);
    const int framerate = 60;
    csGraphicsContextSetTargetFramerate(context,framerate);
    while (csGraphicsUpdate(context))
    {
        csGraphicsFrameStart(context);
        csMeshDraw(mesh,NULL);
        csGraphicsFrameEnd(context);
        csGraphicsWaitForNextFrame(framerate);
    }
    csGraphicsContextDestroy(&context);
    csMeshFree(mesh);
    while(true){};
    return 0;
};