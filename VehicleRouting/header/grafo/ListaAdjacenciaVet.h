#ifndef LISTAADJACENCIAVET_H_INCLUDED
#define LISTAADJACENCIAVET_H_INCLUDED

#include "Vertice.h"
#include "../structure/Point.h"

#include <iostream>
#include <vector>

typedef shared_ptr<Vertice> vertice_ptr;

using namespace std;

/**
*   Classe que representa um grafo
**/
class ListaAdjacenciaVet
{
    private:
        int verticeCount; // Quantidade de vértices
        vector<vertice_ptr> verticeList; // Vetor de vértices do grafo

        bool isDirected; // Define se o grafo é direcionado ou não

        bool depth(bool *visited); // Busca em profundidade
        bool depth(int idVertice1, int idVertice2); // Busca em profundidade para verificar caminho entre dois nós
    public:
        ListaAdjacenciaVet(int verticeCount, bool isDirected);
        ListaAdjacenciaVet(int verticeCount, bool isDirected, OperationType type);

        int getVerticeCount(); // Retorna a quantidade de vértices
        int getVerticeGrau(int idVertice); // Retorna o grau de um vértice
        float getVerticeWeight(int idVertice); // Retorna o peso de um vértice
        void setVerticeWeight(int idVertice, float weight); // Define o peso de um vértice
        shared_ptr<Point> getVerticePoint(int idVertice); // Retorna a coordenada do vértice
        void setVerticePoint(int idVertice, shared_ptr<Point> p); // Define a coordenada do vértice
        bool existsVertice(int idVertice); // Verifica se um vértice existe no grafo

        void addAdjacencia(int idVertice1, int idVertice2, float weight); // Adiciona um adjacência
        void removeAdjacencia(int idVertice1, int idVertice2); // Remove uma adjacência
        bool existsAdjacencia(int idVertice1, int idVertice2); // Veritica se existe um adjacência
        shared_ptr<OrderedList<Adjacencia>> getAdjacenciaList(int idVertice); // Retorna a lista de adjacência de um vértice
        shared_ptr<Adjacencia> getAdjacencia(int idVertice1, int idVertice2); // Retorna uma adjacência de um vértice
        int getAdjacenciaCount(); // Retorna a quantidade de adjacências do grafo

        bool isConexo(); // Verifica se o grafo é conexo
        int compConexaCount(); // Verifica quantas componentes conexas o grafo possui
        bool containsCiclo(int startIdVertice); // Verifica se o grafo possui ciclos
        bool containsCaminho(int startIdVertice, int endIdVertice); // Verifica se existe caminho entre dois nós
};

#endif // LISTAADJACENCIAVET_H_INCLUDED
