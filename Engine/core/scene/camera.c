//
// Created by SeleDreams on 26/09/2024.
//
#include "camera.h"

#include <stdio.h>
#include <gles/gl.h>

#include "../memory/pool_allocator.h"
#include "../maths/includes.h"
#include "transform.h"

ECS_COMPONENT_DECLARE(ViewMatrix);
ECS_COMPONENT_DECLARE(Projection);
GLint m_viewport[4];
void csCameraImport(ecs_world_t *ecs) {
    glGetIntegerv( GL_VIEWPORT, m_viewport );
    ECS_MODULE(ecs,csCamera);

    ECS_COMPONENT_DEFINE(ecs,ViewMatrix);
    ECS_COMPONENT_DEFINE(ecs,Projection);

    ECS_SYSTEM(ecs, csCameraUpdate, EcsOnUpdate, ViewMatrix, Projection);
}

void csCameraUpdate(ecs_iter_t *it) {
    ViewMatrix *viewMatrix = ecs_field(it,ViewMatrix,0);
    Projection *projection = ecs_field(it,Projection,1);
    static const csVec3 csCameraPos = {
        .x = csFixedFromFloat(0.0),
        .y = csFixedFromFloat(0.0),
        .z = csFixedFromFloat(-8.0)
    };

    for (int i = 0; i < it->count; i++) {
        csMatInit(&projection[i].m);
        csMatInit(&viewMatrix[i].m);
        csFixed fovy = csFixedFromFloat(45.0f);
        csFixed aspect = csFixedDiv(csFixedFromInt(m_viewport[2]),csFixedFromInt(m_viewport[3]));
        csFixed zNear = csFixedFromFloat(0.01f);
        csFixed zFar = csFixedFromFloat(100.0f);
        csMatPerspective(fovy, aspect, zNear, zFar, projection[i].m.data);
        csMatTranslate(&viewMatrix[i].m,&csCameraPos);
    }
}

ecs_entity_t csCameraCreate(ecs_world_t *ecs) {
    return ecs_insert(ecs, ecs_value(ViewMatrix, {}),ecs_value(Projection,{}));
}