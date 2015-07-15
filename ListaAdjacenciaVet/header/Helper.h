#ifndef HELPER_H_INCLUDED
#define HELPER_H_INCLUDED

#include <iostream>
#include <climits>

#define INFINITE            INT_MAX
#define SCALERATIO          1000000

using namespace std;

// Estrutura que guarda o custo entre dois n�s e a quantidade de n�s intermedi�rios
struct Floyd
{
    int** pij;
    float** dij;
};

//  Estrutura que guarda o c�lculo de uma inser��o na solu��o
struct InsertCalculation
{
    int nodeId;
    float difPath;
    int idVertice1;
    int idVertice2;
};

// Tipo de heur�stica usada
enum HeuristicType
{
    Gulosa, Randomizada, Reativa
};

/**
*   Classe que cont�m m�todos auxiliares diversos
**/
class Helper
{
    public:
        static int** initializeIntegerMatriz(int length);
        static float** initializeFloatMatriz(int length);
};

#endif // HELPER_H_INCLUDED
