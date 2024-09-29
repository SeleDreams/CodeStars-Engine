#include <core/graphics/Mesh.h>
#include "core/scene/camera.h"
#include "core/maths/includes.h"
#include "GLMesh.h"

#include <fixstring.h>

#include "GLGraphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <gl/gl.h>

#include "core/memory/pool_allocator.h"
#include "core/components/transform.h"

void csMeshDraw(ecs_iter_t *it)
{
    ecs_query_t *q = ecs_query(it->world, {
        .terms = {
            { .id = ecs_id(csCamera) },
            { .id = ecs_id(csTransform), .inout = EcsIn}
        },
    });
    ecs_iter_t cameras = ecs_query_iter(it->world, q);
    ecs_iter_next(&cameras);
    csCamera *cam = ecs_field(&cameras, csCamera, 0);
    csTransform *camTransform = ecs_field(&cameras, csTransform, 1);
    csMesh *mesh = ecs_field(it, csMesh, 0);
    csTransform *transform = ecs_field(it, csTransform, 1);
    ecs_iter_fini(&cameras);
    ecs_query_fini(q);
    // Set up projection matrix once
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixx(cam->projection.data);

    // Set up modelview matrix once
    glMatrixMode(GL_MODELVIEW);


    // Enable client states once
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    for (int i = 0; i < it->count;i++) {
        csMesh *realMesh = &mesh[i];

        glLoadMatrixx(camTransform->m.data);
        glMultMatrixx(transform[i].m.data);
        // Set vertex and color pointers
        glVertexPointer(3, GL_FIXED, 0, realMesh->vertices);
        glColorPointer(4, GL_UNSIGNED_BYTE, 0, realMesh->colors);
        // Draw the combined mesh
        glDrawElements(GL_TRIANGLES, realMesh->indices_count, GL_UNSIGNED_BYTE, realMesh->indices);
    }

    // Disable client states once
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);


    GLenum glError = glGetError();
    if (glError != GL_NO_ERROR) {
        printf("OpenGL Error : 0x%x\n", glError);
    }
}

void csMeshFree(void *ptr,int count, const ecs_type_info_t *info)
{
    //csFree(ptr,sizeof(csMesh));
}
