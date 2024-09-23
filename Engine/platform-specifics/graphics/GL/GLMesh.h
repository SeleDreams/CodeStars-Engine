#ifndef CS_GLMESH_H
#define CS_GLMESH_H
#include <core/graphics/Mesh.h>
#include <core/utils/includes.h>
#include "GLGraphics.h"
extern csMat4 transMat;
extern csMat4 scaleMat;
extern csMat4 rotMat;
typedef struct glMesh
{
    const GLfixed *vertices;
    const GLubyte *indices;
    GLuint vertices_count;
    GLuint indices_count;
    csMat4 modelTransform;
} glMesh;
#endif