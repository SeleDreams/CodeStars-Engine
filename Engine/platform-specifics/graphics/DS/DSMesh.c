#include "DSMesh.h"
#include <core/memory/pool_allocator.h>
#include <core/maths/includes.h>
#include <nds.h>
static const unsigned int triangle_indices[] = {
    0, 3, 1,
    1, 3, 2,
    2, 3, 0,
    0, 1, 2
};

static const csFixed triangle_vertices[] =
{
    -1 << 16,-1 << 16,0 << 16,
    0 << 16,-1 << 16,1 << 16,
    1 << 16, -1 << 16,0 << 16,
    0 << 16, 1 << 16, 0 << 16
};
static csMat4 proj;

static csVec3 pos = {
.x = 0 << 16,
.y = 0 << 16,
.z = -3 << 16
};
static csVec3 size = {
.x = 1 << 16,
.y = 1 << 16,
.z = 1 << 16
};
static csMat4 trans;
static csMat4 scale;
static csMat4 rot;

static csVec3 upVector;

static csQuat rotation;
static m4x4 dsMatrix;
void csMeshDraw(csMesh *mesh, csShader *shader)
{
    static csFixed angle = 0 << 16;
    angle += 1 << 16;
    if (csFixedToInt(angle) >= 359)
    {
        angle = 1 << 16;
    }
    csVec3 axis;
    csVec3Add(&axis,&csVec3Forward,&csVec3Right);
    csQuatFromAxisAngle(&rotation,&csVec3Right,csFixedDegToRad(angle));
    csMatSetRotation(&rot,&rotation);
    csMatFillDiagonal(&mesh->modelTransform,1 << 16);
    csMatMul(&mesh->modelTransform, &mesh->modelTransform, &scale);
    csMatMul(&mesh->modelTransform,&mesh->modelTransform, &rot);
    csMatMul(&mesh->modelTransform,&mesh->modelTransform,&trans);
    csVec3MulM(&upVector,&mesh->modelTransform,&csVec3Up);
    csFixed *matrixArray = (csFixed*)csMatRaw(&mesh->modelTransform);
    for (int i = 0; i < sizeof(dsMatrix.m) / sizeof(int);i++)
    {
       dsMatrix.m[i] = matrixArray[i]; 
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrix4x4(&dsMatrix);
    glBegin(GL_TRIANGLES);
    static const csFixed *current_vertex = NULL;
    for (int i = 0; i < sizeof(triangle_indices) / sizeof(unsigned int);i++)
    {
        current_vertex = triangle_vertices + (triangle_indices[i] * sizeof(csFixed));
        glVertex3v16(current_vertex[0],current_vertex[1],current_vertex[2]);
    }
    glEnd();
}

void csMeshCreatePrimitiveTriangle(csMesh **output)
{
    *output = csMalloc(sizeof(csMesh));
    csMesh *mesh = *output;
    
    csMatPerspective(&proj,csFixedFromInt(45),csFixedDiv(csFixedFromInt(SCREEN_WIDTH - 1),csFixedFromInt(SCREEN_HEIGHT - 1)),csFixedFromFloat(0.1f),csFixedFromInt(100));
    csMatInit(&mesh->modelTransform);
    csMatFillDiagonal(&mesh->modelTransform,1 << 16);

    csMatInit(&trans);
    csMatFillDiagonal(&trans,1 << 16);
    csMatSetPosition(&trans,&pos);

    csMatInit(&scale);
    csMatFillDiagonal(&scale,1 << 16);
    csMatScale(&scale,&size);

    csMatInit(&rot);

    mesh->vertices = triangle_vertices;
    mesh->vertices_count = sizeof(triangle_vertices) / sizeof(csFixed);

    csFixed *matrixArray = (csFixed*)csMatRaw(&proj);
    for (int i = 0; i < sizeof(dsMatrix.m) / sizeof(int);i++)
    {
       dsMatrix.m[i] = matrixArray[i] >> 16;  
    }
    /*glMatrixMode(GL_PROJECTION);
    glLoadMatrix4x4(&dsMatrix);*/
}

void csMeshFree(csMesh *mesh)
{
    csFree(mesh,sizeof(csMesh));
}