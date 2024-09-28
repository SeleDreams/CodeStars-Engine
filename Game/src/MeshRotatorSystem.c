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

typedef struct {
    csQuat rotation;
    csFixed angle;
    csVec3 rotationAxis;
} MeshRotationState;

void generateRandomAxis(csVec3* axis) {
    axis->x = randomFixed();
    axis->y = randomFixed();
    axis->z = randomFixed();
    // Normalize the axis
    csVec3Normalize(axis, axis);
}

void updateRotation(csMat4 *modelTransform, MeshRotationState *state) {
    state->angle = csFixedAdd(state->angle, csFixedFromInt(5));
    int angleInt = csFixedToInt(state->angle);
    if (angleInt > 359) {
        state->angle = csFixedFromInt(1);
        generateRandomAxis(&state->rotationAxis);
    }
    csQuatFromAxisAngle(&state->rotation, &state->rotationAxis, csFixedDegToRad(csFixedFromInt(5)));
    csQuatNormalize(&state->rotation, &state->rotation);
    csMatRotate(modelTransform, &state->rotation);
}

void csMeshRotatorSystem(ecs_iter_t *it) {
    csTransform *transform = ecs_field(it, csTransform, 1);
    static MeshRotationState *rotationStates = NULL;

    if (rotationStates == NULL) {
        rotationStates = malloc(it->count * sizeof(MeshRotationState));
        for (int i = 0; i < it->count; i++) {
            rotationStates[i].angle = csFixedFromInt(0);
            generateRandomAxis(&rotationStates[i].rotationAxis);
        }
    }

    for (int i = 0; i < it->count; i++) {
        csMatScale(&transform[i].m, &size);
        updateRotation(&transform[i].m, &rotationStates[i]);
        csMatTranslate(&transform[i].m, &pos);
    }
}

