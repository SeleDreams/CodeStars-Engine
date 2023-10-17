#ifndef CODESTARS_ENGINE_CORE_MATHS_QUAT_H
#define CODESTARS_ENGINE_CORE_MATHS_QUAT_H
#include "maths.h"
static inline void csMatSet(csMat4 *a, int row, int column, int value);

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
static inline void csQuatToMatrix(csMat4 *dest, const csQuat *q) { 
    csFixed w,x,y,z,
            xx,yy,zz,
            xy,yz,xz,
            wx,wy,wz,
            norm,s;
    norm = csQuatLength(q);
    s = norm > 0 << 16 ? csFixedDiv(2 << 16,norm) : 0 << 16;

    x = q->a;
    y = q->b;
    z = q->c;
    w = q->d;

    xx = csFixedMul(csFixedMul(s,x),x);
    yy = csFixedMul(csFixedMul(s,y),y);
    zz = csFixedMul(csFixedMul(s,z),z);

    xy = csFixedMul(csFixedMul(s,x),y);
    yz = csFixedMul(csFixedMul(s,y),z);
    xz = csFixedMul(csFixedMul(s,x),z);

    wx = csFixedMul(csFixedMul(s,w),x);
    wy = csFixedMul(csFixedMul(s,w),y);
    wz = csFixedMul(csFixedMul(s,w),z);

    csMatSet(dest,0,0,(1 << 16) - yy - zz);
    csMatSet(dest,1,1,(1 << 16) - xx - zz);
    csMatSet(dest,2,2,(1 << 16) - xx - yy);

    csMatSet(dest,0,1,xy + wz);
    csMatSet(dest,1,2,yz + wx);
    csMatSet(dest,2,0,xz + wy);

    csMatSet(dest,1,0,xy - wz);
    csMatSet(dest,2,1,yz - wx);
    csMatSet(dest,0,2,xz - wy);

    csMatSet(dest,0,3,0);
    csMatSet(dest,1,3,0);
    csMatSet(dest,2,3,0);
    csMatSet(dest,3,0,0);
    csMatSet(dest,3,1,0);
    csMatSet(dest,3,2,0);
    csMatSet(dest,3,3,1 << 16);
    
}
static inline void csQuatRotateVector(csVec3 *dest, const csQuat *q, const csVec3 *v) { qf16_rotate(dest,q,v);}
static inline void csQuatFromVector(csQuat *q, const csVec3 *v,csFixed a) {qf16_from_v3d(q,v,a);}
static inline void csQuatToVector(csVec3 *v,const csQuat *q){qf16_to_v3d(v,q);}

#endif