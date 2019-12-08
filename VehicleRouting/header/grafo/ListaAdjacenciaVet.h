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
        int verticeCount; // Quantidade de v�rtices
        vector<vertice_ptr> verticeList; // Vetor de v�rtices do grafo

        bool isDirected; // Define se o grafo � direcionado ou n�o

        bool depth(bool *visited); // Busca em profundidade
        bool depth(int idVertice1, int idVertice2); // Busca em profundidade para verificar caminho entre dois n�s
    public:
        ListaAdjacenciaVet(int verticeCount, bool isDirected);
        ListaAdjacenciaVet(int verticeCount, bool isDirected, OperationType type);

        int getVerticeCount(); // Retorna a quantidade de v�rtices
        int getVerticeGrau(int idVertice); // Retorna o grau de um v�rtice
        float getVerticeWeight(int idVertice); // Retorna o peso de um v�rtice
        void setVerticeWeight(int idVertice, float weight); // Define o peso de um v�rtice
        shared_ptr<Point> getVerticePoint(int idVertice); // Retorna a coordenada do v�rtice
        void setVerticePoint(int idVertice, shared_ptr<Point> p); // Define a coordenada do v�rtice
        bool existsVertice(int idVertice); // Verifica se um v�rtice existe no grafo

        void addAdjacencia(int idVertice1, int idVertice2, float weight); // Adiciona um adjac�ncia
        void removeAdjacencia(int idVertice1, int idVertice2); // Remove uma adjac�ncia
        bool existsAdjacencia(int idVertice1, int idVertice2); // Veritica se existe um adjac�ncia
        shared_ptr<OrderedList<Adjacencia>> getAdjacenciaList(int idVertice); // Retorna a lista de adjac�ncia de um v�rtice
        shared_ptr<Adjacencia> getAdjacencia(int idVertice1, int idVertice2); // Retorna uma adjac�ncia de um v�rtice
        int getAdjacenciaCount(); // Retorna a quantidade de adjac�ncias do grafo

        bool isConexo(); // Verifica se o grafo � conexo
        int compConexaCount(); // Verifica quantas componentes conexas o grafo possui
        bool containsCiclo(int startIdVertice); // Verifica se o grafo possui ciclos
        bool containsCaminho(int startIdVertice, int endIdVertice); // Verifica se existe caminho entre dois n�s
};

#endif // LISTAADJACENCIAVET_H_INCLUDED
