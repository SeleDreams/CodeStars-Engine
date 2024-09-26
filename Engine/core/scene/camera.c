//
// Created by SeleDreams on 26/09/2024.
//
#include "camera.h"

#include <stdio.h>
#include <gles/gl.h>

#include "../memory/pool_allocator.h"

csVec3 csCameraPos = {
    .x = csFixedFromFloat(0.0),
    .y = csFixedFromFloat(0.0),
    .z = csFixedFromFloat(-8.0)
};
void csCameraInit(csCamera *p_camera) {
    if (p_camera == NULL) {
        return;
    }
    GLint m_viewport[4];
    glGetIntegerv( GL_VIEWPORT, m_viewport );
    csMatInit(&p_camera->projection);
    csFixed fovy = csFixedFromFloat(45.0f);
    csFixed aspect = csFixedDiv(csFixedFromInt(m_viewport[2]),csFixedFromInt(m_viewport[3]));
    csFixed zNear = csFixedFromFloat(0.01f);
    csFixed zFar = csFixedFromFloat(100.0f);
    csMatPerspective(fovy, aspect, zNear, zFar, p_camera->projection.data);
    csTransformInit(&p_camera->transform);
}

void csCameraStart(csCamera *p_camera) {
    printf("The camera got initialized\n");
    csMatTranslate(&p_camera->transform.global,&csCameraPos);
}

void csCameraUpdate(csCamera *p_camera,csFixed delta) {

}

void csCameraDestroy(csCamera *p_camera) {
    printf("The camera got destroyed\n");
    csFree(p_camera,sizeof(csCamera));
}

csSceneEntityImpl *csCreateCameraEntityImpl() {
    csSceneEntityImpl *impl = csMalloc(sizeof(csSceneEntityImpl));
    csSceneEntityImplInit(impl);
    impl->object = csMalloc(sizeof(csCamera));
    csCameraInit(impl->object);
    impl->start = ((void (*)(void *))csCameraStart);
    impl->update = ((void (*)(void *,csFixed))csCameraUpdate);
    impl->destroy = ((void (*)(void *))csCameraDestroy);
    impl->name = "Camera";
    return impl;
}