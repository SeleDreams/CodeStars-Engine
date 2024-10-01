//
// Created by SeleDreams on 27/09/2024.
//
#include "MeshRotatorSystem.h"

#include <core/os_functions.h>
#include <core/graphics/Mesh.h>
#include <core/maths/includes.h>
#include <core/components/transform.h>
static csVec3 pos = {
    .x = 0,
    .y = 0,
    .z = 0
};

static csVec3 size = {
    .x = csFixedFromInt(1),
    .y = csFixedFromInt(1),
    .z = csFixedFromInt(1)
};

csVec3 rotationAxis = {
    .x = 0, // 1/sqrt(2)
    .y = csFixedFromInt(1), // 1/sqrt(2)
    .z = 0
};


static inline void updateRotation(csTransform *modelTransform,csFixed delta) {
    static csFixed angle;
    angle += csFixedMul(csFixedFromInt(3),delta);
    int angleInt = csFixedToInt(angle);
    if (angleInt > 359) {
        angle = csFixedFromInt(1);
    }
    csQuat rot;
    csQuatFromAxisAngle(&rot, &rotationAxis, csFixedMul(angle,fix16_deg_to_rad_mult));
    csQuatNormalize(&rot, &rot);

    csTransformRotationSet(modelTransform,&rot);
    //csTransformRotate(modelTransform, &rot);
}

void csMeshRotatorSystem(ecs_iter_t *it) {
    csTransform *transform = ecs_field(it, csTransform, 1);

    for (int i = 0; i < it->count; i++) {
        updateRotation(&transform[i],it->delta_time);
    }
}

