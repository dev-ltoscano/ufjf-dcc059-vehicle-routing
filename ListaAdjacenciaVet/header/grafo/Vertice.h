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

        OrderedList<Adjacencia> *adjacenciaList;
    public:
        Vertice();
        ~Vertice();

        void setAdjOrderList(bool isOrderAdjList);

        int getGrau();
        int getWeight();
        void setWeight(int weight);

        void addAdjacencia(int idVertice1, int idVertice2, int weight);
        void removeAdjacencia(int idVertice2);
        bool existsAdjacencia(int idVertice2);
        Adjacencia* getAdjacencia(int idVertice2);
        OrderedList<Adjacencia> *getAdjacenciaList();
};

#endif // VERTICE_H_INCLUDED
