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
*   Implementa��o do algoritmo de Floyd para caminho m�nimo
**/
class FloydWarshall
{
    private:
        // Retorna o custo da adjac�ncia se ela existir ou infinito caso contr�rio
        static float getAdjacenciaWeight(ListaAdjacenciaVet *grafo, int idVertice1, int idVertice2);

        // Imprime na tela o caminho m�nimo entre dois v�rtices
        static void shortestPath(int **pij, int i, int j);

        // Gera uma string com o caminho m�nimo entre dois v�rtices
        static string shortestStringPath(int **pij, int i, int j);
    public:
        static string getShortestStringPath(Floyd floyd, int i, int j);
        static void printShortestPath(Floyd floyd, int i, int j);

        // Calcula a matriz de custos do grafo
        static Floyd get(ListaAdjacenciaVet *grafo);
};

#endif // FLOYDWARSHALL_H_INCLUDED
