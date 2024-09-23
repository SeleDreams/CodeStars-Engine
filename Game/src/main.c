#include <stdio.h>
#include <stdlib.h>
#include <CodeStarsEngine.h>
#include <fixstring.h>
#include <platform-specifics/graphics/GL/GLGraphics.h>
#include <time.h>
#include <unistd.h>

csMat4 transMat;
csMat4 scaleMat;
csMat4 rotMat;
csMat4 proj;
csQuat rotation;
static csFixed delta;
int main(void)
{
    csMemPoolAllocatorInit(&csMemPoolAllocatorGlobal,8);
    csGLGraphicsInit();
    csGraphicsContext context = NULL;
    if (csGraphicsContextCreate(&context, 800, 600, "New Window"))
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
        printf("fps : %i\n",csFixedDiv(1 << 16,delta) >> 16);
    }
    csGraphicsContextDestroy(&context);
    csMeshFree(mesh);
    if (csAllocatedData() > 0) {
        printf("Exited with %llu bytes of leaked data !\n", csAllocatedData());
    }
    return 0;
}
