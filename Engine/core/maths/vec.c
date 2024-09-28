//
// Created by SeleDreams on 27/09/2024.
//
#include "vec.h"
#include "mat.h"

void csVec3MulMat(csVec3* vec, const csMat4* mat)
{
    csVec3 temp;
    temp.x = csFixedAdd(csFixedAdd(csFixedAdd(csFixedMul(vec->x, mat->data[0]), csFixedMul(vec->y, mat->data[1])), csFixedMul(vec->z, mat->data[2])), mat->data[3]);
    temp.y = csFixedAdd(csFixedAdd(csFixedAdd(csFixedMul(vec->x, mat->data[4]), csFixedMul(vec->y, mat->data[5])), csFixedMul(vec->z, mat->data[6])), mat->data[7]);
    temp.z = csFixedAdd(csFixedAdd(csFixedAdd(csFixedMul(vec->x, mat->data[8]), csFixedMul(vec->y, mat->data[9])), csFixedMul(vec->z, mat->data[10])), mat->data[11]);

    vec->x = temp.x;
    vec->y = temp.y;
    vec->z = temp.z;
}
