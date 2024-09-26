//
// Created by SeleDreams on 25/09/2024.
//
#include "transform.h"

void csTransformInit(csTransform *p_transform) {
   csMatInit(&p_transform->local);
   csMatInit(&p_transform->global);
}

