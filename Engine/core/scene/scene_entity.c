//
// Created by SeleDreams on 25/09/2024.
//
#include "scene_entity.h"

#include "../memory/pool_allocator.h"

void csSceneEntityInit(csSceneEntity *p_entity,csSceneEntityImpl *impl) {
    p_entity->impl = impl;
    p_entity->next = NULL;
    p_entity->previous = NULL;
}

void csSceneEntityDestroy(csSceneEntity *p_entity) {
    if (p_entity->impl) {
        p_entity->impl->destroy(p_entity);
        csFree(p_entity->impl,sizeof(csSceneEntityImpl));
        p_entity->impl = NULL;
    }
    if (p_entity->previous != NULL) {
        p_entity->previous->next = p_entity->next;
        p_entity->previous = NULL;
    }
    if (p_entity->next != NULL) {
        p_entity->next->previous = p_entity->previous;
        p_entity->next = NULL;
    }
    csFree(p_entity,sizeof(csSceneEntity));
}

void csSceneEntityImplInit(csSceneEntityImpl *p_impl) {
    p_impl->destroy = NULL;
    p_impl->object = NULL;
    p_impl->start = NULL;
    p_impl->update = NULL;
    p_impl->name = NULL;
}