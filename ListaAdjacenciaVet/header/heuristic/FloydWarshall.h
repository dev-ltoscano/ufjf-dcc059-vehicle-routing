#ifndef FLOYDWARSHALL_H_INCLUDED
#define FLOYDWARSHALL_H_INCLUDED

#include "../grafo/ListaAdjacenciaVet.h"
#include "../Helper.h"

#include <climits>
#include <string>
#include <sstream>

#define INFINITE        INT_MAX

using namespace std;

typedef struct
{
    string** path;
    int** pij;
    int** dij;
} Floyd;

class FloydWarshall
{
    private:
        static int getAdjWeight(Vertice *verticeList, int idVertice1, int idVertice2);
        static void shortestPath(int **pij, int i, int j);
        static string shortestStringPath(int **pij, int i, int j);
    public:
        static string getShortestStringPath(Floyd floyd, int i, int j);
        static void printShortestPath(Floyd floyd, int i, int j);
        static Floyd get(ListaAdjacenciaVet *grafo);
};

#endif // FLOYDWARSHALL_H_INCLUDED
