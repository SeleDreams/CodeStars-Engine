//
// Created by SeleDreams on 27/09/2024.
//
#include "transform.h"
ECS_COMPONENT_DECLARE(csTransform);

void csTransformModuleImport(ecs_world_t *ecs) {
    ECS_MODULE(ecs,csTransformModule);
    ECS_COMPONENT_DEFINE(ecs,csTransform);
}

void csTransformInit(csTransform *transform) {
    csMatInit(&transform->rotation);
    csMatInit(&transform->scale);
    csMatInit(&transform->translation);
    csMatInit(&transform->transform);
}

void csTransformUpdate(csTransform *transform) {
    csMatInit(&transform->transform);
    csMatMul(&transform->transform,&transform->transform,&transform->scale);
    csMatMul(&transform->transform,&transform->transform,&transform->rotation);
    csMatMul(&transform->transform,&transform->transform,&transform->translation);
}

void csTransformPositionSet(csTransform *transform, const csVec3 *pos) {
    csMatPositionSet(&transform->translation,pos);
}
void csTransformPositionGet(csVec3 *pos, const csTransform *trans) {
    csMatPositionGet(pos,&trans->translation);
}
void csTransformTranslate(csTransform *transform, const csVec3 *pos) {
    csMatTranslate(&transform->translation,pos);
}

void csTransformScaleSet(csTransform *transform, const csVec3 *scale) {
    csMatScaleSet(&transform->scale,scale);
}
void csTransformScaleGet(csVec3 *scale, const csTransform *transform) {
    csMatScaleGet(scale,&transform->scale);
}
void csTransformRotationSet(csTransform *transform, const csQuat *rot) {
    csMatRotationSet(&transform->rotation,rot);
}
void csTransformRotationGet(csQuat *rot, const csTransform *transform) {
    csMatRotationGet(rot,&transform->rotation);
}

void csTransformRotate(csTransform *transform, const csQuat *rot) {
    csMatRotate(&transform->rotation,rot);
}