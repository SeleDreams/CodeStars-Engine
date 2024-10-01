#ifndef CODESTARS_ENGINE_CORE_MATHS_MAT_H
#define CODESTARS_ENGINE_CORE_MATHS_MAT_H
#include <fixmatrix.h>
#include "vec.h"
#include "quat.h"

extern csMat4 cs_matrix_cache[3];
extern csQuat cs_quat_cache[3];
extern csVec3 cs_vec_cache[3];

static inline void csMatFill(csMat4 *dest, const csFixed value) {
    mf16_fill(dest, value);
}

static inline void csMatFillDiagonal(csMat4 *dest, const csFixed value) { mf16_fill_diagonal(dest, value); }
static inline void csMatInit(csMat4 *dest) {
    csMatFillDiagonal(dest,csFixedFromInt(1));
}

static inline int csMatGet(const csMat4 *a, int row, int column) {
    return a->data[column * a->rows + row];
}

static inline void csMatMul(csMat4 *dest, const csMat4 *a, const csMat4 *b) {
    mf16_mul(dest, a, b);
}

static inline void csMatMulAT(csMat4 *dest, const csMat4 *at, const csMat4 *b) { mf16_mul_at(dest, at, b); }
static inline void csMatMulBT(csMat4 *dest, const csMat4 *a, const csMat4 *bt) { mf16_mul_bt(dest, a, bt); }
static inline void csMatAdd(csMat4 *dest, const csMat4 *a, const csMat4 *b) { mf16_add(dest, a, b); }
static inline void csMatSub(csMat4 *dest, const csMat4 *a, const csMat4 *b) { mf16_sub(dest, a, b); }
static inline void csMatTranspose(csMat4 *dest, const csMat4 *mat) { mf16_transpose(dest, mat); }
static inline void csMatMulS(csMat4 *dest, const csMat4 *mat, const csFixed scalar) { mf16_mul_s(dest, mat, scalar); }
static inline void csMatSet(csMat4 *a, int row, int column, int value) {
    a->data[column * a->rows + row] = value;
}
static inline void csMatPositionSet(csMat4 *dest, const csVec3 *pos) {
    dest->data[12] = pos->x;
    dest->data[13] = pos->y;
    dest->data[14] = pos->z;
}

static inline void csMatPositionGet(csVec3 *dest,const csMat4 *mat) {
    dest->x = mat->data[12];
    dest->y = mat->data[13];
    dest->z = mat->data[14];
}
static inline void csMatTranslate(csMat4 *dest, const csVec3 *pos) {
    csVec3 vec;
    csMatPositionGet(&vec,dest);
    csVec3Add(&vec,&vec,pos);
    csMatPositionSet(dest,&vec);
}

static inline void csMatScaleSet(csMat4 *dest, const csVec3 *scale) {
    dest->data[0] = scale->x;
    dest->data[5] = scale->y;
    dest->data[10] = scale->z;
}

static inline void csMatScaleGet(csVec3 *dest,const csMat4 *mat){
    dest->x =mat->data[0];
    dest->y = mat->data[5];
    dest->z = mat->data[10];
}

static inline void csMatScale(csMat4 *dest, const csVec3 *p_scale) {
    csVec3 vec;
    csMatScaleGet(&vec,dest);
    csVec3Add(&vec,&vec,p_scale);
    csMatScaleSet(dest,&vec);
}

static inline void csMatRotationSet(csMat4 *dest, const csQuat *rot) {
    csQuatToMat(rot, dest);
}

static inline void csMatRotationGet(csQuat *rot,const csMat4 *dest) {
    csMatToQuat(dest, rot);
}

static inline void csMatRotate(csMat4 *dest, const csQuat *p_rot) {
    csQuat quat;
    csMatRotationGet(&quat,dest);
    csQuatMul(&quat,&quat,p_rot);
    csMatRotationSet(dest,&quat);
}


static inline void csMatPerspective(csFixed fovy, csFixed aspect, csFixed zNear, csFixed zFar, csMat4 *projection) {
    csFixed f = csFixedDiv(csFixedFromFloat(1.0f), csFixedTan(csFixedDiv(fovy, csFixedFromFloat(2.0f))));
    csFixed rangeInv = csFixedDiv(csFixedFromFloat(1.0f), csFixedSub(zNear, zFar));
    csFixed *matrix = projection->data;
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


static inline void csMatToFloat(csFMat4 *dest, const csMat4 *mat) {
    for (int i = 0; i < 16;i++)
    {
        (*dest)[i] = csFixedToFloat(mat->data[i]);
    }
}
static inline void csMatTo2012(csMat4_2012 *dest, const csMat4 *mat) {
    for (int i = 0; i < 16;i++)
    {
        (*dest)[i] = mat->data[i] >> 4;
    }
}
#endif
