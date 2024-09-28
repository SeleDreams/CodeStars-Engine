#ifndef MATH_DEFINES_H
#define MATH_DEFINES_H
#include <libfixmath/fix16.h>
#define FIXMATRIX_MAX_SIZE 4
#include <fixquat.h>
#include <fixmatrix.h>

typedef fix16_t csFixed;
typedef qf16 csQuat;
typedef float csFMat4[16];
typedef mf16 csMat4;
typedef int csMat4_2012[16];

#define csFixedFromInt(value) ((csFixed)F16(value))
#define csFixedFromFloat(value) ((csFixed)F16(value))

#define csFixedToFloat(value) ((float)(value >> 16))
#define csFixedToInt(value) ((int)(value >> 16))
#endif
