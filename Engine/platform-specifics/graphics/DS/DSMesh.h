#ifndef CODESTARS_DS_MESH_H
#define CODESTARS_DS_MESH_H
#include <core/graphics/Mesh.h>
#include <core/utils/includes.h>
#include <core/maths/includes.h>
typedef struct csMesh
{
    const csFixed *vertices;
    unsigned int vertices_count;
    csMat4 modelTransform;
} csMesh;
#endif