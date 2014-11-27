#ifndef HELPER_H_INCLUDED
#define HELPER_H_INCLUDED

#include "grafo/ListaAdjacenciaVet.h"

#include <climits>
#include <string>
#include <sstream>

//#define INFINITE      numeric_limits<int>::max()
//#define INFINITE      999999
#define INFINITE        INT_MAX

using namespace std;

typedef struct
{
    string** path;
    int** pij;
    int** dij;
} FloydWarshall;

class Helper
{
    private:
        static int getAdjWeight(Vertice *verticeList, int idVertice1, int idVertice2);
        static void shortestPath(int **pij, int i, int j);
        static string shortestStringPath(int **pij, int i, int j);
    public:
//        static int* initializeIntegerVector(int length);
        static int** initializeIntegerMatriz(int length);
        static void printShortestPath(FloydWarshall floyd, int i, int j);
        static string printShortestStringPath(FloydWarshall floyd, int i, int j);
        static FloydWarshall floydWarshall(ListaAdjacenciaVet *grafo);
};

#endif // HELPER_H_INCLUDED
