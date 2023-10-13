#ifndef CS_GLMESH_H
#define CS_GLMESH_H
#include <core/graphics/Mesh.h>
typedef struct csMesh
{
    float *vertices;
    unsigned int vertices_count;
    unsigned int VAO;
    unsigned int VBO;
} csMesh;
#endif