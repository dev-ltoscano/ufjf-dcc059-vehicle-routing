#ifndef ABSTRACTNODELIST_H_INCLUDED
#define ABSTRACTNODELIST_H_INCLUDED

#include "../../grafo/Adjacencia.h"
#include "../../Helper.h"

#include <iostream>

using namespace std;

/*
*   Classe que define um n� da lista ordenada
*/
template <class G> class AbstractNodeList
{
    private:
        int nodeId; // Id do n�
        float nodeValue; // Valor do n�
        G *info; // Informa��o que o n� guarda

        AbstractNodeList<G> *previous; // Anterior ao n�
        AbstractNodeList<G> *next; // Sucessor ao n�
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
