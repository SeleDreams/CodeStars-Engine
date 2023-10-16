#ifndef CODESTARS_ENGINE_CORE_MATHS_MAT_H
#define CODESTARS_ENGINE_CORE_MATHS_MAT_H
#include "maths.h"
typedef mf16 csMat4;
typedef float csFMat4[4][4];
static inline void csMatInit(csMat4 *dest) {dest->rows = 4; dest->columns = 4;}
static inline void csMatFill(csMat4 *dest, const fixed_int value) { mf16_fill(dest,value);}
static inline void csMatSet(csMat4 *a, int row, int column, int value) {
    a->data[row][column] =  fix16_from_int(value);
}
static inline int csMatGet(const csMat4 *a,int row, int column)
{
    return fix16_to_int(a->data[row][column]);
}
static inline void csMatFillDiagonal(csMat4 *dest, const int value) {mf16_fill_diagonal(dest,fix16_from_int(value));}
static inline void csMatMul(csMat4 *dest, const csMat4 *a, const csMat4 *b) { mf16_mul(dest,a,b); }
static inline void csMatMulAT(csMat4 *dest, const csMat4 *at,const csMat4 *b) { mf16_mul_at(dest,at,b);}
static inline void csMatMulBT(csMat4 *dest, const csMat4 *a, const csMat4 *bt) {mf16_mul_bt(dest,a,bt);}
static inline void csMatAdd(csMat4 *dest, const csMat4 *a, const csMat4 *b) {mf16_add(dest,a,b);}
static inline void csMatSub(csMat4 *dest,const csMat4 *a, const csMat4 *b) {mf16_sub(dest,a,b);}
static inline void csMatTranspose(csMat4 *dest,const csMat4 *mat) {mf16_transpose(dest,mat);}
static inline void csMatMulS(csMat4 *dest,const csMat4 *mat, const int scalar) {mf16_mul_s(dest,mat,fix16_from_int(scalar));}
extern void csMatToFloat(csFMat4 *dest, const csMat4 *mat);
#endif
