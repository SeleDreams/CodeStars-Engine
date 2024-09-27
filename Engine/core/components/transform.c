//
// Created by SeleDreams on 27/09/2024.
//
#include "transform.h"
ECS_COMPONENT_DECLARE(csTransform);

void csTransformModuleImport(ecs_world_t *ecs) {
    ECS_MODULE(ecs,csTransformModule);
    ECS_COMPONENT_DEFINE(ecs,csTransform);
}