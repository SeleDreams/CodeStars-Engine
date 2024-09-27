#include "Mesh.h"
#include <stdlib.h>
#include <string.h>
#include "../components/transform.h"
ECS_COMPONENT_DECLARE(csMesh);

void csMeshModuleImport(ecs_world_t *ecs) {
    ECS_MODULE(ecs,csMeshModule);
    ECS_COMPONENT_DEFINE(ecs,csMesh);
    ecs_system(ecs, {
         .entity = ecs_entity(ecs, {
             .name = "csMeshDraw",
             .add = ecs_ids( ecs_dependson(EcsOnUpdate) )
         }),
         .query.terms = {
             { .id = ecs_id(csMesh)},
             {.id=ecs_id(csTransform),.inout = EcsIn}
         },
         .callback = csMeshDraw
    });
    ecs_set_hooks(ecs, csMesh, {
        .dtor = csMeshFree
    });
}