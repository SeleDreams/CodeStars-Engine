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
void csMatToQuat(const mf16 *matrix, qf16 *q) {
    fix16_t trace = matrix->data[0] + matrix->data[5] + matrix->data[10];
    if (trace > 0) {
        fix16_t s = csFixedMul(csFixedSqrt(trace + FIXED_POINT_ONE), FIXED_POINT_TWO);
        q->a = csFixedMul(FIXED_POINT_ONE, s);
        q->b = csFixedMul(matrix->data[9] - matrix->data[6], s);
        q->c = csFixedMul(matrix->data[2] - matrix->data[8], s);
        q->d = csFixedMul(matrix->data[4] - matrix->data[1], s);
    } else if ((matrix->data[0] > matrix->data[5]) && (matrix->data[0] > matrix->data[10])) {
        fix16_t s = csFixedMul(csFixedSqrt(FIXED_POINT_ONE + matrix->data[0] - matrix->data[5] - matrix->data[10]), FIXED_POINT_TWO);
        q->a = csFixedMul(matrix->data[9] - matrix->data[6], s);
        q->b = csFixedMul(FIXED_POINT_ONE, s);
        q->c = csFixedMul(matrix->data[4] + matrix->data[1], s);
        q->d = csFixedMul(matrix->data[2] + matrix->data[8], s);
    } else if (matrix->data[5] > matrix->data[10]) {
        fix16_t s = csFixedMul(csFixedSqrt(FIXED_POINT_ONE + matrix->data[5] - matrix->data[0] - matrix->data[10]), FIXED_POINT_TWO);
        q->a = csFixedMul(matrix->data[2] - matrix->data[8], s);
        q->b = csFixedMul(matrix->data[4] + matrix->data[1], s);
        q->c = csFixedMul(FIXED_POINT_ONE, s);
        q->d = csFixedMul(matrix->data[9] + matrix->data[6], s);
    } else {
        fix16_t s = csFixedMul(csFixedSqrt(FIXED_POINT_ONE + matrix->data[10] - matrix->data[0] - matrix->data[5]), FIXED_POINT_TWO);
        q->a = csFixedMul(matrix->data[4] - matrix->data[1], s);
        q->b = csFixedMul(matrix->data[2] + matrix->data[8], s);
        q->c = csFixedMul(matrix->data[9] + matrix->data[6], s);
        q->d = csFixedMul(FIXED_POINT_ONE, s);
    }
}
