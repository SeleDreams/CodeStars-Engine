#include <core/graphics/Mesh.h>
#include "GLMesh.h"
#include "GLGraphics.h"
#include "GLShader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void csMeshDraw(csMesh *mesh, csShader *shader)
{
    glUseProgram(shader->program);
    glBindVertexArray(mesh->VAO);
    glBindBuffer(GL_VERTEX_ARRAY,mesh->VBO);
    glDrawArrays(GL_TRIANGLES,0,mesh->vertices_count / 3);
    glBindBuffer(GL_VERTEX_ARRAY,0);
    glBindVertexArray(0);
}

void csMeshCreatePrimitiveTriangle(csMesh **output)
{
    *output = malloc(sizeof(csMesh));
    csMesh *mesh = *output;
    float vertices[] =
        {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            0.0f, 1.0f, 0.0f};
    mesh->vertices = malloc(sizeof(vertices));
    mesh->vertices_count = sizeof(vertices) / sizeof(float);
    memcpy(mesh->vertices, vertices, sizeof(vertices));

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, mesh->vertices_count * sizeof(float), mesh->vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    mesh->VAO = VAO;
    mesh->VBO = VBO;
}

void csMeshFree(csMesh *mesh)
{
   /* glDeleteVertexArrays(1, &mesh->VAO);
    glDeleteBuffers(1, &mesh->VBO);*/
    free(mesh->vertices);
    free(mesh);
}