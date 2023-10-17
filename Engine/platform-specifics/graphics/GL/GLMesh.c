#include <core/graphics/Mesh.h>
#include "core/maths/includes.h"
#include "GLMesh.h"
#include "GLGraphics.h"
#include "GLShader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "core/maths/mat.h"
#include "core/memory/pool_allocator.h"

static const GLuint triangle_indices[] = {
    0, 3, 1,
    1, 3, 2,
    2, 3, 0,
    0, 1, 2
};

static const GLfixed triangle_vertices[] =
{
    -1 << 16,-1 << 16,0 << 16,
    0 << 16,-1 << 16,1 << 16,
    1 << 16, -1 << 16,0 << 16,
    0 << 16, 1 << 16, 0 << 16
};

static csMat4 proj;
static csFMat4 fMat;
static csFMat4 fProj;

static csVec3 pos = {
.x = 0 << 16,
.y = 0 << 16,
.z = -2 << 16
};
static csVec3 size = {
.x = 1 << 16,
.y = 1 << 16,
.z = 1 << 16
};
static csVec3 up = {
.x = 0 << 16,
.y = 1 << 16,
.z = 0 << 16
};

static csMat4 trans;
static csMat4 scale;
static csMat4 rot;

static csQuat rotation;
void csMeshDraw(csMesh *mesh, csShader *shader)
{
    static csFixed angle = 0 << 16;
    angle += 1 << 16;
    if (csFixedToInt(angle) >= 359)
    {
        angle = 0 << 16;
    }
    
    glUseProgram(((glShader*)shader)->program);
    csQuatFromAxisAngle(&rotation,&up,csFixedDegToRad(angle));
    csMatSetRotation(&rot,&rotation);
    csMatFillDiagonal(&mesh->modelTransform,1 << 16);
    csMatMul(&mesh->modelTransform, &mesh->modelTransform, &scale);
    csMatMul(&mesh->modelTransform,&mesh->modelTransform, &rot);
    csMatMul(&mesh->modelTransform,&mesh->modelTransform,&trans);

    //csMatSet(&mesh->modelTransform,3,3,1 << 16);
    csMatToFloat(&fMat,&mesh->modelTransform,1);
    csMatToFloat(&fProj,&proj,0);
    glUniformMatrix4fv(((glShader*)shader)->uModelTransform,1,GL_FALSE,(GLfloat*)fMat);
    glUniformMatrix4fv(((glShader*)shader)->uProjection,1,GL_FALSE,(GLfloat*)fProj);

    glBindBuffer(GL_ARRAY_BUFFER,mesh->VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mesh->VAO);
            glEnableVertexAttribArray(0);
                glVertexAttribPointer(0,3,GL_FIXED,GL_FALSE,0,0);
                glDrawElements(GL_TRIANGLES,sizeof(triangle_indices) / sizeof(GLuint),GL_UNSIGNED_INT,0);
            glDisableVertexAttribArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    int glError = glGetError();
    if (glError)
    {
         printf("OpenGL Error : 0x%x\n",glError);
    }
}

void csMeshCreatePrimitiveTriangle(csMesh **output)
{
    *output = csMalloc(sizeof(csMesh));
    csMesh *mesh = *output;
    
    GLint m_viewport[4];

    glGetIntegerv( GL_VIEWPORT, m_viewport );
    csMatPerspective(&proj,csFixedDegToRad(csFixedFromFloat(45.0f)),csFixedFromFloat((float)m_viewport[2] / (float)m_viewport[3]),csFixedFromFloat(0.1f),csFixedFromInt(100));
    csMatInit(&mesh->modelTransform);
    csMatFillDiagonal(&mesh->modelTransform,1 << 16);

    csMatInit(&trans);
    csMatFillDiagonal(&trans,1 << 16);
    csMatSetPosition(&trans,&pos);

    csMatInit(&scale);
    csMatFillDiagonal(&scale,1 << 16);
    csMatScale(&scale,&size);

    csMatInit(&rot);
    csMatFillDiagonal(&rot,1 << 16);
    //csQuatFromAxisAngle(&rotation,&up,csFixedDegToRad(0 << 16));
    //csMatSetRotation(&rot,&rotation);

    mesh->vertices = triangle_vertices;
    mesh->vertices_count = sizeof(triangle_vertices) / sizeof(GLfixed);
    GLuint IBO, VBO;
    glGenBuffers(1,&IBO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(triangle_indices),triangle_indices,GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FIXED,GL_FALSE,0,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    int glError = glGetError();
    if (glError)
    {
         printf("OpenGL Error : 0x%x\n",glError);
    }
    mesh->VAO = IBO;
    mesh->VBO = VBO;
}

void csMeshFree(csMesh *mesh)
{
    glDeleteBuffers(1, &mesh->VBO);
    csFree(mesh,sizeof(csMesh));
}