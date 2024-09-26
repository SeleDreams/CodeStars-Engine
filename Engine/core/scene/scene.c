//
// Created by SeleDreams on 25/09/2024.
//
#include "scene.h"

#include <string.h>

#include "transform.h"
#include "scene_entity.h"

void csSceneInit(csScene *p_scene) {
    p_scene->entities = NULL;
}

void csSceneDestroy(csScene *p_scene) {
    csSceneEntity *entity = p_scene->entities;
    while(entity != NULL) {
            csSceneEntityDestroy(entity);
            entity = entity->next;
    }
    p_scene->entities = NULL;
    csFree(p_scene,sizeof(csScene));
}

void csSceneUpdate(csScene *p_scene,csFixed delta) {
    csSceneEntity *entity = p_scene->entities;
    while(entity != NULL&& entity->impl != NULL && entity->impl->update != NULL) {
        entity->impl->update(entity->impl->object,delta);
        entity = entity->next;
    }
}

void csSceneStart(csScene *p_scene) {
    csSceneEntity *entity = p_scene->entities;
    while(entity != NULL && entity->impl != NULL && entity->impl->start != NULL) {
        entity->impl->start(entity->impl->object);
        entity = entity->next;
    }
}

void csSceneAdd(csScene *p_scene, csSceneEntity *p_entity) {
    csSceneEntity *entity = p_scene->entities;
    if (entity == NULL) {
        p_scene->entities = p_entity;
        return;
    }
    while (entity != NULL) {
        if (entity->next == NULL) {
            entity->next = p_entity;
            return;
        }
        entity = entity->next;
    }
}

void *csSceneEntityByName(csScene *p_scene,const char *p_name) {
    csSceneEntity *entity = p_scene->entities;
    while (strcmp(p_name,entity->impl->name) != 0) {
        if (entity->next == NULL) {
            return NULL;
        }
        entity = entity->next;
    }
    return entity->impl->object;
}