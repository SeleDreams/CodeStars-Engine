#ifndef ARITHMETIC_H
#define ARITHMETIC_H
#include "defines.h"
static csFixed csFixedDegToRad(csFixed a) { return fix16_deg_to_rad(a); }
static csFixed csFixedRadToDeg(csFixed a) { return fix16_rad_to_deg(a); }

static inline csFixed csFixedAdd(csFixed a,csFixed b) { return a + b;}
static inline csFixed csFixedSub(csFixed a,csFixed b) {return a - b;}
static inline csFixed csFixedMul(csFixed a,csFixed b) { return fix16_mul(a,b); }
static inline csFixed csFixedDiv(csFixed a,csFixed b) { return fix16_div(a,b);}
static inline csFixed csFixedDivUnsigned(csFixed a,csFixed b) {return fix16_div(a,b);}

static inline csFixed csFixedSqrt(csFixed a) { return fix16_sqrt(a);}
static inline csFixed csFixedTan(csFixed a) { return fix16_tan(a);}
#endif
