#ifndef ABSTRACTNODELIST_H_INCLUDED
#define ABSTRACTNODELIST_H_INCLUDED

#include "../../grafo/Adjacencia.h"
#include "../../Helper.h"

#include <iostream>
#include <memory>

using namespace std;

/**
*   N� da lista ordenada
**/
template <class G> class AbstractNodeList
{
    private:
        int nodeId; // Id do n�
        float nodeValue; // Valor do n�
        shared_ptr<G> info; // Informa��o que o n� guarda

        shared_ptr<AbstractNodeList<G>> previous; // Anterior ao n�
        shared_ptr<AbstractNodeList<G>> next; // Sucessor ao n�
    public:
        AbstractNodeList(int nodeId, float nodeValue, shared_ptr<G> info);
        AbstractNodeList(int nodeId, float nodeValue, shared_ptr<G> info, shared_ptr<AbstractNodeList<G>> previous, shared_ptr<AbstractNodeList<G>> next);

        int getNodeId();
        float getNodeValue();

        shared_ptr<G> getInfo();
        void setInfo(shared_ptr<G> info);

        shared_ptr<AbstractNodeList<G>> getPrevious();
        shared_ptr<AbstractNodeList<G>> getNext();
        void setPrevious(shared_ptr<AbstractNodeList<G>> previous);
        void setNext(shared_ptr<AbstractNodeList<G>> next);
};

#endif // ABSTRACTNODELIST_H_INCLUDED
