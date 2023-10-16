#ifndef CODESTARS_ENGINE_CORE_MATHS_H
#define CODESTARS_ENGINE_CORE_MATHS_H
#include "stdlib.h"
#include "libs/libfixmatrix/libfixmath/libfixmath/fix16.h"
#define FIXMATRIX_MAX_SIZE 8
#include "libs/libfixmatrix/fixmatrix.h"
#include "libs/libfixmatrix/fixvector3d.h"
#include "libs/libfixmatrix/fixvector2d.h"
typedef fix16_t fixed_int;
static inline fixed_int csFixedIntFromInt(int value) { return fix16_from_int(value);}
static inline fixed_int csFixedIntFromFloat(float value) { return fix16_from_float(value);}
#endif