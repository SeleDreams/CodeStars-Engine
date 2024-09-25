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
static csMat4 proj;
static csVec3 pos = {
.x = 0,
.y = 0,
.z = csFixedFromInt(-5)
};
static csVec3 size = {
.x = csFixedFromInt(1),
.y = csFixedFromInt(1),
.z = csFixedFromInt(1)
};
csVec3 rotationAxis = {
.x = 0, // 1/sqrt(2)
.y = csFixedFromInt(1), // 1/sqrt(2)
.z = 0
};
static csQuat rotation;

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

csFixed randomFixed() {
    return csFixedDiv(csFixedFromInt(rand() % 2001 - 1000), csFixedFromInt(1000));
}
// Function to generate a random rotation axis
void generateRandomAxis(csVec3* axis) {
    axis->x = randomFixed();
    axis->y = randomFixed();
    axis->z = randomFixed();
    // Normalize the axis
    csVec3Normalize(axis, axis);
}
static csFixed angle;

void updateRotation() {
    angle = csFixedAdd(angle, csFixedFromInt(5));
    int angleInt = csFixedToInt(angle);
    if (angleInt > 359) {
        angle = csFixedFromInt(1);
        generateRandomAxis(&rotationAxis);
    }
    csQuatFromAxisAngle(&rotation, &rotationAxis, csFixedDegToRad(angle));
    csQuatNormalize(&rotation, &rotation);
    csMatSetRotation(&realMesh->rotMat, &rotation);
}

void csMeshDraw(csMesh *mesh, csShader *shader)
{
    realMesh = (glMesh*)mesh;
    static csFixed angle = csFixedFromInt(0);
    updateRotation();
    csMatSetPosition(&realMesh->transMat, &pos);

    csMatScale(&realMesh->scaleMat, &size);
    csMatInit(&realMesh->modelTransform);
    csMatFillDiagonal(&realMesh->modelTransform, csFixedFromInt(1));

    csMatMul(&realMesh->modelTransform, &realMesh->modelTransform, &realMesh->scaleMat);
    csMatMul(&realMesh->modelTransform, &realMesh->modelTransform, &realMesh->rotMat);
    csMatMul(&realMesh->modelTransform, &realMesh->modelTransform, &realMesh->transMat);

    // Set up the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glLoadMatrixx(proj.data);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glLoadMatrixx(realMesh->modelTransform.data);

    // Enable client states
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FIXED, 0, pyramid_vertices);
    glColorPointer(4, GL_UNSIGNED_BYTE, 0, pyramid_colors);
    glDrawElements(GL_TRIANGLES, sizeof(pyramid_indices) / sizeof(pyramid_indices[0]), GL_UNSIGNED_BYTE, pyramid_indices);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
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
    csMatFillDiagonal(&proj,csFixedFromInt(1));
    csFixed fovy = csFixedFromFloat(45.0f);
    csFixed aspect = csFixedDiv(csFixedFromInt(m_viewport[2]),csFixedFromInt(m_viewport[3]));
    csFixed zNear = csFixedFromFloat(0.01f);
    csFixed zFar = csFixedFromFloat(100.0f);
    csMatPerspective(fovy, aspect, zNear, zFar, proj.data);
    csMatInit(&realMesh->modelTransform);
    csMatFillDiagonal(&realMesh->modelTransform,csFixedFromInt(1));

    csMatInit(&realMesh->transMat);
    csMatFillDiagonal(&realMesh->transMat,csFixedFromInt(1));
    csMatSetPosition(&realMesh->transMat,&pos);

    csMatInit(&realMesh->scaleMat);
    csMatFillDiagonal(&realMesh->scaleMat,csFixedFromInt(1));
    csMatScale(&realMesh->scaleMat,&size);

    csMatInit(&realMesh->rotMat);
    csMatFillDiagonal(&realMesh->rotMat,csFixedFromInt(1));

    realMesh->vertices = pyramid_vertices;
    realMesh->indices = pyramid_indices;
    realMesh->indices_count = sizeof(pyramid_indices) / sizeof(GLubyte);
    realMesh->vertices_count = sizeof(pyramid_vertices) / sizeof(GLfixed);
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