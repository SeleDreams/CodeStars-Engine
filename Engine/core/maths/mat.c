#include "mat.h"

void csMatToFloat(csFMat4 *dest, const csMat4 *mat)
{
    for (int i = 0; i < 4;i++)
    {
        for (int j = 0; j < 4;j++)
        {
            (*dest)[i][j] = fix16_to_float(mat->data[i][j]);
        }
    }
}