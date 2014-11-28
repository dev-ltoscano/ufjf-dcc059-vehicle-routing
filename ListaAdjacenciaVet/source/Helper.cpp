#include "../header/Helper.h"

int** Helper::initializeIntegerMatriz(int length)
{
    int **dij = new int *[length];

    for(int i = 0; i < length; i++)
    {
        dij[i] = new int[length];
    }

    return dij;
}
