#include "mat.h"
#include <stdio.h>

void csMatToFloat(csFMat4 *dest, const csMat4 *mat, int print)
{
    for (int i = 0; i < 4;i++)
    {
        for (int j = 0; j < 4;j++)
        {
            (*dest)[i][j] = csFixedToFloat(mat->data[i][j]);
            if (print)
            {

            printf("%f ",(*dest)[i][j]);
            }
        }
        if (print)
        {

        printf("\n");
        }
    }
    if (print)
    {

    printf("\n\n");
    }
}