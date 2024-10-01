/* Basic quaternion implementation based on libfixmath fix16_t datatype. */

#ifndef _FIXQUAT_H_
#define _FIXQUAT_H_

#include <libfixmath/fix16.h>
#include "fixmatrix.h"
#include "fixvector3d.h"

typedef struct {
    fix16_t a; // Real part
    fix16_t b; // i
    fix16_t c; // j
    fix16_t d; // k
} qf16;

// Conjugate of quaternion
void qf16_conj(qf16 *dest, const qf16 *q);

// Multiply two quaternions, dest = q * r.
void qf16_mul(qf16 *dest, const qf16 *q, const qf16 *r);

// Add two quaternions, dest = q + r
void qf16_add(qf16 *dest, const qf16 *q, const qf16 *r);

// Multiply quaternion by scalar
void qf16_mul_s(qf16 *dest, const qf16 *q, fix16_t s);

// Divide quaternion by scalar
void qf16_div_s(qf16 *dest, const qf16 *q, fix16_t s);

// Dot product of two quaternions
fix16_t qf16_dot(const qf16 *q, const qf16 *r);

// Quaternion norm
fix16_t qf16_norm(const qf16 *q);

// Normalize quaternion
void qf16_normalize(qf16 *dest, const qf16 *q);

// Quaternion power (exponentation)
void qf16_pow(qf16 *dest, const qf16 *q, fix16_t power);

// Weighted average of two quaternions
// Think of it as q = w * q1 + (1 - w) * q2, but the internal algorithm considers attitudes.
void qf16_avg(qf16 *dest, const qf16 *q1, const qf16 *q2, fix16_t weight);

// Unit quaternion from axis and angle.
// Axis should have unit length and angle in radians.
void qf16_from_axis_angle(qf16 *dest, const v3d *axis, fix16_t angle);

// Unit quaternion to rotation matrix
static inline void qf16_to_matrix(mf16 *dest, const qf16 *q) {
    //fix16_t a2 = fix16_mul(q->a, q->a);
    fix16_t b2 = fix16_mul(q->b, q->b);
    fix16_t c2 = fix16_mul(q->c, q->c);
    fix16_t d2 = fix16_mul(q->d, q->d);

    fix16_t ab = fix16_mul(q->a, q->b);
    fix16_t ac = fix16_mul(q->a, q->c);
    fix16_t ad = fix16_mul(q->a, q->d);
    fix16_t bc = fix16_mul(q->b, q->c);
    fix16_t bd = fix16_mul(q->b, q->d);
    fix16_t cd = fix16_mul(q->c, q->d);

    dest->rows = dest->columns = 4;
    dest->errors = 0;

    dest->data[0] = fix16_one - 2 * (c2 + d2);
    dest->data[1] = 2 * (bc - ad);
    dest->data[2] = 2 * (bd + ac);
    dest->data[3] = 0;

    dest->data[4] = 2 * (bc + ad);
    dest->data[5] = fix16_one - 2 * (b2 + d2);
    dest->data[6] = 2 * (cd - ab);
    dest->data[7] = 0;

    dest->data[8] = 2 * (bd - ac);
    dest->data[9] = 2 * (cd + ab);
    dest->data[10] = fix16_one - 2 * (b2 + c2);
    dest->data[11] = 0;

    dest->data[12] = 0;
    dest->data[13] = 0;
    dest->data[14] = 0;
    dest->data[15] = fix16_one;
}

// Rotate vector using quaternion
void qf16_rotate(v3d *dest, const qf16 *q, const v3d *v);

static inline void qf16_from_v3d(qf16 *q, const v3d *v, fix16_t a)
{
    q->a = a;
    q->b = v->x;
    q->c = v->y;
    q->d = v->z;
}

static inline void qf16_to_v3d(v3d *v, const qf16 *q)
{
    v->x = q->b;
    v->y = q->c;
    v->z = q->d;
}

#endif
