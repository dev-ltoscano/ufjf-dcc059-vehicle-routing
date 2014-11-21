#ifndef LISTAADJACENCIAVET_H_INCLUDED
#define LISTAADJACENCIAVET_H_INCLUDED

#include <iostream>

#include "Node.h"

using namespace std;

class ListaAdjacenciaVet
{
    private:
        int nodeCount;
        Node *nodeList;
        bool isDirected;

        bool existsNode(int idNode);

        void depth(int idNode, int *nodeVet); // Busca em profundidade no grafo
        bool cicle(int idNode, int startIdNode, int *nodeVet); // Busca por ciclos no grafo
        bool path(int idNode, int endIdNode,  int *nodeVet); // Busca por caminho entre dois nós do grafo
    public:
        ListaAdjacenciaVet(int nodeCount, bool isDirected);
        ~ListaAdjacenciaVet();

        int getNodeCount();
        Node* getNodeList();

        void addAdjacencia(int idNode1, int idNode2, float weight);
        void removeAdjacencia(int idNode1, int idNode2);
        bool existsAdjacencia(int idNode1, int idNode2);
        Adjacencia* getAdjacenciaInfo(int idNode1, int idNode2);

        int getGrau(int idNode);
        void getNodeInfo(int idNode);

        bool isConexo(); // Verifica se o grafo é conexo
        int compConexaCount(); // Verifica quantas componentes conexas o grafo possui
        bool containsCiclo(int startIdNode); // Verifica se o grafo possui ciclos
        bool containsCaminho(int startIdNode, int endIdNode); // Verifica se existe caminho entre dois nós
        void minCaminho(int startIdNode); // Caminho mínimo a partir do nó inicial (Dijkstra)
};

#endif // LISTAADJACENCIAVET_H_INCLUDED
