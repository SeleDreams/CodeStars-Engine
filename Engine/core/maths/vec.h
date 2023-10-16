#ifndef CODESTARS_ENGINE_CORE_MATHS_VEC_H
#define CODESTARS_ENGINE_CORE_MATHS_VEC_H
#include "maths.h"
typedef v3d csVec3;
typedef struct csVec4 {
    fixed_int x;
    fixed_int y;
    fixed_int z;
    fixed_int w;
} csVec4;
typedef v2d csVec2;

static inline void csVec3Add(csVec3 *dest, const csVec3 *a,const csVec3 *b) {v3d_add(dest,a,b);}
static inline void csVec3Sub(csVec3 *dest, const csVec3 *a, const csVec3 *b) {v3d_sub(dest,a,b);}
static inline void csVec3MulS(csVec3 *dest,const csVec3 *a,fixed_int b){v3d_mul_s(dest,a,b);}
static inline void csVec3DivS(csVec3 *dest,const csVec3 *a, fixed_int b){v3d_div_s(dest,a,b);}

static inline fixed_int csVec3Length(const csVec3 *a) {return v3d_norm(a);}
static inline void csVec3Normalize(csVec3 *dest,const csVec3 *a){v3d_normalize(dest,a);}
static inline fixed_int csVec3Dot(const csVec3 *a,const csVec3 *b){ return v3d_dot(a,b);}
static inline void csVec3Cross(csVec3 *dest, const csVec3 *a, const csVec3 *b){v3d_cross(dest,a,b);}

#endif