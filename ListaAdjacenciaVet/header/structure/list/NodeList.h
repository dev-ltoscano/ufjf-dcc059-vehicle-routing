#ifndef NODELIST_H_INCLUDED
#define NODELIST_H_INCLUDED

#include "../../grafo/Adjacencia.h"

#include <iostream>

using namespace std;

class NodeList
{
    private:
        Adjacencia *adj;

        NodeList *previous;
        NodeList *next;
    public:
        NodeList(Adjacencia *adj);
        NodeList(Adjacencia *adj, NodeList *previous, NodeList *next);
        ~NodeList();

        Adjacencia* getAdjacencia();
        void setAdjacencia(Adjacencia *adj);

        NodeList* getPrevious();
        NodeList* getNext();
        void setPrevious(NodeList *previous);
        void setNext(NodeList *next);
};

#endif // NODELIST_H_INCLUDED
