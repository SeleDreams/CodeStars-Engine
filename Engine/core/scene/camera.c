//
// Created by SeleDreams on 26/09/2024.
//
#include "camera.h"

#include <stdio.h>
#include <gles/gl.h>

#include "../components/transform.h"
#include "../memory/pool_allocator.h"
#include "../maths/includes.h"

ECS_COMPONENT_DECLARE(csCamera);

GLint m_viewport[4];
void csCameraModuleImport(ecs_world_t *ecs) {
    glGetIntegerv( GL_VIEWPORT, m_viewport );
    ECS_MODULE(ecs,csCameraModule);

    ECS_COMPONENT_DEFINE(ecs,csCamera);
    ecs_system(ecs, {
         .entity = ecs_entity(ecs, {
             .name = "csCameraStart",
             .add = ecs_ids( ecs_dependson(EcsOnStart) )
         }),
         .query.terms = {
             { .id = ecs_id(csCamera)},
             {.id=ecs_id(csTransform),.inout = EcsIn}
         },
         .callback = csCameraStart
    });
    ecs_system(ecs, {
     .entity = ecs_entity(ecs, {
         .name = "csCameraUpdate",
         .add = ecs_ids( ecs_dependson(EcsOnUpdate) )
     }),
     .query.terms = {
         { .id = ecs_id(csCamera)},
         {.id=ecs_id(csTransform),.inout = EcsIn}
     },
     .callback = csCameraUpdate
    });
}

void csCameraStart(ecs_iter_t *it) {
    csCamera *camera = ecs_field(it,csCamera,0);
    csTransform *transform = ecs_field(it,csTransform,1);
    static const csVec3 csCameraPos = {
        .x = csFixedFromFloat(0.0),
        .y = csFixedFromFloat(0.0),
        .z = csFixedFromFloat(-8.0)
    };
    for (int i = 0; i < it->count; i++) {
        csMatInit(&camera[i].projection);
        csMatInit(&transform[i]);
        csFixed fovy = csFixedFromFloat(45.0f);
        csFixed aspect = csFixedDiv(csFixedFromInt(m_viewport[2]),csFixedFromInt(m_viewport[3]));
        csFixed zNear = csFixedFromFloat(0.01f);
        csFixed zFar = csFixedFromFloat(100.0f);
        csMatPerspective(fovy, aspect, zNear, zFar, &camera[i].projection);
        csMatTranslate(&transform[i],&csCameraPos);
    }
}

void csCameraUpdate(ecs_iter_t *it) {
    csCamera *camera = ecs_field(it,csCamera,0);
    csTransform *transform = ecs_field(it,csTransform,1);
    static const csVec3 translation = {
        .x = 0,
        .y = 0,
        .z = csFixedFromFloat(-1)
    };
    csVec3 final = {};
    csVec3MulS(&final,&translation,it->delta_time);

    for (int i = 0; i < it->count; i++) {
        csMatTranslate(&transform[i],&final);
    }
}

ecs_entity_t csCameraCreate(ecs_world_t *ecs) {
    ecs_entity_t cam = ecs_set_name(ecs,0,"camera");
    ecs_set(ecs,cam,csCamera,{0});
    ecs_set(ecs,cam,csTransform,{0});
    return cam;
}