#ifndef CODESTARS_ENGINE_CORE_MATHS_H
#define CODESTARS_ENGINE_CORE_MATHS_H
#include "stdlib.h"
#include <libfixmath/fix16.h>
#define FIXMATRIX_MAX_SIZE 4
#include <fixquat.h>
#include <fixmatrix.h>
#include "fixvector3d.h"
#include "fixvector2d.h"
typedef fix16_t csFixed;
typedef qf16 csQuat;
typedef float csFMat4[16];
typedef mf16 csMat4;

static inline csFixed csFixedDegToRad(csFixed a) { return fix16_deg_to_rad(a); }
static inline csFixed csFixedRadToDeg(csFixed a) { return fix16_rad_to_deg(a); }

static inline csFixed csFixedFromInt(int value) { return fix16_from_int(value);}
static inline csFixed csFixedFromFloat(float value) { return fix16_from_float(value);}
static inline float csFixedToFloat(csFixed value) { return fix16_to_float(value); }
static inline int csFixedToInt(csFixed value) { return fix16_to_int(value); }
static inline csFixed csFixedAdd(csFixed a,csFixed b) {return fix16_add(a,b);}
static inline csFixed csFixedSub(csFixed a,csFixed b) {return fix16_sub(a,b);}
static inline csFixed csFixedMul(csFixed a,csFixed b) { return fix16_mul(a,b); }
static inline csFixed csFixedDiv(csFixed a,csFixed b) { return fix16_div(a,b);}

static inline csFixed csFixedTan(csFixed a) { return fix16_tan(a);}
#endif
