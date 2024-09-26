//
// Created by SeleDreams on 25/09/2024.
//

#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H
#include "transform.h"



typedef struct csSceneEntity {
    struct csSceneEntityImpl *impl;
    struct csSceneEntity *next;
    struct csSceneEntity *previous;
} csSceneEntity;

typedef struct csSceneEntityImpl {
    void *object;
    const char *name;
    void (*start)(void *p_object);
    void (*update)(void *p_object,csFixed delta);
    void (*destroy)(void *p_object);
} csSceneEntityImpl;

void csSceneEntityInit(csSceneEntity *p_entity,csSceneEntityImpl *impl);
void csSceneEntityImplInit(csSceneEntityImpl *p_impl);
void csSceneEntityDestroy(csSceneEntity *p_entity);
#endif //GAME_ENTITY_H
