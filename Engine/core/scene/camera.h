//
// Created by SeleDreams on 26/09/2024.
//

#ifndef CAMERA_H
#define CAMERA_H
#include "transform.h"
#include "scene_entity.h"
typedef struct csCamera {
    csTransform transform;
    csMat4 projection;
} csCamera;
void csCameraInit(csCamera *p_camera);
void csCameraStart(csCamera *p_camera);
void csCameraDestroy(csCamera *p_camera);
void csCameraUpdate(csCamera *p_camera,csFixed delta);
csSceneEntityImpl *csCreateCameraEntityImpl(void);
#endif //CAMERA_H
