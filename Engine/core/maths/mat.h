#ifndef CODESTARS_ENGINE_CORE_MATHS_MAT_H
#define CODESTARS_ENGINE_CORE_MATHS_MAT_H
#include "maths.h"
#include "vec.h"
#include <math.h>
#include "quat.h"


static inline void csMatFill(csMat4 *dest, const csFixed value) {
    mf16_fill(dest,value);
}
static inline void csMatInit(csMat4 *dest) {
    mf16_initialize(dest,4,4);
}

static inline void csMatFillDiagonal(csMat4 *dest, const csFixed value) {mf16_fill_diagonal(dest,value);}

static inline void csMatSet(csMat4 *a, int row, int column, int value) {
    a->data[column * a->rows + row] = value;
}

static inline int csMatGet(const csMat4 *a,int row, int column)
{
    return a->data[column * a->rows + row];
}

static inline void csMatMul(csMat4 *dest, const csMat4 *a, const csMat4 *b) {
    mf16_mul(dest,a,b);
}
static inline void csMatMulAT(csMat4 *dest, const csMat4 *at,const csMat4 *b) { mf16_mul_at(dest,at,b);}
static inline void csMatMulBT(csMat4 *dest, const csMat4 *a, const csMat4 *bt) {mf16_mul_bt(dest,a,bt);}
static inline void csMatAdd(csMat4 *dest, const csMat4 *a, const csMat4 *b) {mf16_add(dest,a,b);}
static inline void csMatSub(csMat4 *dest,const csMat4 *a, const csMat4 *b) {mf16_sub(dest,a,b);}
static inline void csMatTranspose(csMat4 *dest,const csMat4 *mat) {mf16_transpose(dest,mat);}
static inline void csMatMulS(csMat4 *dest,const csMat4 *mat, const csFixed scalar) {mf16_mul_s(dest,mat,scalar);}

static inline void csMatSetPosition(csMat4 *dest,const csVec3 *pos)
{
    csMatSet(dest,0,3,pos->x);
    csMatSet(dest,1,3,pos->y);
    csMatSet(dest,2,3,pos->z);
}

static inline csMat4 csMatTranslate(const csMat4 *src,const csVec3 *pos)
{
    csMat4 translation;
    csMatInit(&translation);
    csMatFillDiagonal(&translation,1 << 16);
    csMatSet(&translation,0,3,csMatGet(src,0,3) + pos->x);
    csMatSet(&translation,1,3,csMatGet(src,1,3) + pos->y);
    csMatSet(&translation,2,3, csMatGet(src,2,3) + pos->z);
    return translation;
}

static inline void csMatGetPosition(csVec3 *dest, csMat4 *mat)
{
    dest->x = csMatGet(mat,0,3);
    dest->y = csMatGet(mat,1,3);
    dest->z = csMatGet(mat,2,3);
}

static inline void csMatScale(csMat4 *dest, const csVec3 *scale)
{
    csMatSet(dest,0,0,scale->x);
    csMatSet(dest,1,1,scale->y);
    csMatSet(dest,2,2,scale->z);
}

static inline void csMatSetRotation(csMat4 *dest, const csQuat *rot)
{
    csQuatToMat(rot,dest);
}


static inline void csMatPerspective(csFixed fovy, csFixed aspect, csFixed zNear, csFixed zFar, csFixed* matrix) {
    csFixed f = csFixedDiv(csFixedFromFloat(1.0f), csFixedTan(csFixedDiv(fovy, csFixedFromFloat(2.0f))));
    csFixed rangeInv = csFixedDiv(csFixedFromFloat(1.0f), csFixedSub(zNear, zFar));

    matrix[0] = csFixedDiv(f, aspect);
    matrix[1] = 0;
    matrix[2] = 0;
    matrix[3] = 0;

    matrix[4] = 0;
    matrix[5] = f;
    matrix[6] = 0;
    matrix[7] = 0;

    matrix[8] = 0;
    matrix[9] = 0;
    matrix[10] = csFixedMul(csFixedAdd(zFar, zNear), rangeInv);
    matrix[11] = -csFixedFromFloat(1.0f);

    matrix[12] = 0;
    matrix[13] = 0;
    matrix[14] = csFixedMul(csFixedMul(csFixedFromFloat(2.0f), zFar), csFixedMul(zNear, rangeInv));
    matrix[15] = 0;
}




extern void csMatToFloat(csFMat4 *dest, const csMat4 *mat, int print);

#endif
