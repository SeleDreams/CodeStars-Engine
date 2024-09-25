#include <stdio.h>
#include <CodeStarsEngine.h>
#include <time.h>
#include <platform-specifics/graphics/GL/GLGraphics.h>

static csFixed delta;
int main(void)
{
    initMemoryPool(&csMemPoolAllocatorGlobal);
    //csMemPoolAllocatorInit(&csMemPoolAllocatorGlobal,8);
    csGLGraphicsInit();
    csGLGraphicsContext *context = NULL;
    if (csGraphicsContextCreate(&context, 1280, 720, "New Window"))
    {
        printf("An error occurred while initializing the graphics context\n");
        return 1;
    }
    csMesh *mesh = NULL;
    csMeshCreatePrimitivePyramid(&mesh);
    const int framerate = 60;
    csGraphicsContextSetTargetFramerate(context, framerate);
    while (csGraphicsUpdate(context))
    {
        csGraphicsFrameStart(context);
        csMeshDraw(mesh,NULL);
        csGraphicsFrameEnd(context);
        delta = csGraphicsWaitForNextFrame(framerate);
        int fps = csFixedToInt(csFixedDiv(csFixedFromInt(CLOCKS_PER_SEC), delta));
        printf("fps : %i\n",fps);
    }
    csGraphicsContextDestroy(context);
    csMeshFree(mesh);
    if (csAllocatedData() > 0) {
        printf("Exited with %llu bytes of leaked data !\n", csAllocatedData());
    }
    while (getchar() != '\n'){}
    return 0;
}
