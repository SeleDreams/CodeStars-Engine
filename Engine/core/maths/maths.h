#ifndef CODESTARS_ENGINE_CORE_MATHS_H
#define CODESTARS_ENGINE_CORE_MATHS_H
#include "stdlib.h"
#include "libs/libfixmatrix/libfixmath/libfixmath/fix16.h"
#define FIXMATRIX_MAX_SIZE 8
#include "libs/libfixmatrix/fixquat.h"
#include "libs/libfixmatrix/fixmatrix.h"
#include "libs/libfixmatrix/fixvector3d.h"
#include "libs/libfixmatrix/fixvector2d.h"
typedef fix16_t csFixed;
typedef qf16 csQuat;
typedef mf16 csMat4;

static inline csFixed csFixedDegToRad(csFixed a) { return fix16_deg_to_rad(a); }
static inline csFixed csFixedRadToDeg(csFixed a) { return fix16_rad_to_deg(a); }

static inline csFixed csFixedFromInt(int value) { return fix16_from_int(value);}
static inline csFixed csFixedFromFloat(float value) { return fix16_from_float(value);}
static inline float csFixedToFloat(csFixed value) { return fix16_to_float(value); }
static inline int csFixedToInt(csFixed value) { return fix16_to_int(value); }

static inline csFixed csFixedMul(csFixed a,csFixed b) { return fix16_mul(a,b); }
static inline csFixed csFixedDiv(csFixed a,csFixed b) { return fix16_div(a,b);}

static inline csFixed csFixedTan(csFixed a) { return fix16_tan(a);}
#endif