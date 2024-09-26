//
// Created by SeleDreams on 25/09/2024.
//

#ifndef SCENE_TRANSFORM_H
#define SCENE_TRANSFORM_H
#include "../maths/mat.h"
#include <flecs.h>
typedef struct csTransform {
    csMat4 transform;
} csTransform;

#endif //SCENE_TRANSFORM_H
