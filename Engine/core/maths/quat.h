#ifndef CODESTARS_ENGINE_CORE_MATHS_QUAT_H
#define CODESTARS_ENGINE_CORE_MATHS_QUAT_H
#include "defines.h"
#include "vec.h"
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

#define FIXED_POINT_ONE (1 << 16)
#define FIXED_POINT_TWO (2 << 16)

extern void csQuatToMat(const qf16 *q, mf16 *matrix);


static inline void csQuatRotateVector(csVec3 *dest, const csQuat *q, const csVec3 *v) { qf16_rotate(dest,q,v);}
static void csQuatFromVector(csQuat *q, const csVec3 *v,csFixed a) {qf16_from_v3d(q,v,a);}
static void csQuatToVector(csVec3 *v,const csQuat *q){qf16_to_v3d(v,q);}

#endif
