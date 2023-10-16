#include "mat.h"
#include <stdio.h>

void csMatToFloat(csFMat4 *dest, const csMat4 *mat)
{
    for (int i = 0; i < 4;i++)
    {
        for (int j = 0; j < 4;j++)
        {
            printf("%d ", csMatGet(mat,i,j));
            (*dest)[i][j] = (float)fix16_to_float(mat->data[i][j]);
        }
        printf("\n");
    }
    
    //(*dest)[3][3] = 1;
    printf("\n");
    for (int i = 0; i < 4;i++)
    {
        for (int j = 0; j < 4;j++)
        {
            printf("%f ", (*dest)[i][j]);
        }
        printf("\n");
    }
}