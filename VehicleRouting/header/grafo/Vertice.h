#ifndef VERTICE_H_INCLUDED
#define VERTICE_H_INCLUDED

#include "Adjacencia.h"
#include "../structure/list/OrderedList.h"

#include <iostream>
#include "../structure/Point.h"

using namespace std;

/**
*   Classe que representa um vértice do grafo
**/
class Vertice
{
    private:
        float weight; // Peso do vértice
        shared_ptr<Point> coord; // Coordenada do vértice
        OperationType adjInsertType; // Tipo de operação de inserção e remoção da lista de adjacências

        shared_ptr<OrderedList<Adjacencia>> adjacenciaList; // Lista de adjacências do vértice
    public:
        Vertice();
//        ~Vertice();

        shared_ptr<Point> getCoord();
        void setCoord(shared_ptr<Point> coord);

        void setAdjListType(OperationType type);

        int getGrau();
        float getWeight();
        void setWeight(float weight);

        void addAdjacencia(int idVertice1, int idVertice2, float weight);
        void removeAdjacencia(int idVertice2);
        bool existsAdjacencia(int idVertice2);
        shared_ptr<Adjacencia> getAdjacencia(int idVertice2);
        shared_ptr<OrderedList<Adjacencia>> getAdjacenciaList();
};

#endif // VERTICE_H_INCLUDED
