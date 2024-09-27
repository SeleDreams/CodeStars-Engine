//
// Created by SeleDreams on 27/09/2024.
//
#include "MeshRotatorSystem.h"

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

csFixed randomFixed(void) {
    return csFixedDiv(csFixedFromInt(rand() % 2001 - 1000), csFixedFromInt(1000));
}

void generateRandomAxis(csVec3* axis) {
    axis->x = randomFixed();
    axis->y = randomFixed();
    axis->z = randomFixed();
    // Normalize the axis
    csVec3Normalize(axis, axis);
}

void updateRotation(csMat4 *modelTransform) {
    static csQuat rotation;
    static csFixed angle;
    angle = csFixedAdd(angle, csFixedFromInt(5));
    int angleInt = csFixedToInt(angle);
    if (angleInt > 359) {
        angle = csFixedFromInt(1);
        generateRandomAxis(&rotationAxis);
    }
    csQuatFromAxisAngle(&rotation, &rotationAxis, csFixedDegToRad(angle));
    csQuatNormalize(&rotation, &rotation);
    csMatRotate(modelTransform, &rotation);
}

void csMeshRotatorSystem(ecs_iter_t *it) {
    csTransform *transform = ecs_field(it,csTransform,1);
    for (int i = 0; i < it->count;i++) {
        csMatInit(&transform[i]);
        csMatScale(&transform[i],&size);
        updateRotation(&transform[i]);
        csMatTranslate(&transform[i],&pos);
    }
}
