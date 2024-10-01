#ifndef CODESTARS_ENGINE_CORE_MATHS_QUAT_H
#define CODESTARS_ENGINE_CORE_MATHS_QUAT_H
#include "defines.h"
#include "vec.h"
#include <fixquat.h>
static inline void csQuatConjugate(csQuat *dest, const csQuat *q) { qf16_conj(dest,q);}
static inline void csQuatMul(csQuat *dest, const csQuat *q, const csQuat *r) {qf16_mul(dest,q,r);}
static inline void csQuatAdd(csQuat *dest, const csQuat *q, const csQuat *r) {qf16_add(dest,q,r);}
static inline void csQuatMulS(csQuat *dest, const csQuat *q, csFixed s) {qf16_mul_s(dest,q,s);}
static inline void csQuatDivS(csQuat *dest, const csQuat *q, csFixed s) {qf16_div_s(dest,q,s);}
static inline csFixed csQuatDot(const csQuat *q, const csQuat *r) { return qf16_dot(q,r);}
static inline csFixed csQuatLength(const csQuat *q) { return qf16_norm(q);}
static inline void csQuatNormalize(csQuat *dest, const csQuat *q) {qf16_normalize(dest,q);}
static inline void csQuatPow(csQuat *dest, const csQuat *q, csFixed power) { qf16_pow(dest,q,power);}
static inline void csQuatAvg(csQuat *dest, const csQuat *q1, const csQuat *q2, csFixed weight) { qf16_avg(dest,q1,q2,weight);}
static inline void csQuatFromAxisAngle(csQuat *dest,const csVec3 *axis, csFixed angle) {qf16_from_axis_angle(dest,axis,angle);}

static inline void csQuatToMat(const qf16 *q, mf16 *matrix) {
    qf16_to_matrix(matrix,q);
    /*fix16_t xx = csFixedMul(q->b, q->b);
    fix16_t xy = csFixedMul(q->b, q->c);
    fix16_t xz = csFixedMul(q->b, q->d);
    fix16_t xw = csFixedMul(q->b, q->a);

    fix16_t yy = csFixedMul(q->c, q->c);
    fix16_t yz = csFixedMul(q->c, q->d);
    fix16_t yw = csFixedMul(q->c, q->a);

    fix16_t zz = csFixedMul(q->d, q->d);
    fix16_t zw = csFixedMul(q->d, q->a);

    matrix->rows = 4;
    matrix->columns = 4;
    matrix->errors = 0;

    matrix->data[0] = FIXED_POINT_ONE - csFixedMul(FIXED_POINT_TWO, yy + zz);
    matrix->data[1] = csFixedMul(FIXED_POINT_TWO, xy + zw);
    matrix->data[2] = csFixedMul(FIXED_POINT_TWO, xz - yw);
    matrix->data[3] = 0;

    matrix->data[4] = csFixedMul(FIXED_POINT_TWO, xy - zw);
    matrix->data[5] = FIXED_POINT_ONE - csFixedMul(FIXED_POINT_TWO, xx + zz);
    matrix->data[6] = csFixedMul(FIXED_POINT_TWO, yz + xw);
    matrix->data[7] = 0;

    matrix->data[8] = csFixedMul(FIXED_POINT_TWO, xz + yw);
    matrix->data[9] = csFixedMul(FIXED_POINT_TWO, yz - xw);
    matrix->data[10] = FIXED_POINT_ONE - csFixedMul(FIXED_POINT_TWO, xx + yy);
    matrix->data[11] = 0;

    matrix->data[12] = 0;
    matrix->data[13] = 0;
    matrix->data[14] = 0;
    matrix->data[15] = FIXED_POINT_ONE;*/
}

static inline void csMatToQuat(const mf16 *matrix, qf16 *q) {

}


static inline void csQuatRotateVector(csVec3 *dest, const csQuat *q, const csVec3 *v) { qf16_rotate(dest,q,v);}
static void csQuatFromVector(csQuat *q, const csVec3 *v,csFixed a) {qf16_from_v3d(q,v,a);}
static void csQuatToVector(csVec3 *v,const csQuat *q){qf16_to_v3d(v,q);}

#endif
