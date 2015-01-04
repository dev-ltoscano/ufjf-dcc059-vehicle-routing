#ifndef FLOYDWARSHALL_H_INCLUDED
#define FLOYDWARSHALL_H_INCLUDED

#include "../grafo/ListaAdjacenciaVet.h"
#include "../Helper.h"

#include <climits>
#include <string>
#include <sstream>
#include <memory>

using namespace std;

/**
*   Implementação do algoritmo de Floyd para caminho mínimo
**/
class FloydWarshall
{
    private:
        // Retorna o custo da adjacência se ela existir ou infinito caso contrário
        static float getAdjacenciaWeight(ListaAdjacenciaVet *grafo, int idVertice1, int idVertice2);

        // Imprime na tela o caminho mínimo entre dois vértices
        static void shortestPath(int **pij, int i, int j);

        // Gera uma string com o caminho mínimo entre dois vértices
        static string shortestStringPath(int **pij, int i, int j);
    public:
        static string getShortestStringPath(Floyd floyd, int i, int j);
        static void printShortestPath(Floyd floyd, int i, int j);

        // Calcula a matriz de custos do grafo
        static Floyd get(ListaAdjacenciaVet *grafo);
};

#endif // FLOYDWARSHALL_H_INCLUDED
