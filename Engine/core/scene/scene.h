//
// Created by SeleDreams on 25/09/2024.
//

#ifndef SCENE_H
#define SCENE_H
#include "scene_entity.h"
#include "../memory/pool_allocator.h"

typedef struct csScene {
    csSceneEntity *entities;
    size_t entity_count;
    size_t max_entity_count;
} csScene;
extern csScene *csSceneRoot;
void csSceneInit(csScene *p_scene);
void csSceneDestroy(csScene *p_scene);
void csSceneStart(csScene *p_scene);
void csSceneUpdate(csScene *p_scene,csFixed delta);
void *csSceneEntityByName(csScene *scene,const char *name);
void csSceneAdd(csScene *p_scene, csSceneEntity *p_entity);
#endif //SCENE_H
