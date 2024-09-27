#include <core/graphics/Mesh.h>
#include "core/scene/camera.h"
#include "core/maths/includes.h"
#include "GLMesh.h"

#include <fixstring.h>

#include "GLGraphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <core/scene/scene.h>
#include <gl/gl.h>

#include "core/maths/mat.h"
#include "core/memory/pool_allocator.h"
#include "core/components/transform.h"

static glMesh *realMesh;

// Vertices of the pyramid (fixed-point format)
const GLfixed pyramid_vertices[] = {
    csFixedFromFloat(-1.0), csFixedFromFloat(1.0), csFixedFromFloat(-1.0),  // Top front left
    csFixedFromFloat(1.0), csFixedFromFloat(1.0), csFixedFromFloat(-1.0),   // Top front right
    csFixedFromFloat(1.0), csFixedFromFloat(-1.0), csFixedFromFloat(-1.0),  // Bottom front right
    csFixedFromFloat(-1.0), csFixedFromFloat(-1.0), csFixedFromFloat(-1.0), // Bottom front left
    csFixedFromFloat(-1.0), csFixedFromFloat(1.0), csFixedFromFloat(1.0),   // Top back left
    csFixedFromFloat(1.0), csFixedFromFloat(1.0), csFixedFromFloat(1.0),    // Top back right
    csFixedFromFloat(1.0), csFixedFromFloat(-1.0), csFixedFromFloat(1.0),   // Bottom back right
    csFixedFromFloat(-1.0), csFixedFromFloat(-1.0), csFixedFromFloat(1.0)   // Bottom back left
};

// Indices for the cube faces
const GLubyte pyramid_indices[] = {
    0, 1, 2, 2, 3, 0, // Front face
    4, 5, 6, 6, 7, 4, // Back face
    0, 1, 5, 5, 4, 0, // Top face
    2, 3, 7, 7, 6, 2, // Bottom face
    0, 3, 7, 7, 4, 0, // Left face
    1, 2, 6, 6, 5, 1  // Right face
};

// Colors for each vertex
const GLubyte pyramid_colors[] = {
    255, 0, 0, 255,   // Red for top front left
    0, 255, 0, 255,   // Green for top front right
    0, 0, 255, 255,   // Blue for bottom front right
    255, 255, 0, 255, // Yellow for bottom front left
    0, 255, 255, 255, // Cyan for top back left
    255, 0, 255, 255, // Magenta for top back right
    192, 192, 192, 255, // Silver for bottom back right
    128, 0, 128, 255  // Purple for bottom back left
};


ecs_entity_t camera;
void csMeshDraw(ecs_iter_t *it)
{
    ecs_entities_t entities =  ecs_get_entities(csSceneRoot->world);
    for (int i = 0; i < entities.alive_count; i++) {
        ecs_entity_t id = entities.ids[i];
        if (ecs_has(csSceneRoot->world,id,csCamera)) {
            camera = id;
        }
    }
    csMesh *mesh = ecs_field(it,csMesh,0);
    csTransform *transform = ecs_field(it,csTransform,1);
    for (int i = 0; i < it->count; i++) {
        realMesh = mesh[i].backend;

        // Set up the projection matrix
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        const csCamera *cam = ecs_get(csSceneRoot->world,camera,csCamera);
        glLoadMatrixx(cam->projection.data);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        const csTransform *trans = ecs_get(csSceneRoot->world,camera,csTransform);
        glLoadMatrixx(trans->data);
        glMultMatrixx(transform[i].data);

        // Enable client states
        glEnableClientState(GL_VERTEX_ARRAY);
            glEnableClientState(GL_COLOR_ARRAY);
                glVertexPointer(3, GL_FIXED, 0, realMesh->vertices);
                glColorPointer(4, GL_UNSIGNED_BYTE, 0, realMesh->colors);
                glDrawElements(GL_TRIANGLES, realMesh->indices_count, GL_UNSIGNED_BYTE, realMesh->indices);
            glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        GLenum glError = glGetError();
        if (glError != GL_NO_ERROR)
        {
            printf("OpenGL Error : 0x%x\n", glError);
        }
    }
}

void *csMeshCreatePrimitivePyramid(void)
{
    realMesh = csMalloc(sizeof(glMesh));
    realMesh->vertices = pyramid_vertices;
    realMesh->indices = pyramid_indices;
    realMesh->colors = pyramid_colors;
    realMesh->indices_count = sizeof(pyramid_indices) / sizeof(GLubyte);
    realMesh->vertices_count = sizeof(pyramid_vertices) / sizeof(GLfixed);
    realMesh->colors_count = sizeof(pyramid_colors) / sizeof(GLubyte);
    GLenum glError = glGetError();
    if (glError != GL_NO_ERROR)
    {
         printf("OpenGL Error : 0x%x\n",glError);
    }
    return realMesh;
}

void csMeshFree(void *ptr,int count, const ecs_type_info_t *info)
{
    csMesh *mesh = ptr;
    for (int i = 0; i < count; i++) {
        csFree(mesh[i].backend,sizeof(glMesh));
    }
}

