#ifndef CODESTARS_ENGINE_CORE_MATHS_MAT_H
#define CODESTARS_ENGINE_CORE_MATHS_MAT_H
#include "maths.h"
#include "vec.h"
#include <math.h>
#include "quat.h"

typedef float csFMat4[4][4];

static inline void csMatFill(csMat4 *dest, const csFixed value) { mf16_fill(dest,value);}
static inline void csMatFillDiagonal(csMat4 *dest, const int value) {mf16_fill_diagonal(dest,value);}
static inline void csMatInit(csMat4 *dest) {dest->rows = 4; dest->columns = 4; csMatFill(dest,0);}
static inline void csMatSet(csMat4 *a, int row, int column, int value) {
    a->data[row][column] =  value;
}
static inline int csMatGet(const csMat4 *a,int row, int column)
{
    return a->data[row][column];
}
static inline void csMatMul(csMat4 *dest, const csMat4 *a, const csMat4 *b) { mf16_mul(dest,a,b); }
static inline void csMatMulAT(csMat4 *dest, const csMat4 *at,const csMat4 *b) { mf16_mul_at(dest,at,b);}
static inline void csMatMulBT(csMat4 *dest, const csMat4 *a, const csMat4 *bt) {mf16_mul_bt(dest,a,bt);}
static inline void csMatAdd(csMat4 *dest, const csMat4 *a, const csMat4 *b) {mf16_add(dest,a,b);}
static inline void csMatSub(csMat4 *dest,const csMat4 *a, const csMat4 *b) {mf16_sub(dest,a,b);}
static inline void csMatTranspose(csMat4 *dest,const csMat4 *mat) {mf16_transpose(dest,mat);}
static inline void csMatMulS(csMat4 *dest,const csMat4 *mat, const csFixed scalar) {mf16_mul_s(dest,mat,scalar);}

static inline void csMatSetPosition(csMat4 *dest,const csVec3 *pos)
{
    csMatSet(dest,3,0,pos->x);
    csMatSet(dest,3,1,pos->y);
    csMatSet(dest,3,2,pos->z);
}

static inline csMat4 csMatTranslate(const csMat4 *src,const csVec3 *pos)
{
    csMat4 translation;
    csMatInit(&translation);
    csMatFillDiagonal(&translation,1 << 16);
    csMatSet(&translation,3,0,csMatGet(src,3,0) + pos->x);
    csMatSet(&translation,3,1,csMatGet(src,3,1) + pos->y);
    csMatSet(&translation,3,2, csMatGet(src,3,2) + pos->z);
    return translation;
}

static inline void csMatGetPosition(csVec3 *dest, csMat4 *mat)
{
    dest->x = csMatGet(mat,3,0);
    dest->y = csMatGet(mat,3,1);
    dest->z = csMatGet(mat,3,2);
}

static inline void csMatScale(csMat4 *dest, const csVec3 *scale)
{
    csMatSet(dest,0,0,scale->x);
    csMatSet(dest,1,1,scale->y);
    csMatSet(dest,2,2,scale->z);
}

static inline void csMatSetRotation(csMat4 *dest, const csQuat *rot)
{
    csQuatToMatrix(dest,rot);
}

static inline void csMatPerspective(csMat4 *mat,csFixed fov,csFixed aspect,csFixed near,csFixed far)
{
    csFixed halfFOV = csFixedTan(csFixedDiv(fov,2));
    csMatFill(mat,csFixedFromInt(0));
    csMatSet(mat,0,0,csFixedDiv(1 << 16,csFixedMul(aspect,halfFOV)));
    csMatSet(mat,1,1,csFixedDiv(1 << 16,halfFOV));
    csMatSet(mat,2,2,csFixedDiv(far,near - far));
    csMatSet(mat,2,3,csFixedFromInt(-1));
    csMatSet(mat,3,2,csFixedDiv(csFixedMul(csFixedMul(far,near),csFixedFromInt(-1)),far - near));
    
   /*int tangent = csFixedTan(csFixedDegToRad(csFixedDiv(fov,csFixedFromInt(2))));
    csMatInit(mat);
    csMatSet(mat,0,0,csFixedDiv(tangent,csFixedFromInt(2)));
    csMatSet(mat,1,1,csFixedDiv(csFixedDiv(aspect,csFixedFromInt(2)),tangent));
    csMatSet(mat,2,2,csFixedDiv(csFixedMul(far,csFixedFromInt(-1)) + near,far - near));
    csMatSet(mat,2,3,csFixedFromInt(-1));
    csMatSet(mat,3,2,csFixedDiv(csFixedMul(csFixedMul(csFixedFromInt(-2),far),near),far - near));
    */

}
extern void csMatToFloat(csFMat4 *dest, const csMat4 *mat, int print);

#endif
