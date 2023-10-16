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

static const GLfixed triangle_vertices[] =
{
    -1 << 16,-1 << 16,1 << 16,
    1 << 16, -1 << 16,0 << 16,
    0 << 16, 1 << 16, 0 << 16
};

csFMat4 fMat;

void csMeshDraw(csMesh *mesh, csShader *shader)
{
   // mesh->modelTransform.data[0][3] = 1;
    csMatToFloat(&fMat,&mesh->modelTransform);
    glUniformMatrix4fv(((glShader*)shader)->uModelTransform,1,GL_FALSE,(GLfloat*)fMat);
    glUseProgram(((glShader*)shader)->program);
    glBindBuffer(GL_ARRAY_BUFFER,mesh->VBO);
        glEnableVertexAttribArray(0);
            glVertexAttribPointer(0,3,GL_FIXED,GL_FALSE,0,0);
            glDrawArrays(GL_TRIANGLES,0,mesh->vertices_count / 3);
        glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
}

void csMeshCreatePrimitiveTriangle(csMesh **output)
{
    *output = csMalloc(sizeof(csMesh));
    csMesh *mesh = *output;
    csMatInit(&mesh->modelTransform);
    csMatFillDiagonal(&mesh->modelTransform,1000);
    
    mesh->vertices = triangle_vertices;
    mesh->vertices_count = sizeof(triangle_vertices) / sizeof(GLint);
    GLuint VAO, VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, mesh->vertices_count * sizeof(GLint), mesh->vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    mesh->VAO = VAO;
    mesh->VBO = VBO;
}

void csMeshFree(csMesh *mesh)
{
    glDeleteBuffers(1, &mesh->VBO);
    csFree(mesh,sizeof(csMesh));
}