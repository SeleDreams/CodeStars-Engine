//
// Created by SeleDreams on 27/09/2024.
//

#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "../maths/mat.h"
#include <flecs.h>
typedef struct {csMat4 translation;csMat4 rotation; csMat4 scale;csMat4 transform;bool dirty;} csTransform;
extern ECS_COMPONENT_DECLARE(csTransform);
void csTransformModuleImport(ecs_world_t *ecs);

void csTransformUpdateSystem(ecs_iter_t *iter);
void csTransformConstructor(void *ptr, int32_t count, const ecs_type_info_t *type_info);

static inline void csTransformInit(csTransform *transform) {
    transform->dirty = false;
    csMatInit(&transform->rotation);
    csMatInit(&transform->scale);
    csMatInit(&transform->translation);
    csMatInit(&transform->transform);
}

static inline void csTransformUpdate(csTransform *transform) {
    if (!transform->dirty) {
        return;
    }
    csMatFillDiagonal(&transform->transform,csFixedFromInt(1));
    csMatMul(&transform->transform,&transform->transform,&transform->scale);
    csMatMul(&transform->transform,&transform->transform,&transform->rotation);
    csMatMul(&transform->transform,&transform->transform,&transform->translation);
    transform->dirty = false;
}

static inline void csTransformPositionSet(csTransform *transform, const csVec3 *pos) {
    csMatPositionSet(&transform->translation,pos);
    transform->dirty = true;
}
static inline void csTransformPositionGet(csVec3 *pos, const csTransform *trans) {
    csMatPositionGet(pos,&trans->translation);
}

static inline void csTransformTranslate(csTransform *transform, const csVec3 *pos) {
    csMatTranslate(&transform->translation,pos);
    transform->dirty = true;
}

static inline void csTransformScaleSet(csTransform *transform, const csVec3 *scale) {
    csMatScaleSet(&transform->scale,scale);
    transform->dirty = true;
}

static inline void csTransformScaleGet(csVec3 *scale, const csTransform *transform) {
    csMatScaleGet(scale,&transform->scale);
}

static inline void csTransformRotationSet(csTransform *transform, const csQuat *rot) {
    csMatRotationSet(&transform->rotation,rot);
    transform->dirty = true;
}

static inline void csTransformRotationGet(csQuat *rot, const csTransform *transform) {
    csMatRotationGet(rot,&transform->rotation);
}

static inline void csTransformRotate(csTransform *transform, const csQuat *rot) {
    csMatRotate(&transform->rotation,rot);
    transform->dirty = true;
}

#endif //TRANSFORM_H
