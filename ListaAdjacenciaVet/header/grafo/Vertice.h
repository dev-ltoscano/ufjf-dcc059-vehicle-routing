#ifndef VERTICE_H_INCLUDED
#define VERTICE_H_INCLUDED

#include "Adjacencia.h"
#include "../structure/list/OrderedList.h"

#include <iostream>
#include "../structure/Point.h"

using namespace std;

/**
*   Classe que representa um v�rtice do grafo
**/
class Vertice
{
    private:
        float weight; // Peso do v�rtice
        Point *coord; // Coordenada do v�rtice
        OperationType adjInsertType; // Tipo de opera��o de inser��o e remo��o da lista de adjac�ncias

        OrderedList<Adjacencia> *adjacenciaList; // Lista de adjac�ncias do v�rtice
    public:
        Vertice();
        ~Vertice();

        Point* getCoord();
        void setCoord(Point *coord);

        void setAdjListType(OperationType type);

        int getGrau();
        float getWeight();
        void setWeight(float weight);

        void addAdjacencia(int idVertice1, int idVertice2, float weight);
        void removeAdjacencia(int idVertice2);
        bool existsAdjacencia(int idVertice2);
        Adjacencia* getAdjacencia(int idVertice2);
        OrderedList<Adjacencia> *getAdjacenciaList();
};

#endif // VERTICE_H_INCLUDED
