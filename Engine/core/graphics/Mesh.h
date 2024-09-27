#ifndef CS_MESH_H
#define CS_MESH_H
#include "Shader.h"
#include <flecs.h>
#include "../maths/mat.h"
typedef struct csMesh {
    void *backend;
} csMesh;
extern ECS_COMPONENT_DECLARE(csMesh);
void *csMeshCreatePrimitivePyramid(void);
void csMeshFree(void *ptr,int unknown, const struct ecs_type_info_t *info);
void csMeshDraw(ecs_iter_t *it);
void csMeshModuleImport(ecs_world_t *ecs);
#endif
