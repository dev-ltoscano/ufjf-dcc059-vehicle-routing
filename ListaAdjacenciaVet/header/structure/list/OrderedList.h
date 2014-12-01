#ifndef ORDEREDLIST_H_INCLUDED
#define ORDEREDLIST_H_INCLUDED

#include "AbstractNodeList.h"

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

        void insert(int nodeId, float nodeValue);
        void insert(int nodeId, InsertType type);
        void insert(int nodeId, float nodeValue, G *info);
        void insert(int nodeId, float nodeValue, G *info, InsertType type);
        bool search(int nodeId);
        void remove(int nodeId);
        void remove(InsertType type);
        void remove(int nodeId, InsertType type);
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
