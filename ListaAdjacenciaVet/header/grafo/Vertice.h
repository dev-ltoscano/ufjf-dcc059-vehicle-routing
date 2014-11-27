#ifndef VERTICE_H_INCLUDED
#define VERTICE_H_INCLUDED

#include "Adjacencia.h"
#include "../structure/list/OrderedList.h"

#include <iostream>

using namespace std;

class Vertice
{
    private:
        int weight;

        OrderedList *adjacenciaList;
    public:
        Vertice();
        Vertice(bool isOrderAdjList);
        ~Vertice();

        int getGrau();
        int getWeight();
        void setWeight(int weight);

        void addAdjacencia(int idVertice1, int idVertice2, int weight);
        void removeAdjacencia(int idVertice2);
        bool existsAdjacencia(int idVertice2);
        Adjacencia* getAdjacencia(int idVertice2);
        OrderedList *getAdjacenciaList();
};

#endif // VERTICE_H_INCLUDED
