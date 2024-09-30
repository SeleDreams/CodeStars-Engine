#include "NDSMesh.h"
#include <core/graphics/Mesh.h>
#include "core/scene/camera.h"
#include <stdio.h>
#include <stdlib.h>

#include "core/memory/pool_allocator.h"
#include "core/components/transform.h"
#include "core/scene/scene.h"

static inline void setupProjectionMatrix(m4x4 *nds_mat,const csCamera *cam) {
    csMatTo2012(&nds_mat->m, &cam->projection);
    glMatrixMode(GL_PROJECTION);
    glLoadMatrix4x4(nds_mat);
}

static inline void setupModelViewMatrix(m4x4 *nds_mat,csTransform *camTransform) {
    csMatTo2012(&nds_mat->m, &camTransform->transform);
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrix4x4(nds_mat);
}

static inline void applyTransformMatrix(m4x4 *nds_mat,csTransform *transform) {
    csMatTo2012(&nds_mat->m, &transform->transform);
    glMultMatrix4x4(nds_mat);
}

void drawMesh(const csMesh *mesh) {
    unsigned int realIndex;
    for (int index = 0; index < mesh->indices_count; index++) {
        realIndex = mesh->indices[index] * 3;

        glColor3b(
            mesh->colors[realIndex],
            mesh->colors[realIndex + 1],
            mesh->colors[realIndex + 2]
            );
        glVertex3v16(
            mesh->vertices[realIndex] >> 4,
            mesh->vertices[realIndex + 1] >> 4,
            mesh->vertices[realIndex + 2] >> 4
            );
    }

}
m4x4 nds_mat;
void csMeshDraw(ecs_iter_t *it) {
    const csCamera *cam = ecs_get(it->world, csSceneRoot->camera, csCamera);
    csTransform *camTransform = (csTransform*)ecs_get(it->world, csSceneRoot->camera, csTransform);
    csMesh *mesh = ecs_field(it, csMesh, 0);
    csTransform *transform = ecs_field(it, csTransform, 1);

    setupProjectionMatrix(&nds_mat,cam);
    setupModelViewMatrix(&nds_mat,camTransform);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < it->count; i++) {
        glPushMatrix();
        applyTransformMatrix(&nds_mat,&transform[i]);
        drawMesh(&mesh[i]);
        glPopMatrix(1);
    }
    glEnd();
    glFlush(0);
}


void csMeshFree(void *ptr,int32_t count, const ecs_type_info_t *info)
{
    csFree(ptr,sizeof(csMesh));
}
