#ifndef ARITHMETIC_H
#define ARITHMETIC_H
#include "defines.h"
static csFixed csFixedDegToRad(csFixed a) { return fix16_deg_to_rad(a); }
static csFixed csFixedRadToDeg(csFixed a) { return fix16_rad_to_deg(a); }

inline csFixed csFixedAdd(csFixed a,csFixed b) {return fix16_add(a,b);}
inline csFixed csFixedSub(csFixed a,csFixed b) {return fix16_sub(a,b);}
inline csFixed csFixedMul(csFixed a,csFixed b) { return fix16_mul(a,b); }
inline csFixed csFixedDiv(csFixed a,csFixed b) { return fix16_div(a,b);}

inline csFixed csFixedTan(csFixed a) { return fix16_tan(a);}
#endif
