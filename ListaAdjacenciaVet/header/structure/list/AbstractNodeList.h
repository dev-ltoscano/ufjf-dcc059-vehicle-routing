#ifndef ABSTRACTNODELIST_H_INCLUDED
#define ABSTRACTNODELIST_H_INCLUDED

#include "../../grafo/Adjacencia.h"

#include <iostream>

using namespace std;

template <class G> class AbstractNodeList
{
    private:
        int nodeId;
        int nodeValue;
        G *info;

        AbstractNodeList<G> *previous;
        AbstractNodeList<G> *next;
    public:
        AbstractNodeList(int nodeId, int nodeValue, G *info);
        AbstractNodeList(int nodeId, int nodeValue, G *info, AbstractNodeList<G> *previous, AbstractNodeList<G> *next);
        ~AbstractNodeList();

        int getNodeId();
        int getNodeValue();

        G* getInfo();
        void setInfo(G *info);

        AbstractNodeList<G>* getPrevious();
        AbstractNodeList<G>* getNext();
        void setPrevious(AbstractNodeList<G> *previous);
        void setNext(AbstractNodeList<G> *next);
};

#endif // ABSTRACTNODELIST_H_INCLUDED
