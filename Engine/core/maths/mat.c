#include "mat.h"
#include <stdio.h>


void csMatToFloat(csFMat4 *dest, const csMat4 *mat, int print)
{
    for (int i = 0; i < 16;i++)
    {
            (*dest)[i] = csFixedToFloat(mat->data[i]);
    }
}
