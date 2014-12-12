#ifndef LISTAADJACENCIAVET_H_INCLUDED
#define LISTAADJACENCIAVET_H_INCLUDED

#include "Vertice.h"
#include "../structure/Point.h"

#include <iostream>

using namespace std;

/**
*   Classe que representa um grafo
**/
class ListaAdjacenciaVet
{
    private:
        int verticeCount; // Quantidade de v�rtices
        Vertice *verticeList; // Vetor de v�rtices
        bool isDirected; // Define se o grafo � direcionado ou n�o

        bool depth(bool *visited); // Busca em profundidade
        bool depth(int idVertice1, int idVertice2); // Busca em profundidade para verificar caminho entre dois n�s
    public:
        ListaAdjacenciaVet(int verticeCount, bool isDirected);
        // Construtor que define como as adjac�ncias ser�o inseridas nas listas de adjac�ncias dos v�rtices
        ListaAdjacenciaVet(int verticeCount, bool isDirected, OperationType type);
        ~ListaAdjacenciaVet();

        Vertice* getVerticeList(); // Retorna a lista de v�rtices
        int getVerticeCount(); // Retorna a quantidade de v�rtices
        int getVerticeGrau(int idVertice); // Retorna o grau de um v�rtice
        float getVerticeWeight(int idVertice); // Retorna o peso de um v�rtice
        void setVerticeWeight(int idVertice, float weight); // Define o peso de um v�rtice
        Point* getVerticePoint(int idVertice); // Retorna a coordenada do v�rtice
        void setVerticePoint(int idVertice, Point *p); // Define a coordenada do v�rtice
        bool existsVertice(int idVertice); // Verifica se um v�rtice existe no grafo

        void addAdjacencia(int idVertice1, int idVertice2, float weight); // Adiciona um adjac�ncia
        void removeAdjacencia(int idVertice1, int idVertice2); // Remove uma adjac�ncia
        bool existsAdjacencia(int idVertice1, int idVertice2); // Veritica se existe um adjac�ncia
        OrderedList<Adjacencia>* getAdjacenciaList(int idVertice); // Retorna a lista de adjac�ncia de um v�rtice
        Adjacencia* getAdjacencia(int idVertice1, int idVertice2); // Retorna uma adjac�ncia de um v�rtice
        int getAdjacenciaCount(); // Retorna a quantidade de adjac�ncias do grafo

        bool isConexo(); // Verifica se o grafo � conexo
        int compConexaCount(); // Verifica quantas componentes conexas o grafo possui
        bool containsCiclo(int startIdVertice); // Verifica se o grafo possui ciclos
        bool containsCaminho(int startIdVertice, int endIdVertice); // Verifica se existe caminho entre dois n�s
};

#endif // LISTAADJACENCIAVET_H_INCLUDED
