//
// Created by SeleDreams on 26/09/2024.
//

#ifndef CAMERA_H
#define CAMERA_H
#include "../maths/includes.h"
#include <flecs.h>

typedef struct {csMat4 m;} ViewMatrix,Projection;
extern ECS_COMPONENT_DECLARE(ViewMatrix);
extern ECS_COMPONENT_DECLARE(Projection);

void csCameraImport(ecs_world_t *ecs);
ecs_entity_t csCameraCreate(ecs_world_t *ecs);
void csCameraUpdate(ecs_iter_t *it);
#endif //CAMERA_H
