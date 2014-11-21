#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include <iostream>
#include <list>

#include "NodeInfo.h"
#include "Adjacencia.h"

using namespace std;

class Node
{
    private:
        float weight;

        list<Adjacencia*> adjacenciaList;
    public:
        Node();
        ~Node();

        float getWeight();
        void setWeight(float weight);

        void addAdjacencia(int idNode1, int idNode2, float weight);
        void removeAdjacencia(int idNodeAdj);
        bool existsAdjacencia(int idNodeAdj);
        Adjacencia* getAdjacencia(int idNodeAdj);
        list<Adjacencia*> getAdjacenciaList();

        int getGrau();
};

#endif // NODE_H_INCLUDED
