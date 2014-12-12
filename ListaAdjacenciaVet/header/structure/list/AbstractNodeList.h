#ifndef ABSTRACTNODELIST_H_INCLUDED
#define ABSTRACTNODELIST_H_INCLUDED

#include "../../grafo/Adjacencia.h"
#include "../../Helper.h"

#include <iostream>

using namespace std;

/*
*   Classe que define um nó da lista ordenada
*/
template <class G> class AbstractNodeList
{
    private:
        int nodeId; // Id do nó
        float nodeValue; // Valor do nó
        G *info; // Informação que o nó guarda

        AbstractNodeList<G> *previous; // Anterior ao nó
        AbstractNodeList<G> *next; // Sucessor ao nó
    public:
        AbstractNodeList(int nodeId, float nodeValue, G *info);
        AbstractNodeList(int nodeId, float nodeValue, G *info, AbstractNodeList<G> *previous, AbstractNodeList<G> *next);
        ~AbstractNodeList();

        int getNodeId();
        float getNodeValue();

        G* getInfo();
        void setInfo(G *info);

        AbstractNodeList<G>* getPrevious();
        AbstractNodeList<G>* getNext();
        void setPrevious(AbstractNodeList<G> *previous);
        void setNext(AbstractNodeList<G> *next);
};

#endif // ABSTRACTNODELIST_H_INCLUDED
