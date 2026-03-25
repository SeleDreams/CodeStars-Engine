#ifndef CODESTARS_ENGINE_CORE_MATHS_VEC_H
#define CODESTARS_ENGINE_CORE_MATHS_VEC_H
#include "maths.h"
#include <stdio.h>
typedef v3d csVec3;
typedef v2d csVec2;
static inline int csMatGet(const csMat4 *a,int row, int column);
static inline void csMatGetPosition(csVec3 *dest, const csMat4 *mat);
typedef struct csVec4 {
    csFixed x;
    csFixed y;
    csFixed z;
    csFixed w;
} csVec4;

static const csVec3 csVec3Up = {
    .x = 0,
    .y = 1 << 16,
    .z = 0
};

static const csVec3 csVec3Right = {
    .x = 1 << 16,
    .y = 0,
    .z = 0
};

static const csVec3 csVec3Forward = {
    .x = 0,
    .y = 0,
    .z = 1 << 16
};
static inline csFixed csVec3Length(const csVec3 *a) {return v3d_norm(a);}
static inline void csVec3Normalize(csVec3 *dest,const csVec3 *a){v3d_normalize(dest,a);}
static inline void csVec3Add(csVec3 *dest, const csVec3 *a,const csVec3 *b) {v3d_add(dest,a,b);}
static inline void csVec3Sub(csVec3 *dest, const csVec3 *a, const csVec3 *b) {v3d_sub(dest,a,b);}
static inline void csVec3MulS(csVec3 *dest,const csVec3 *a,csFixed b){v3d_mul_s(dest,a,b);}
static inline void csVec3MulM(csVec3 *dest,const csMat4 *mat, const csVec3 *vec)
{
    static csVec4 tempVec = {
        .x = 0,
        .y = 0,
        .z = 0,
        .w = 1 << 16
    };
    tempVec.x = vec->x;
    tempVec.y = vec->y;
    tempVec.z = vec->z;
    csVec3 pos;
    csMatGetPosition(&pos,mat);
    csFixed x = csFixedMul(csMatGet(mat,0,0),tempVec.x) + csFixedMul(csMatGet(mat,1,0),tempVec.x) + csFixedMul(csMatGet(mat,2,0),tempVec.x) + csFixedMul(csMatGet(mat,3,0),tempVec.x) - pos.x;
    csFixed y = csFixedMul(csMatGet(mat,0,1),tempVec.y) + csFixedMul(csMatGet(mat,1,1),tempVec.y) + csFixedMul(csMatGet(mat,2,1),tempVec.y) + csFixedMul(csMatGet(mat,3,1),tempVec.y) - pos.y;
    csFixed z = csFixedMul(csMatGet(mat,0,2),tempVec.z) + csFixedMul(csMatGet(mat,1,2),tempVec.z) + csFixedMul(csMatGet(mat,2,2),tempVec.z) + csFixedMul(csMatGet(mat,3,2),tempVec.z) - pos.z;
    /*csFixed w = csFixedMul(csMatGet(mat,0,3),tempVec.w) + csFixedMul(csMatGet(mat,1,3),tempVec.w) + csFixedMul(csMatGet(mat,2,3),tempVec.z) + csFixedMul(csMatGet(mat,3,3),tempVec.w);*/

    dest->x = x;
    dest->y = y;
    dest->z = z;
    csVec3Normalize(dest,dest);
}
static inline void csVec3DivS(csVec3 *dest,const csVec3 *a, csFixed b){v3d_div_s(dest,a,b);}


static inline csFixed csVec3Dot(const csVec3 *a,const csVec3 *b){ return v3d_dot(a,b);}
static inline void csVec3Cross(csVec3 *dest, const csVec3 *a, const csVec3 *b){v3d_cross(dest,a,b);}

static inline void csVec3Print(const csVec3 *vec)
{
    printf("X : %f Y : %f Z : %f\n",csFixedToFloat(vec->x),csFixedToFloat(vec->y),csFixedToFloat(vec->z));
}

#endif