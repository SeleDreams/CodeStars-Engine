#ifndef CODESTARS_ENGINE_CORE_MATHS_MAT_H
#define CODESTARS_ENGINE_CORE_MATHS_MAT_H
#include "maths.h"
typedef mf16 csMat4;
typedef float csFMat4[4][4];
static inline void csMatInit(csMat4 *dest) {dest->rows = 4; dest->columns = 4;}
static inline void csMatFill(csMat4 *dest, const fixed_int value) { mf16_fill(dest,value);}
static inline void csMatFillDiagonal(csMat4 *dest, const fixed_int value) {mf16_fill_diagonal(dest,value);}
static inline void csMatMul(csMat4 *dest, const csMat4 *a, const csMat4 *b) { mf16_mul(dest,a,b); }
static inline void csMatMulAT(csMat4 *dest, const csMat4 *at,const csMat4 *b) { mf16_mul_at(dest,at,b);}
static inline void csMatMulBT(csMat4 *dest, const csMat4 *a, const csMat4 *bt) {mf16_mul_bt(dest,a,bt);}
static inline void csMatAdd(csMat4 *dest, const csMat4 *a, const csMat4 *b) {mf16_add(dest,a,b);}
static inline void csMatSub(csMat4 *dest,const csMat4 *a, const csMat4 *b) {mf16_sub(dest,a,b);}
static inline void csMatTranspose(csMat4 *dest,const csMat4 *mat) {mf16_transpose(dest,mat);}
static inline void csMatMulS(csMat4 *dest,const csMat4 *mat, const fixed_int scalar) {mf16_mul_s(dest,mat,scalar);}
extern void csMatToFloat(csFMat4 *dest, const csMat4 *mat);
#endif
