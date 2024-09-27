#include "mat.h"
#include <stdio.h>

void csMatToFloat(csFMat4 *dest, const csMat4 *mat, int print)
{
    for (int i = 0; i < 16;i++)
    {
            (*dest)[i] = csFixedToFloat(mat->data[i]);
    }
}

void csMatPerspective(csFixed fovy, csFixed aspect, csFixed zNear, csFixed zFar, csMat4 *projection) {
    csFixed f = csFixedDiv(csFixedFromFloat(1.0f), csFixedTan(csFixedDiv(fovy, csFixedFromFloat(2.0f))));
    csFixed rangeInv = csFixedDiv(csFixedFromFloat(1.0f), csFixedSub(zNear, zFar));
    csFixed *matrix = projection->data;
    matrix[0] = csFixedDiv(f, aspect);
    matrix[1] = 0;
    matrix[2] = 0;
    matrix[3] = 0;

    matrix[4] = 0;
    matrix[5] = f;
    matrix[6] = 0;
    matrix[7] = 0;

    matrix[8] = 0;
    matrix[9] = 0;
    matrix[10] = csFixedMul(csFixedAdd(zFar, zNear), rangeInv);
    matrix[11] = -csFixedFromFloat(1.0f);

    matrix[12] = 0;
    matrix[13] = 0;
    matrix[14] = csFixedMul(csFixedMul(csFixedFromFloat(2.0f), zFar), csFixedMul(zNear, rangeInv));
    matrix[15] = 0;
}