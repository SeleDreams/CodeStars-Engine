//
// Created by SeleDreams on 27/09/2024.
//
#include "quat.h"
#include "arithmetic.h"

void csQuatToMat(const qf16 *q, mf16 *matrix) {
    fix16_t xx = csFixedMul(q->b, q->b);
    fix16_t xy = csFixedMul(q->b, q->c);
    fix16_t xz = csFixedMul(q->b, q->d);
    fix16_t xw = csFixedMul(q->b, q->a);

    fix16_t yy = csFixedMul(q->c, q->c);
    fix16_t yz = csFixedMul(q->c, q->d);
    fix16_t yw = csFixedMul(q->c, q->a);

    fix16_t zz = csFixedMul(q->d, q->d);
    fix16_t zw = csFixedMul(q->d, q->a);

    matrix->rows = 4;
    matrix->columns = 4;
    matrix->errors = 0;

    matrix->data[0] = FIXED_POINT_ONE - csFixedMul(FIXED_POINT_TWO, yy + zz);
    matrix->data[1] = csFixedMul(FIXED_POINT_TWO, xy + zw);
    matrix->data[2] = csFixedMul(FIXED_POINT_TWO, xz - yw);
    matrix->data[3] = 0;

    matrix->data[4] = csFixedMul(FIXED_POINT_TWO, xy - zw);
    matrix->data[5] = FIXED_POINT_ONE - csFixedMul(FIXED_POINT_TWO, xx + zz);
    matrix->data[6] = csFixedMul(FIXED_POINT_TWO, yz + xw);
    matrix->data[7] = 0;

    matrix->data[8] = csFixedMul(FIXED_POINT_TWO, xz + yw);
    matrix->data[9] = csFixedMul(FIXED_POINT_TWO, yz - xw);
    matrix->data[10] = FIXED_POINT_ONE - csFixedMul(FIXED_POINT_TWO, xx + yy);
    matrix->data[11] = 0;

    matrix->data[12] = 0;
    matrix->data[13] = 0;
    matrix->data[14] = 0;
    matrix->data[15] = FIXED_POINT_ONE;
}