#ifndef ORDEREDLIST_H_INCLUDED
#define ORDEREDLIST_H_INCLUDED

#include "AbstractNodeList.h"

template <class G> class OrderedList
{
    private:
        AbstractNodeList<G> *startNode;
        AbstractNodeList<G> *endNode;
        AbstractNodeList<G> *it;

        bool isOrdered;
        int length;

        void searchById(int nodeId);
        void searchByValue(int nodeValue);
    public:
        OrderedList();
        ~OrderedList();

        void setOrder(bool isOrdered);

        void insert(int nodeId, int nodeValue, G *info);
        bool search(int nodeId);
        void remove(int nodeId);
        void print();

        void start();
        void end();
        void previous();
        void next();
        bool isEnd();

        G* getInfo();
        G* getInfo(int nodeId);
        int getLength();
};

#endif // ORDEREDLIST_H_INCLUDED
