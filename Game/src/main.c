#include <camera.h>
#include <stdio.h>
#include <CodeStarsEngine.h>
#include <scene.h>
#include <time.h>
#include "MeshRotatorSystem.h"
#include "platform_init.h"
#include <core/components/transform.h>
csScene *csSceneRoot;
static csFixed delta;

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    initMemoryPool(&csMemPoolAllocatorGlobal);
    initialize_engine();
    csGraphicsContext *context = NULL;
    if (csGraphicsContextCreate(&context, 800, 600, "New Window"))
    {
        printf("An error occurred while initializing the graphics context\n");
        return 1;
    }

    csScene *scene = csMalloc(sizeof(csScene));
    csSceneRoot = scene;

    csSceneInit(scene);

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



    for (int i = 0; i < 70; i++) {
        csVec3 pos = {csFixedFromInt(rand() % 41-20), csFixedFromInt(rand()  % 11-5), csFixedFromInt(rand() %  41-20)};

        csMesh mesh;
        csMeshCreatePrimitiveCube(&mesh);
        csTransform transform;
        csTransformInit(&transform);
        csTransformPositionSet(&transform, &pos);

        ecs_entity_t pyramid_entity = ecs_entity(scene->world,{0});

        ecs_set_ptr(scene->world, pyramid_entity, csMesh, &mesh);
        ecs_set_ptr(scene->world, pyramid_entity, csTransform, &transform);
    }
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
    if (csAllocatedData() != 0) {
        printf("Exited with %ui bytes of leaked data !\n", csAllocatedData());
    }
    return 0;
}
