#ifndef CODESTARS_ENGINE_CORE_MATHS_VEC_H
#define CODESTARS_ENGINE_CORE_MATHS_VEC_H
#include "maths.h"
typedef struct 
{ 
    fixed_int x; 
    fixed_int y; 
    fixed_int z;
    fixed_int w;
} csVec4;

typedef struct 
{ 
    fixed_int x; 
    fixed_int y; 
    fixed_int z;
} csVec3;

#endif