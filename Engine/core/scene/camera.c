//
// Created by SeleDreams on 26/09/2024.
//
#include "camera.h"

#include <stdio.h>


#include "../components/transform.h"
#include "../memory/pool_allocator.h"
#include "../maths/includes.h"

ECS_COMPONENT_DECLARE(csCamera);

unsigned int m_viewport[4];
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
    static const csVec3 csCameraPos = {
        .x = csFixedFromFloat(0.0),
        .y = csFixedFromFloat(0.0),
        .z = csFixedFromFloat(-7.0)
    };
    for (int i = 0; i < it->count; i++) {
        csMatInit(&camera[i].projection);
        csMatInit(&transform[i].m);
        csFixed fovy = csFixedFromFloat(45.0f);
        csFixed aspect = csFixedDiv(csFixedFromInt(m_viewport[2]),csFixedFromInt(m_viewport[3]));
        csFixed zNear = csFixedFromFloat(0.01f);
        csFixed zFar = csFixedFromFloat(100.0f);
        csMatPerspective(fovy, aspect, zNear, zFar, &camera[i].projection);
        csMatTranslate(&transform[i].m,&csCameraPos);
    }
}
const csVec3 up = {
.x = 0,
    .y =  csFixedFromInt(1),
    .z = 0
};
csVec3 get_forward_vector(const csMat4* transform) {
    csVec3 forward;
    forward.x = transform->data[8];
    forward.y = transform->data[9];
    forward.z = transform->data[10];
    csVec3Normalize(&forward,&forward);
    return forward;
}

csVec3 get_right_vector(const csMat4* transform) {
    csVec3 right;
    right.x = transform->data[0];
    right.y = transform->data[1];
    right.z = transform->data[2];
    csVec3Normalize(&right,&right);
    return right;
}

csVec3 get_up_vector(const csMat4* transform) {
    csVec3 up;
    up.x = transform->data[4];
    up.y = transform->data[5];
    up.z = transform->data[6];
    csVec3Normalize(&up,&up);
    return up;
}
void csCameraUpdate(ecs_iter_t *it) {
    csCamera *camera = ecs_field(it,csCamera,0);
    csTransform *transform = ecs_field(it,csTransform,1);
    static csVec3 translation;
    static csVec3 final;
    for (int i = 0; i < it->count; i++) {
         translation = get_forward_vector(&transform[i].m);

        csVec3MulS(&final,&translation,csFixedMul(it->delta_time,csFixedFromInt(10)) );
       csMatTranslate(&transform[i].m,&final);
        csMatGetPosition(&final,&transform[i].m);
        //if (abs(final.z) > csFixedFromInt(30)) {
            csQuat rot;
            csQuatFromAxisAngle(&rot,&up,csFixedMul(it->delta_time,csFixedDegToRad(csFixedFromInt(50))));
            csMatRotate(&transform[i].m,&rot);
        //}
    }
}

ecs_entity_t csCameraCreate(ecs_world_t *ecs) {
    printf("Creating camera");
    ecs_entity_t cam = ecs_set_name(ecs,0,"camera");
    ecs_set(ecs,cam,csCamera,{0});
    ecs_set(ecs,cam,csTransform,{0});
    return cam;
}