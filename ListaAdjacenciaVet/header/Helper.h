#ifndef HELPER_H_INCLUDED
#define HELPER_H_INCLUDED

#include "grafo/Adjacencia.h"

using namespace std;

//TODO
struct InsertCalculation {
    int nodeId;
    int difPath;
    Adjacencia* adj;
};

enum HeuristicType
{
    Gulosa, Randomizada, Reativa
};

class Helper
{
    private:

    public:
        static int** initializeIntegerMatriz(int length);
        static float** initializeFloatMatriz(int length);
};

#endif // HELPER_H_INCLUDED
