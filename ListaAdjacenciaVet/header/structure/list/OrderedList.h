#ifndef ORDEREDLIST_H_INCLUDED
#define ORDEREDLIST_H_INCLUDED

#include "NodeList.h"

class OrderedList
{
    private:
        NodeList *startNode;
        NodeList *endNode;
        NodeList *it;

        bool isOrdered;
        int length;

        void searchByWeight(int weight);
        void searchById(int idVertice2);
    public:
        OrderedList();
        ~OrderedList();

        void setOrder(bool isOrdered);

        void insert(Adjacencia *adj);
        bool search(int idVertice2);
        void remove(int idVertice2);

        void start();
        void end();
        void previous();
        void next();
        bool isEnd();

        Adjacencia* getAdjacencia();
        Adjacencia* getAdjacencia(int idVertice2);
        int getLength();
};

#endif // ORDEREDLIST_H_INCLUDED
