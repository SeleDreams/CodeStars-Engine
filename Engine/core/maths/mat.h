#ifndef CODESTARS_ENGINE_CORE_MATHS_MAT_H
#define CODESTARS_ENGINE_CORE_MATHS_MAT_H
#include <fixmatrix.h>
#include "vec.h"
#include "quat.h"

extern csMat4 cs_matrix_cache[3];
extern csQuat cs_quat_cache[3];
extern csVec3 cs_vec_cache[3];

inline void csMatFill(csMat4 *dest, const csFixed value) {
    mf16_fill(dest, value);
}

inline void csMatFillDiagonal(csMat4 *dest, const csFixed value) { mf16_fill_diagonal(dest, value); }
inline void csMatInit(csMat4 *dest) {
    mf16_initialize(dest, 4, 4);
    csMatFillDiagonal(dest,csFixedFromInt(1));
}



inline int csMatGet(const csMat4 *a, int row, int column) {
    return a->data[column * a->rows + row];
}

inline void csMatMul(csMat4 *dest, const csMat4 *a, const csMat4 *b) {
    mf16_mul(dest, a, b);
}

inline void csMatMulAT(csMat4 *dest, const csMat4 *at, const csMat4 *b) { mf16_mul_at(dest, at, b); }
inline void csMatMulBT(csMat4 *dest, const csMat4 *a, const csMat4 *bt) { mf16_mul_bt(dest, a, bt); }
inline void csMatAdd(csMat4 *dest, const csMat4 *a, const csMat4 *b) { mf16_add(dest, a, b); }
inline void csMatSub(csMat4 *dest, const csMat4 *a, const csMat4 *b) { mf16_sub(dest, a, b); }
inline void csMatTranspose(csMat4 *dest, const csMat4 *mat) { mf16_transpose(dest, mat); }
inline void csMatMulS(csMat4 *dest, const csMat4 *mat, const csFixed scalar) { mf16_mul_s(dest, mat, scalar); }
inline void csMatSet(csMat4 *a, int row, int column, int value) {
    a->data[column * a->rows + row] = value;
}
inline void csMatPositionSet(csMat4 *dest, const csVec3 *pos) {
    csMatSet(dest, 0, 3, pos->x);
    csMatSet(dest, 1, 3, pos->y);
    csMatSet(dest, 2, 3, pos->z);
}

inline void csMatTranslate(csMat4 *dest, const csVec3 *pos) {
    csMatInit(&cs_matrix_cache[0]);
    csMatPositionSet(&cs_matrix_cache[0],pos);
    csMatMul(dest,dest,&cs_matrix_cache[0]);
}

inline void csMatGetPosition(csVec3 *dest, csMat4 *mat) {
    dest->x = csMatGet(mat, 0, 3);
    dest->y = csMatGet(mat, 1, 3);
    dest->z = csMatGet(mat, 2, 3);
}

inline void csMatScaleSet(csMat4 *dest, const csVec3 *scale) {
    csMatSet(dest, 0, 0, scale->x);
    csMatSet(dest, 1, 1, scale->y);
    csMatSet(dest, 2, 2, scale->z);
}

inline void csMatScale(csMat4 *dest, const csVec3 *p_scale) {
    csMatInit(&cs_matrix_cache[0]);
    csMatScaleSet(&cs_matrix_cache[0],p_scale);
    csMatMul(dest,dest,&cs_matrix_cache[0]);
}

inline void csMatRotationSet(csMat4 *dest, const csQuat *rot) {
    csQuatToMat(rot, dest);
}

inline void csMatRotate(csMat4 *dest, const csQuat *p_rot) {
    csMatGetPosition(&cs_vec_cache[0],dest);

    csMatInit(&cs_matrix_cache[0]);
    csMatRotationSet(&cs_matrix_cache[0],p_rot);

    csMatMul(dest,dest,&cs_matrix_cache[0]);

    csMatPositionSet(dest,&cs_vec_cache[0]);
}


void csMatPerspective(csFixed fovy, csFixed aspect, csFixed zNear, csFixed zFar, csMat4 *projection);


void csMatToFloat(csFMat4 *dest, const csMat4 *mat, int print);

#endif
