//
// Created by SeleDreams on 27/09/2024.
//
#include "transform.h"
ECS_COMPONENT_DECLARE(csTransform);

void csTransformModuleImport(ecs_world_t *ecs) {
    ECS_MODULE(ecs,csTransformModule);
    ECS_COMPONENT_DEFINE(ecs,csTransform);
    ecs_set_hooks(ecs,csTransform,{
        .ctor = csTransformConstructor
        });

    ecs_system(ecs, {
         .entity = ecs_entity(ecs, {
             .name = "csTransformUpdateSystem",
             .add = ecs_ids( ecs_dependson(EcsOnUpdate) )
         }),
         .query.terms = {
             {.id=ecs_id(csTransform),.inout = EcsIn}
         },
         .callback = csTransformUpdateSystem
    });
}

void csTransformUpdateSystem(ecs_iter_t *iter) {
    csTransform *transform = ecs_field(iter,csTransform,0);
    for (int i = 0; i < iter->count;i++) {
        csTransformUpdate(&transform[i]);
    }
}
void csTransformConstructor(void *ptr, int32_t count, const ecs_type_info_t *type_info) {
    for (int i = 0; i < count;i++) {
        csTransformInit(&((csTransform*)ptr)[i]);
    }
}
