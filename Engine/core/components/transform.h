//
// Created by SeleDreams on 27/09/2024.
//

#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "../maths/mat.h"
#include <flecs.h>
typedef csMat4 csTransform;
extern ECS_COMPONENT_DECLARE(csTransform);
void csTransformModuleImport(ecs_world_t *ecs);
#endif //TRANSFORM_H
