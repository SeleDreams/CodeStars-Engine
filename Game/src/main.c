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
    if (csGraphicsContextCreate(&context, 1280, 720, "New Window"))
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
    ecs_entity_desc_t entitydesc;
    memset(&entitydesc,0,sizeof(ecs_entity_desc_t));
    csMesh *mesh = csMalloc(sizeof(csMesh));
    csMeshCreatePrimitivePyramid(mesh);

    for (int i = 0; i < 180; ++i) {
        csVec3 pos = {csFixedFromInt(rand() % 41-20), csFixedFromInt(rand()  % 41-20), csFixedFromInt(rand() %  41-20)};
        csTransform transform;
        csMatInit(&transform.m);
        csMatTranslate(&transform.m, &pos);
        ecs_entity_t pyramid_entity = ecs_entity_init(scene->world,&entitydesc);

        ecs_set_ptr(scene->world, pyramid_entity, csMesh, mesh);
        ecs_set_ptr(scene->world, pyramid_entity, csTransform, &transform);
    }
    csFree(mesh,sizeof(csMesh));
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
    /*if (csAllocatedData() != 0) {
        printf("Exited with %lu bytes of leaked data !\n", csAllocatedData());
    }*/
    return 0;
}
