#include <core/graphics/Mesh.h>
#include "core/maths/includes.h"
#include "GLMesh.h"

#include <fixstring.h>

#include "GLGraphics.h"
#include "GLShader.h"
#include <stdio.h>
#include <stdlib.h>
#include <gl/gl.h>

#include "core/maths/mat.h"
#include "core/memory/pool_allocator.h"


static const GLubyte triangle_indices[] = {
    0 , 3, 1,
    1, 3, 2,
    2, 3, 0,
    0, 1, 2,
};

static const GLfixed triangle_vertices[] =
{
    -1 * (1 << 16) ,-1 * (1 << 16),0,
    0 ,-1* (1 << 16) ,1* (1 << 16),
    1* (1 << 16) , -1* (1 << 16) ,0 ,
    0, 1* (1 << 16), 0
};
extern csMat4 proj;
static csVec3 pos = {
.x = 0 * 65536,
.y = 0 * 65536,
.z = -3 * 65536
};
static csVec3 size = {
.x = 1 * 65536,
.y = 1 * 65536,
.z = 1 * 65536
};
static csVec3 up = {
    .x = 0 * 65536, // 1/sqrt(2)
        .y = 1 * 65536, // 1/sqrt(2)
        .z = 0
};
extern csQuat rotation;

static glMesh *realMesh;
void csMeshDraw(csMesh *mesh, csShader *shader)
{
    realMesh = (glMesh*)mesh;
    static csFixed angle = 180 * 65536;

    angle += 0.5 * (1  << 16);
    if (csFixedToInt(angle) > 359) {
        angle = 1 << 16;
    }
    csQuatFromAxisAngle(&rotation, &up, csFixedDegToRad(angle));
    csQuatNormalize(&rotation,&rotation);
    csMatSetRotation(&rotMat, &rotation);
    csMatSetPosition(&transMat, &pos);

    csMatScale(&scaleMat, &size);
    csMatInit(&realMesh->modelTransform);
    csMatFillDiagonal(&realMesh->modelTransform, 1 * 65536);

    csMatMul(&realMesh->modelTransform, &realMesh->modelTransform, &scaleMat);
    csMatMul(&realMesh->modelTransform, &realMesh->modelTransform, &rotMat);
    csMatMul(&realMesh->modelTransform, &realMesh->modelTransform, &transMat);

    // Set up the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glLoadMatrixx(proj.data);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glLoadMatrixx(realMesh->modelTransform.data);

    // Enable client states
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FIXED, 0, triangle_vertices);
    glDrawElements(GL_TRIANGLES, sizeof(triangle_indices) / sizeof(triangle_indices[0]), GL_UNSIGNED_BYTE, triangle_indices);
    glDisableClientState(GL_VERTEX_ARRAY);
    /*printf("================================ START\n");
    printf("rotation matrix  for angle %i:\n",csFixedToInt(angle));
    print_mf16(stdout, &rotMat);
    printf("-----------------------------------------\n");
    printf("final matrix :\n");
    print_mf16(stdout, &realMesh->modelTransform);
    printf("================================ END\n");*/
    GLenum glError = glGetError();
    if (glError != GL_NO_ERROR)
    {
        printf("OpenGL Error : 0x%x\n", glError);
    }
}


void csMeshCreatePrimitivePyramid(csMesh **output)
{
    realMesh = csMalloc(sizeof(glMesh));
    *output = (csMesh*)realMesh;
    GLint m_viewport[4];

    glGetIntegerv( GL_VIEWPORT, m_viewport );
    csMatInit(&proj);
    csMatFillDiagonal(&proj,1 << 16);
    csFixed fovy = csFixedFromFloat(90.0f);
    csFixed aspect = csFixedDiv(4 << 16,3 << 16);
    csFixed zNear = csFixedFromFloat(0.1f);
    csFixed zFar = csFixedFromFloat(100.0f);
    csMatPerspective(fovy, aspect, zNear, zFar, proj.data);
    csMatInit(&realMesh->modelTransform);
    csMatFillDiagonal(&realMesh->modelTransform,1 * 65536);

    csMatInit(&transMat);
    csMatFillDiagonal(&transMat,1 * 65536);
    csMatSetPosition(&transMat,&pos);

    csMatInit(&scaleMat);
    csMatFillDiagonal(&scaleMat,1 * 65536);
    csMatScale(&scaleMat,&size);

    csMatInit(&rotMat);
    csMatFillDiagonal(&rotMat,1 * 65536);
    //csQuatFromAxisAngle(&rotation,&up,csFixedDegToRad(0 * 65536));
    //csMatSetRotation(&rot,&rotation);

    realMesh->vertices = triangle_vertices;
    realMesh->indices = triangle_indices;
    realMesh->indices_count = sizeof(triangle_indices) / sizeof(GLubyte);
    realMesh->vertices_count = sizeof(triangle_vertices) / sizeof(GLfixed);
    GLenum glError = glGetError();
    if (glError != GL_NO_ERROR)
    {
         printf("OpenGL Error : 0x%x\n",glError);
    }
}

void csMeshFree(csMesh *mesh)
{
    csFree(mesh,sizeof(glMesh));
}