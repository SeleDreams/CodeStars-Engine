#ifndef CS_GLMESH_H
#define CS_GLMESH_H
#include <core/graphics/Mesh.h>
#include <core/utils/includes.h>
#include "GLGraphics.h"
typedef struct glMesh
{
    const GLfixed *vertices;
    const GLubyte *indices;
    GLuint vertices_count;
    GLuint indices_count;
    csMat4 modelTransform;
    csMat4 transMat;
    csMat4 scaleMat;
    csMat4 rotMat;
} glMesh;
#endif