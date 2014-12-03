#ifndef LISTAADJACENCIAVET_H_INCLUDED
#define LISTAADJACENCIAVET_H_INCLUDED

#include "Vertice.h"

#include <iostream>
#include <list>

using namespace std;

class ListaAdjacenciaVet
{
    private:
        int verticeCount;
        Vertice *verticeList;
        bool isDirected;

        bool existsVertice(int idVertice);

        bool depth(bool *visited); // Busca em profundidade
        bool depth(int idVertice1, int idVertice2); // Busca em profundidade para verificar caminho entre dois nós
    public:
        ListaAdjacenciaVet(int verticeCount, bool isDirected);
        ListaAdjacenciaVet(int verticeCount, bool isDirected, InsertType type);
        ~ListaAdjacenciaVet();

        Vertice* getVerticeList();
        Vertice getVertice(int idVertice);
        int getVerticeCount();
        int getVerticeGrau(int idVertice);
        float getVerticeWeight(int idVertice);
        void setVerticeWeight(int idVertice, float weight);


        void addAdjacencia(int idVertice1, int idVertice2, float weight);
        void removeAdjacencia(int idVertice1, int idVertice2);
        bool existsAdjacencia(int idVertice1, int idVertice2);
//        Adjacencia* getAdjacencia(int idVertice1, int idVertice2);
        int getAdjacenciaCount();

        bool isConexo(); // Verifica se o grafo é conexo
        int compConexaCount(); // Verifica quantas componentes conexas o grafo possui
        bool containsCiclo(int startIdVertice); // Verifica se o grafo possui ciclos
        bool containsCaminho(int startIdVertice, int endIdVertice); // Verifica se existe caminho entre dois nós
//        void minCaminho(int startIdVertice); // Caminho mínimo a partir do nó inicial (Dijkstra)
};

#endif // LISTAADJACENCIAVET_H_INCLUDED
