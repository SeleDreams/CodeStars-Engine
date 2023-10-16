#ifndef CS_GLMESH_H
#define CS_GLMESH_H
#include <core/graphics/Mesh.h>
#include <core/utils/includes.h>
#include "GLGraphics.h"
typedef struct csMesh
{
    const GLfixed *vertices;
    GLuint vertices_count;
    GLuint VAO;
    GLuint VBO;
    csMat4 modelTransform;
} csMesh;
#endif