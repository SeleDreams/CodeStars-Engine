//
// Created by SeleDreams on 26/09/2024.
//
#include "camera.h"

#include <stdio.h>


#include "../os_functions.h"
#include "../components/transform.h"
#include "../memory/pool_allocator.h"
#include "../maths/includes.h"

ECS_COMPONENT_DECLARE(csCamera);

uint32_t m_viewport[4];
void csCameraModuleImport(ecs_world_t *ecs) {
#ifdef USE_GL
#include <gles/gl.h>
    glGetIntegerv( GL_VIEWPORT, m_viewport );
#else
    m_viewport[2] = 255;
    m_viewport[3] = 191;
#endif
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
    for (int i = 0; i < it->count; i++) {
        csMatInit(&camera[i].projection);
        csTransformInit(&transform[i]);
        csFixed fovy = csFixedFromFloat(70.0f);
        csFixed aspect = csFixedDivUnsigned(csFixedFromUInt(m_viewport[2]),csFixedFromUInt(m_viewport[3]));
        csFixed zNear = csFixedFromFloat(0.11f);
        csFixed zFar = csFixedFromFloat(20.0f);
        csMatPerspective(fovy, aspect, zNear, zFar, &camera[i].projection);
    }
}

const csVec3 up = {
    .x = 0,
    .y =  csFixedFromInt(1),
    .z = 0
};

void csCameraUpdate(ecs_iter_t *it) {
    csCamera *camera = ecs_field(it,csCamera,0);
    csTransform *transform = ecs_field(it,csTransform,1);
    static csVec3 translation;
    static csVec3 final;
    static csFixed angle;
    csQuat rot;
    for (int i = 0; i < it->count; i++) {


        angle += csFixedMul(csFixedFromInt(30),it->delta_time);
        if (csFixedToInt(angle) > 359) {
            angle = csFixedFromInt(1);
        }
        csQuatFromAxisAngle(&rot,&up,csFixedDegToRad(angle));
        csQuatNormalize(&rot,&rot);
        //csTransformRotate(&transform[i],&rot);
        csTransformRotationSet(&transform[i],&rot);
    }
}

ecs_entity_t csCameraCreate(ecs_world_t *ecs) {
    ecs_entity_t cam = ecs_set_name(ecs,0,"camera");
    ecs_set(ecs,cam,csCamera,{0});
    ecs_set(ecs,cam,csTransform,{0});
    printf("Created camera\n");
    return cam;
}