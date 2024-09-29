#include "NDSMesh.h"
#include <core/graphics/Mesh.h>
#include "core/scene/camera.h"
#include <stdio.h>
#include <stdlib.h>

#include "core/memory/pool_allocator.h"
#include "core/components/transform.h"
#include "core/scene/scene.h"

void csMeshDraw(ecs_iter_t *it)
{
   // printf("csMeshDraw called ! \n");
    m4x4 nds_mat;
    const csCamera *cam = ecs_get(it->world,csSceneRoot->camera,csCamera);
    const csTransform *camTransform = ecs_get(it->world,csSceneRoot->camera,csTransform);
    csMesh *mesh = ecs_field(it, csMesh, 0);
    csTransform *transform = ecs_field(it, csTransform, 1);
    glMatrixMode(GL_PROJECTION);
    csMatTo2012(&nds_mat.m,&cam->projection);
    glLoadMatrix4x4(&nds_mat);
    glMatrixMode(GL_MODELVIEW);
    for (int i = 0; i < it->count;i++) {
        csMesh *realMesh = &mesh[i];
        csMatTo2012(&nds_mat.m,&camTransform->m);
        glLoadMatrix4x4(&nds_mat);
        csMatTo2012(&nds_mat.m,&transform[i].m);
        glMultMatrix4x4(&nds_mat);
        glPushMatrix();
        glBegin(GL_TRIANGLES);
        for (int index = 0; index < realMesh->indices_count; index++) {
            unsigned char indices = realMesh->indices[index];
            glColor3b(realMesh->colors[indices * 3], realMesh->colors[indices * 3 + 1], realMesh->colors[indices * 3 + 2]);
            glVertex3v16(realMesh->vertices[indices * 3] >> 4, realMesh->vertices[indices * 3 + 1] >> 4, realMesh->vertices[indices * 3 + 2] >> 4);
        }

        glEnd();
        glPopMatrix(1);
    }
    glFlush(0);
}

void csMeshFree(void *ptr,int32_t count, const ecs_type_info_t *info)
{
    csFree(ptr,sizeof(csMesh));
}
