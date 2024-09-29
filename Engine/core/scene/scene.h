//
// Created by SeleDreams on 25/09/2024.
//

#ifndef SCENE_H
#define SCENE_H
#include "../memory/pool_allocator.h"
#include "../maths/includes.h"
#include <flecs.h>

typedef struct csScene {
    ecs_entity_t camera;
    ecs_world_t *world;
} csScene;
extern csScene *csSceneRoot;
void csSceneInit(csScene *p_scene);
void csSceneDestroy(csScene *p_scene);
void csSceneStart(csScene *p_scene);
void csSceneUpdate(csScene *p_scene,csFixed delta);
#endif //SCENE_H
