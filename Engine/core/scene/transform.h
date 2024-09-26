//
// Created by SeleDreams on 25/09/2024.
//

#ifndef SCENE_TRANSFORM_H
#define SCENE_TRANSFORM_H
#include "../maths/mat.h"
typedef struct csTransform {
    csMat4 local;
    csMat4 global;
} csTransform;

void csTransformInit(csTransform *p_transform);


#endif //SCENE_TRANSFORM_H
