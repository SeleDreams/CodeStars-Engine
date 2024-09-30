#include "fixmatrix.h"
#include "fixarray.h"
#include "../../core/maths/maths.h"

/****************************
 * Initialization functions *
 ****************************/

void mf16_initialize(mf16 *matrix, int rows, int columns)
{
    matrix->rows = rows;
    matrix->columns = columns;
    matrix->errors = 0;

    mf16_fill(matrix,0);
}

void mf16_fill(mf16 *matrix, fix16_t value) {
    for (int column = 0; column < matrix->columns; column++)
    {
        for (int row = 0; row < matrix->rows; row++)
        {
            matrix->data[column * matrix->rows + row] = value;
        }
    }
}


void mf16_fill_diagonal(mf16 *dest, fix16_t value)
{
    int col;

    mf16_fill(dest, 0);

    for (col = 0; col < dest->columns; col++)
    {
        dest->data[col * dest->rows + col] = value;
    }
}


/*********************************
 * Operations between 2 matrices *
 *********************************/

void mf16_mul(mf16 *dest, const mf16 *a, const mf16 *b)
{
    int row, column;

    // If dest and input matrices alias, we have to use a temp matrix.
    mf16 tmp;
    fa16_unalias(dest, (void**)&a, (void**)&b, &tmp, sizeof(tmp));

    dest->errors = a->errors | b->errors;

    if (a->columns != b->rows)
        dest->errors |= FIXMATRIX_DIMERR;

    dest->rows = a->rows;
    dest->columns = b->columns;

    for (column = 0; column < dest->columns; column++)
    {
        for (row = 0; row < dest->rows; row++)
        {
            dest->data[column * 4 + row] = 0;
            for (int k = 0; k < 4; ++k) {
                dest->data[column * 4 + row] += fix16_mul(a->data[column * 4 + k], b->data[k * 4 + row]);
            }
        }
    }
}


// Multiply transpose of at with b
void mf16_mul_at(mf16 *dest, const mf16 *at, const mf16 *b)
{
    int row, column;
    
    // If dest and input matrices alias, we have to use a temp matrix.
    mf16 tmp;
    fa16_unalias(dest, (void**)&at, (void**)&b, &tmp, sizeof(tmp));
    
    dest->errors = at->errors | b->errors;
    
    if (at->rows != b->rows)
        dest->errors |= FIXMATRIX_DIMERR;
    
    dest->rows = at->columns;
    dest->columns = b->columns;
    
    for (column = 0; column < dest->columns; column++)
    {
        for (row = 0; row < dest->rows; row++)
        {
            dest->data[column * dest->rows + row] = fa16_dot(
                &at->data[row], at->rows,
                &b->data[column * b->rows], 1,
                at->rows);

            if (dest->data[column * dest->rows + row] == fix16_overflow)
                dest->errors |= FIXMATRIX_OVERFLOW;
        }
    }
}


void mf16_mul_bt(mf16 *dest, const mf16 *a, const mf16 *bt)
{
    int row, column;
    
    // If dest and input matrices alias, we have to use a temp matrix.
    mf16 tmp;
    fa16_unalias(dest, (void**)&a, (void**)&bt, &tmp, sizeof(tmp));
    
    dest->errors = a->errors | bt->errors;
    
    if (a->columns != bt->columns)
        dest->errors |= FIXMATRIX_DIMERR;
    
    dest->rows = a->rows;
    dest->columns = bt->rows;
    
    for (column = 0; column < dest->columns; column++)
    {
        for (row = 0; row < dest->rows; row++)
        {
            dest->data[column * dest->rows + row] = fa16_dot(
                &a->data[row], a->rows,
                &bt->data[column * bt->rows], 1,
                a->columns);

            if (dest->data[column * dest->rows + row] == fix16_overflow)
                dest->errors |= FIXMATRIX_OVERFLOW;
        }
    }
}


static void mf16_addsub(mf16 *dest, const mf16 *a, const mf16 *b, uint8_t add)
{
    int row, column;
    
    dest->errors = a->errors | b->errors;
    if (a->columns != b->columns || a->rows != b->rows)
        dest->errors |= FIXMATRIX_DIMERR;
    
    dest->rows = a->rows;
    dest->columns = a->columns;
    
    for (column = 0; column < dest->columns; column++)
    {
        for (row = 0; row < dest->rows; row++)
        {
            fix16_t sum;
            if (add)
                sum = fix16_add(a->data[row * a->columns + column], b->data[row * b->columns + column]);
            else
                sum = fix16_sub(a->data[row * a->columns + column], b->data[row * b->columns + column]);

            if (sum == fix16_overflow)
                dest->errors |= FIXMATRIX_OVERFLOW;

            dest->data[column * dest->rows + row] = sum;
        }
    }
}


void mf16_add(mf16 *dest, const mf16 *a, const mf16 *b)
{
    mf16_addsub(dest, a, b, 1);
}

void mf16_sub(mf16 *dest, const mf16 *a, const mf16 *b)
{
    mf16_addsub(dest, a, b, 0);
}

/*********************************
 * Operations on a single matrix *
 *********************************/

void mf16_transpose(mf16 *dest, const mf16 *matrix)
{
    int row, column;
    
    // This code is a bit tricky in order to work
    // in the situation when dest = matrix.
    // Before writing a value in dest, we must copy
    // the corresponding value from matrix to a temporary
    // variable.
    
    // We actually transpose a n by n square matrix, because
    // that can be done in-place easily. Because mf16 always
    // allocates a square area even if actual matrix is smaller,
    // this is not a problem.
    int n = matrix->rows;
    if (matrix->columns > n) n = matrix->columns;
    
    uint8_t rows = matrix->rows;
    dest->rows = matrix->columns;
    dest->columns = rows;
    dest->errors = matrix->errors;
    
    for (column = 0; column < n; column++)
    {
        for (row = 0; row < column; row++)
        {
            fix16_t temp = matrix->data[row * matrix->columns + column];
            dest->data[column * dest->rows + row] = matrix->data[column * matrix->columns + row];
            dest->data[row * dest->columns + column] = temp;
        }

        dest->data[column * dest->rows + column] = matrix->data[column * matrix->columns + column];
    }
}


/***************************************
 * Operations of a matrix and a scalar *
 ***************************************/

static void mf16_divmul_s(mf16 *dest, const mf16 *matrix, fix16_t scalar, uint8_t mul)
{
    int row, column;
    
    dest->rows = matrix->rows;
    dest->columns = matrix->columns;
    dest->errors = matrix->errors;
    
    for (column = 0; column < dest->columns; column++)
    {
        for (row = 0; row < dest->rows; row++)
        {
            fix16_t value = matrix->data[column * matrix->rows + row];

            if (mul)
                value = fix16_mul(value, scalar);
            else
                value = fix16_div(value, scalar);

            if (value == fix16_overflow)
                dest->errors |= FIXMATRIX_OVERFLOW;

            dest->data[column * dest->rows + row] = value;
        }
    }
}


void mf16_mul_s(mf16 *dest, const mf16 *matrix, fix16_t scalar)
{
    mf16_divmul_s(dest, matrix, scalar, 1);
}

void mf16_div_s(mf16 *dest, const mf16 *matrix, fix16_t scalar)
{
    mf16_divmul_s(dest, matrix, scalar, 0);
}


/***************************************************
 * Solving linear equations using QR decomposition *
 ***************************************************/

// Takes two columns vectors, v and u, of size n.
// Performs v = v - dot(u, v) * u,
// where dot(u,v) has already been computed
// u is assumed to be an unit vector.
static void subtract_projection(fix16_t *v, const fix16_t *u, fix16_t dot, int n, uint8_t *errors)
{
    while (n--)
    {
        // For unit vector u, u[i] <= 1
        // Therefore this multiplication cannot overflow
        fix16_t product = fix16_mul(dot, *u);
        
        // Overflow here is rare, but possible.
        fix16_t diff = fix16_sub(*v, product);
        
        if (diff == fix16_overflow)
            *errors |= FIXMATRIX_OVERFLOW;
        
        *v = diff;
        
        v++;
        u++;
    }
}


void mf16_qr_decomposition(mf16 *q, mf16 *r, const mf16 *matrix, int reorthogonalize)
{
    int i, j, reorth;
    fix16_t dot, norm;
    
    uint8_t stride = 1;
    uint8_t n = matrix->rows;

    // This uses the modified Gram-Schmidt algorithm.
    // subtract_projection takes advantage of the fact that
    // previous columns have already been normalized.

    // We start with q = matrix
    if (q != matrix)
    {
        *q = *matrix;
    }

    // R is initialized to have square size of cols(A) and zeroed.
    r->columns = matrix->columns;
    r->rows = matrix->columns;
    r->errors = 0;
    mf16_fill(r, 0);

    // Now do the actual Gram-Schmidt for the columns.
    for (j = 0; j < q->columns; j++)
    {
        for (reorth = 0; reorth <= reorthogonalize; reorth++)
        {
            for (i = 0; i < j; i++)
            {
                fix16_t *v = &q->data[j * q->rows];
                fix16_t *u = &q->data[i * q->rows];

                dot = fa16_dot(v, stride, u, stride, n);
                subtract_projection(v, u, dot, n, &q->errors);

                if (dot == fix16_overflow)
                    q->errors |= FIXMATRIX_OVERFLOW;

                r->data[i * r->rows + j] += dot;
            }
        }

        // Normalize the column in q
        norm = fa16_norm(&q->data[j * q->rows], stride, n);
        r->data[j * r->rows + j] = norm;

        if (norm == fix16_overflow)
            q->errors |= FIXMATRIX_OVERFLOW;

        if (norm < 5 && norm > -5)
        {
            // Nearly zero norm, which means that the column
            // was linearly dependent.
            q->errors |= FIXMATRIX_SINGULAR;
            continue;
        }

        for (i = 0; i < n; i++)
        {
            // norm >= v[i] for all i, therefore this division
            // doesn't overflow unless norm approaches 0.
            q->data[j * q->rows + i] = fix16_div(q->data[j * q->rows + i], norm);
        }
    }

    r->errors = q->errors;
}


void mf16_solve(mf16 *dest, const mf16 *q, const mf16 *r, const mf16 *matrix)
{
    int row, column, variable;
    
    if (r->columns != r->rows || r->columns != q->columns || r == dest)
    {
        dest->errors |= FIXMATRIX_USEERR;
        return;
    }
    
    // Ax=b <=> QRx=b <=> Q'QRx=Q'b <=> Rx=Q'b
    // Q'b is calculated directly and x is then solved column-by-column.
    mf16_mul_at(dest, q, matrix);

    for (column = 0; column < dest->columns; column++)
    {
        for (row = dest->rows - 1; row >= 0; row--)
        {
            fix16_t value = dest->data[column * dest->rows + row];

            // Subtract any already solved variables
            for (variable = row + 1; variable < r->columns; variable++)
            {
                fix16_t multiplier = r->data[variable * r->rows + row];
                fix16_t known_value = dest->data[column * dest->rows + variable];
                fix16_t product = fix16_mul(multiplier, known_value);
                value = fix16_sub(value, product);

                if (product == fix16_overflow || value == fix16_overflow)
                {
                    dest->errors |= FIXMATRIX_OVERFLOW;
                }
            }

            // Now value = R_ij x_i <=> x_i = value / R_ij
            fix16_t divider = r->data[row * r->rows + row];
            if (divider == 0)
            {
                dest->errors |= FIXMATRIX_SINGULAR;
                dest->data[column * dest->rows + row] = 0;
                continue;
            }

            fix16_t result = fix16_div(value, divider);
            dest->data[column * dest->rows + row] = result;

            if (result == fix16_overflow)
            {
                dest->errors |= FIXMATRIX_OVERFLOW;
            }
        }
    }
}


/**************************
 * Cholesky decomposition *
 **************************/

void mf16_cholesky(mf16 *dest, const mf16 *matrix)
{
    // This is the Cholesky–Banachiewicz algorithm.
    // Refer to http://en.wikipedia.org/wiki/Cholesky_decomposition#The_Cholesky.E2.80.93Banachiewicz_and_Cholesky.E2.80.93Crout_algorithms
    
    int row, column, k;
    dest->errors = matrix->errors;
    
    if (matrix->rows != matrix->columns)
        dest->errors |= FIXMATRIX_DIMERR;
    
    dest->rows = dest->columns = matrix->rows;
    
    for (column = 0; column < dest->columns; column++)
    {
        for (row = 0; row < dest->rows; row++)
        {
            if (row == column)
            {
                // Value on the diagonal
                // Ljj = sqrt(Ajj - sum(Ljk^2, k = 1..(j-1))
                fix16_t value = matrix->data[column * matrix->rows + row];
                for (k = 0; k < column; k++)
                {
                    fix16_t Ljk = dest->data[k * dest->rows + row];
                    Ljk = fix16_mul(Ljk, Ljk);
                    value = fix16_sub(value, Ljk);

                    if (value == fix16_overflow || Ljk == fix16_overflow)
                        dest->errors |= FIXMATRIX_OVERFLOW;
                }

                if (value < 0)
                {
                    if (value < -65)
                        dest->errors |= FIXMATRIX_NEGATIVE;
                    value = 0;
                }

                dest->data[column * dest->rows + row] = fix16_sqrt(value);
            }
            else if (row < column)
            {
                // Value above diagonal
                dest->data[column * dest->rows + row] = 0;
            }
            else
            {
                // Value below diagonal
                // Lij = 1/Ljj (Aij - sum(Lik Ljk, k = 1..(j-1)))
                fix16_t value = matrix->data[column * matrix->rows + row];
                for (k = 0; k < column; k++)
                {
                    fix16_t Lik = dest->data[k * dest->rows + row];
                    fix16_t Ljk = dest->data[k * dest->rows + column];
                    fix16_t product = fix16_mul(Lik, Ljk);
                    value = fix16_sub(value, product);

                    if (value == fix16_overflow || product == fix16_overflow)
                        dest->errors |= FIXMATRIX_OVERFLOW;
                }
                fix16_t Ljj = dest->data[column * dest->rows + column];
                value = fix16_div(value, Ljj);
                dest->data[column * dest->rows + row] = value;

                if (value == fix16_overflow)
                    dest->errors |= FIXMATRIX_OVERFLOW;
            }
        }
    }
}




/***********************************
 * Lower-triangular matrix inverse *
 **********************************/

void mf16_invert_lt(mf16 *dest, const mf16 *matrix)
{
    // This is port of the algorithm as found in the Efficient Java Matrix Library
    // https://code.google.com/p/efficient-java-matrix-library

    int_fast8_t i, j, k;
    const uint_fast8_t n = matrix->rows;

    // If dest and input matrices alias, we have to use a temp matrix.
    mf16 tmp;
    fa16_unalias(dest, (void**)&matrix, (void**)&matrix, &tmp, sizeof(tmp));

    dest->errors = dest->errors | matrix->errors;

    // TODO reorder these operations to avoid cache misses

    // inverts the lower triangular system and saves the result
    // in the upper triangle to minimize cache misses
    for (i = 0; i < n; ++i)
    {
        const fix16_t el_ii = matrix->data[i * matrix->rows + i];
        for (j = 0; j <= i; ++j)
        {
            fix16_t sum = (i == j) ? fix16_one : 0;
            for (k = i - 1; k >= j; --k)
            {
                sum = fix16_sub(sum, fix16_mul(matrix->data[k * matrix->rows + i], dest->data[k * dest->rows + j]));
            }
            dest->data[i * dest->rows + j] = fix16_div(sum, el_ii);
        }
    }
    // solve the system and handle the previous solution being in the upper triangle
    // takes advantage of symmetry
    for (i = n - 1; i >= 0; --i)
    {
        const fix16_t el_ii = matrix->data[i * matrix->rows + i];
        for (j = 0; j <= i; ++j)
        {
            fix16_t sum = (i < j) ? 0 : dest->data[i * dest->rows + j];
            for (k = i + 1; k < n; ++k)
            {
                sum = fix16_sub(sum, fix16_mul(matrix->data[i * matrix->rows + k], dest->data[k * dest->rows + j]));
            }
            dest->data[i * dest->rows + j] = dest->data[j * dest->rows + i] = fix16_div(sum, el_ii);
        }
    }
}

