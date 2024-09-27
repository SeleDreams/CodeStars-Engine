#ifndef CODESTARS_ENGINE_CORE_MATHS_MAT_H
#define CODESTARS_ENGINE_CORE_MATHS_MAT_H
#include <fixmatrix.h>

#include "maths.h"
#include "vec.h"
#include "quat.h"


inline void csMatFill(csMat4 *dest, const csFixed value) {
    mf16_fill(dest, value);
}


static void csMatFillDiagonal(csMat4 *dest, const csFixed value) { mf16_fill_diagonal(dest, value); }
static void csMatInit(csMat4 *dest) {
    mf16_initialize(dest, 4, 4);
    csMatFillDiagonal(dest,csFixedFromInt(1));
}

inline void csMatSet(csMat4 *a, int row, int column, int value) {
    a->data[column * a->rows + row] = value;
}

inline int csMatGet(const csMat4 *a, int row, int column) {
    return a->data[column * a->rows + row];
}

static void csMatMul(csMat4 *dest, const csMat4 *a, const csMat4 *b) {
    mf16_mul(dest, a, b);
}

inline void csMatMulAT(csMat4 *dest, const csMat4 *at, const csMat4 *b) { mf16_mul_at(dest, at, b); }
inline void csMatMulBT(csMat4 *dest, const csMat4 *a, const csMat4 *bt) { mf16_mul_bt(dest, a, bt); }
inline void csMatAdd(csMat4 *dest, const csMat4 *a, const csMat4 *b) { mf16_add(dest, a, b); }
inline void csMatSub(csMat4 *dest, const csMat4 *a, const csMat4 *b) { mf16_sub(dest, a, b); }
inline void csMatTranspose(csMat4 *dest, const csMat4 *mat) { mf16_transpose(dest, mat); }
inline void csMatMulS(csMat4 *dest, const csMat4 *mat, const csFixed scalar) { mf16_mul_s(dest, mat, scalar); }

static void csMatPositionSet(csMat4 *dest, const csVec3 *pos) {
    csMatSet(dest, 0, 3, pos->x);
    csMatSet(dest, 1, 3, pos->y);
    csMatSet(dest, 2, 3, pos->z);
}

static void csMatTranslate(csMat4 *dest, const csVec3 *pos) {
    static csMat4 translation;
    csMatInit(&translation);
    csMatPositionSet(&translation,pos);
    csMatMul(dest,dest,&translation);
}

inline void csMatGetPosition(csVec3 *dest, csMat4 *mat) {
    dest->x = csMatGet(mat, 0, 3);
    dest->y = csMatGet(mat, 1, 3);
    dest->z = csMatGet(mat, 2, 3);
}

static void csMatScaleSet(csMat4 *dest, const csVec3 *scale) {
    csMatSet(dest, 0, 0, scale->x);
    csMatSet(dest, 1, 1, scale->y);
    csMatSet(dest, 2, 2, scale->z);
}

static void csMatScale(csMat4 *dest, const csVec3 *p_scale) {
    static csMat4 scale;
    csMatInit(&scale);
    csMatScaleSet(&scale,p_scale);
    csMatMul(dest,dest,&scale);
}

static void csMatRotationSet(csMat4 *dest, const csQuat *rot) {
    csQuatToMat(rot, dest);
}

static void csMatRotate(csMat4 *dest, const csQuat *p_rot) {
    static csMat4 rot;
    csMatInit(&rot);
    csMatRotationSet(&rot,p_rot);
    csMatMul(dest,dest,&rot);
}


void csMatPerspective(csFixed fovy, csFixed aspect, csFixed zNear, csFixed zFar, csMat4 *projection);


void csMatToFloat(csFMat4 *dest, const csMat4 *mat, int print);

#endif
