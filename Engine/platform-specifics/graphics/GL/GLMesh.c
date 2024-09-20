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
    0, 1, 2,
    

};

static const GLfixed triangle_vertices[] =
{
    -1 * 65536,-1 * 65536,0 * 65536,
    0 * 65536,-1 * 65536,1 * 65536,
    1 * 65536, -1 * 65536,0 * 65536,
    0 * 65536, 1 * 65536, 0 * 65536
};

static csMat4 proj;
static csFMat4 fMat;
static csFMat4 fProj;

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
.x = 1 * 65536,
.y = 1 * 65536,
.z = 0 * 65536
};

static csMat4 trans;
static csMat4 scale;
static csMat4 rot;

static csQuat rotation;

static glMesh *realMesh = NULL;
void csMeshDraw(csMesh *mesh, csShader *shader)
{
    realMesh = (glMesh*)mesh;
    static csFixed angle = 0 * 65536;
    angle += 1 * 65536;
    if (csFixedToInt(angle) >= 359)
    {
        angle = 1 * 65536;
    }
    
    glUseProgram(((glShader*)shader)->program);
    csQuatFromAxisAngle(&rotation,&up,csFixedDegToRad(angle));
    csMatSetRotation(&rot,&rotation);
    csMatFillDiagonal(&realMesh->modelTransform,1 * 65536);
    csMatMul(&realMesh->modelTransform, &realMesh->modelTransform, &scale);
    csMatMul(&realMesh->modelTransform,&realMesh->modelTransform, &rot);
    csMatMul(&realMesh->modelTransform,&realMesh->modelTransform,&trans);

    //csMatSet(&mesh->modelTransform,3,3,1 * 65536);
    csMatToFloat(&fMat,&realMesh->modelTransform,0);
    csMatToFloat(&fProj,&proj,0);
    glUniformMatrix4fv(((glShader*)shader)->uModelTransform,1,GL_FALSE,(GLfloat*)fMat);
    glUniformMatrix4fv(((glShader*)shader)->uProjection,1,GL_FALSE,(GLfloat*)fProj);

    glBindBuffer(GL_ARRAY_BUFFER,realMesh->VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,realMesh->VAO);
            glVertexAttribPointer(0,3,GL_FIXED,GL_FALSE,0,0);
            glEnableVertexAttribArray(0);
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
    realMesh = csMalloc(sizeof(glMesh));
    *output = (csMesh*)realMesh;


    GLint m_viewport[4];

    glGetIntegerv( GL_VIEWPORT, m_viewport );
    csMatPerspective(&proj,csFixedDegToRad(csFixedFromFloat(45.0f)),csFixedDiv(m_viewport[2] * 65536,m_viewport[3] * 65536),csFixedFromFloat(0.1f),csFixedFromInt(100));
    csMatInit(&realMesh->modelTransform);
    csMatFillDiagonal(&realMesh->modelTransform,1 * 65536);

    csMatInit(&trans);
    csMatFillDiagonal(&trans,1 * 65536);
    csMatSetPosition(&trans,&pos);

    csMatInit(&scale);
    csMatFillDiagonal(&scale,1 * 65536);
    csMatScale(&scale,&size);

    csMatInit(&rot);
    //csQuatFromAxisAngle(&rotation,&up,csFixedDegToRad(0 * 65536));
    //csMatSetRotation(&rot,&rotation);

    realMesh->vertices = triangle_vertices;
    realMesh->vertices_count = sizeof(triangle_vertices) / sizeof(GLfixed);
    GLuint IBO, VBO;
    glGenBuffers(1,&IBO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(triangle_indices),triangle_indices,GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0,3,GL_FIXED,GL_FALSE,0,0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    int glError = glGetError();
    if (glError)
    {
         printf("OpenGL Error : 0x%x\n",glError);
    }
    realMesh->VAO = IBO;
    realMesh->VBO = VBO;
}

void csMeshFree(csMesh *mesh)
{
    glDeleteBuffers(1, &realMesh->VBO);
    csFree(mesh,sizeof(glMesh));
}