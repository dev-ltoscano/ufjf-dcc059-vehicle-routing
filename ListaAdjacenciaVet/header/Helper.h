#ifndef HELPER_H_INCLUDED
#define HELPER_H_INCLUDED

#include "grafo/Adjacencia.h"

using namespace std;

struct InsertCalculation {
    int nodeId;
    int difPath;
    Adjacencia* adj;
};

class Helper
{
    private:

    public:
        static int** initializeIntegerMatriz(int length);
        static float** initializeFloatMatriz(int length);
};

#endif // HELPER_H_INCLUDED
