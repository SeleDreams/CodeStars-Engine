//
// Created by SeleDreams on 27/09/2024.
//

#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "../maths/mat.h"
#include <flecs.h>
typedef struct {csMat4 translation;csMat4 rotation; csMat4 scale;csMat4 transform;} csTransform;
extern ECS_COMPONENT_DECLARE(csTransform);
void csTransformModuleImport(ecs_world_t *ecs);
void csTransformInit(csTransform *transform);
void csTransformUpdate(csTransform *transform);

void csTransformPositionSet(csTransform *transform, const csVec3 *pos);
void csTransformPositionGet(csVec3 *pos, const csTransform *trans);
void csTransformTranslate(csTransform *transform, const csVec3 *pos);

void csTransformScaleSet(csTransform *transform, const csVec3 *scale);
void csTransformScaleGet(csVec3 *scale, const csTransform *transform);

void csTransformRotationSet(csTransform *transform, const csQuat *rot);
void csTransformRotationGet(csQuat *rot, const csTransform *transform);
void csTransformRotate(csTransform *transform, const csQuat *rot);
#endif //TRANSFORM_H
