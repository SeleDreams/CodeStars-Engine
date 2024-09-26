//
// Created by SeleDreams on 25/09/2024.
//
#include "scene.h"
#include "transform.h"
#include "camera.h"

void csSceneInit(csScene *p_scene) {
    p_scene->world = ecs_init();
    ecs_measure_frame_time(p_scene->world,false);
    ECS_IMPORT(p_scene->world,csCamera);
    csCameraCreate(p_scene->world);
}

void csSceneDestroy(csScene *p_scene) {
    ecs_fini(p_scene->world);
    csFree(p_scene,sizeof(csScene));
}

void csSceneUpdate(csScene *p_scene,csFixed delta) {
    ecs_progress(p_scene->world, delta);
}

void csSceneStart(csScene *p_scene) {
}