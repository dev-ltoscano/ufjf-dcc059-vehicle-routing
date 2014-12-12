#ifndef HELPER_H_INCLUDED
#define HELPER_H_INCLUDED

#include "grafo/Adjacencia.h"

#include <climits>

#define INFINITE        INT_MAX

using namespace std;

//TODO
struct InsertCalculation
{
    int nodeId;
    int difPath;
//    Adjacencia* adj;
    int idVertice1;
    int idVertice2;
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
