#include <camera.h>
#include <stdio.h>
#include <CodeStarsEngine.h>
#include <scene.h>
#include <time.h>
#include "MeshRotatorSystem.h"
#include <platform-specifics/graphics/GL/GLGraphics.h>
#include <core/components/transform.h>
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
    csSceneRoot = scene;
    csSceneInit(scene);
    void *pyramid = csMeshCreatePrimitivePyramid();

    // Create a system for Position, Velocity.
    ecs_system(scene->world, {
        .entity = ecs_entity(scene->world, {
            .name = "csMeshRotator",
            .add = ecs_ids( ecs_dependson(EcsOnUpdate) )
        }),
        .query.terms = {
            { .id = ecs_id(csMesh)},
            {.id=ecs_id(csTransform) }
        },
        .callback = csMeshRotatorSystem
    });

    ecs_entity_t pyramid_entity = ecs_set_name(scene->world, 0, "Pyramid");
    ecs_set(scene->world,pyramid_entity,csMesh,{pyramid});
    ecs_set(scene->world,pyramid_entity,csTransform,{
    .rows = 4,
    .columns = 4,
    .errors = 0,
    .data = {0}
});
    csSceneStart(scene);

    const int framerate = 60;
    csGraphicsContextSetTargetFramerate(context, framerate);
    while (csGraphicsUpdate(context))
    {
        csGraphicsFrameStart(context);
        delta = csGraphicsWaitForNextFrame(framerate);
        csSceneUpdate(scene,delta);
        csGraphicsFrameEnd(context);

        int fps = csFixedToInt(csFixedDiv(csFixedFromInt(1), delta));
        printf("fps : %i\n",fps);
    }
    csSceneDestroy(scene);
    csGraphicsContextDestroy(context);
    if (csAllocatedData() > 0) {
        printf("Exited with %llu bytes of leaked data !\n", csAllocatedData());
    }
    while (getchar() != '\n'){}
    return 0;
}
