#include <camera.h>
#include <stdio.h>
#include <CodeStarsEngine.h>
#include <scene.h>
#include <time.h>
#include <platform-specifics/graphics/GL/GLGraphics.h>
csScene *csSceneRoot;
static csFixed delta;
int main(void)
{
    initMemoryPool(&csMemPoolAllocatorGlobal);
    csGLGraphicsInit();
    csGLGraphicsContext *context = NULL;
    if (csGraphicsContextCreate(&context, 1280, 720, "New Window"))
    {
        printf("An error occurred while initializing the graphics context\n");
        return 1;
    }
    csScene *scene = csMalloc(sizeof(csScene));
    csSceneInit(scene);
    csSceneStart(scene);
    csSceneRoot = scene;
    csMesh *mesh = NULL;
    csMeshCreatePrimitivePyramid(&mesh);
    const int framerate = 60;
    csGraphicsContextSetTargetFramerate(context, framerate);
    while (csGraphicsUpdate(context))
    {
        csGraphicsFrameStart(context);
        delta = csGraphicsWaitForNextFrame(framerate);
        csSceneUpdate(scene,delta);
        csMeshDraw(mesh,NULL);
        csGraphicsFrameEnd(context);

        int fps = csFixedToInt(csFixedDiv(csFixedFromInt(CLOCKS_PER_SEC), delta));
        printf("fps : %i\n",fps);
    }
    csSceneDestroy(scene);
    csGraphicsContextDestroy(context);
    csMeshFree(mesh);
    if (csAllocatedData() > 0) {
        printf("Exited with %llu bytes of leaked data !\n", csAllocatedData());
    }
    while (getchar() != '\n'){}
    return 0;
}
