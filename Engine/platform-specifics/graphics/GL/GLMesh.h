#ifndef CS_GLMESH_H
#define CS_GLMESH_H
#include <core/graphics/Mesh.h>
#include <core/utils/includes.h>
#include "GLGraphics.h"
typedef struct glMesh
{
    const GLfixed *vertices;
    const GLubyte *indices;
    const GLubyte *colors;
    GLuint vertices_count;
    GLuint indices_count;
    GLuint colors_count;
} glMesh;
#endif