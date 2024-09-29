#ifndef CS_MESH_H
#define CS_MESH_H
#include "Shader.h"
#include <flecs.h>
#include "../maths/mat.h"
typedef struct csMesh {
    const csFixed *vertices;
    const unsigned char *indices;
    const unsigned char *colors;
    uint32_t vertices_count;
    uint32_t indices_count;
    uint32_t colors_count;
    ecs_query_t *q;
} csMesh;

extern ECS_COMPONENT_DECLARE(csMesh);
void csMeshCreatePrimitiveCube(csMesh *mesh);
void csMeshFree(void *ptr,int32_t unknown, const struct ecs_type_info_t *info);
void csMeshDraw(ecs_iter_t *it);
void csMeshModuleImport(ecs_world_t *ecs);
#endif
