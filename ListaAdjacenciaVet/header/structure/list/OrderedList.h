#ifndef ORDEREDLIST_H_INCLUDED
#define ORDEREDLIST_H_INCLUDED

#include "AbstractNodeList.h"
#include "../../Helper.h"

enum InsertType
{
    InsertOrdered, InsertStart, InsertEnd, InsertNone
};

template <class G> class OrderedList
{
    private:
        AbstractNodeList<G> *startNode;
        AbstractNodeList<G> *endNode;
        AbstractNodeList<G> *it;

        int length;

        void searchById(int nodeId);
        void searchByValue(float nodeValue);
    public:
        OrderedList();
        ~OrderedList();

        void insert(float nodeValue, InsertType type);
        void insert(G *info, InsertType type);
        void insert(float nodeValue, G *info, InsertType type);
        void insert(int nodeId, float nodeValue, G *info, InsertType type);
        bool search(int nodeId);
        void remove(int nodeId);
        void remove(InsertType type);
        void remove(int nodeId, InsertType type);
        void clear();
        void print();

        void start();
        void end();
        void previous();
        void next();
        bool isEnd();
        bool isEmpty();

        int getStartId();
        int getStartValue();
        G* getStartInfo();
        int getCurrentId();
        float getCurrentValue();
        G* getCurrentInfo();
        float getNodeValue(int nodeId);
        G* getNodeInfo(int nodeId);

        int getLength();
};

#endif // ORDEREDLIST_H_INCLUDED
