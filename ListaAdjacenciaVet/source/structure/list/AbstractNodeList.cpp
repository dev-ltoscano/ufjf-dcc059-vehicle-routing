#include "../../../header/structure/list/AbstractNodeList.h"

template <class G> AbstractNodeList<G>::AbstractNodeList(int nodeId, float nodeValue, G *info) : AbstractNodeList(nodeId, nodeValue, info, NULL, NULL) { }

template <class G> AbstractNodeList<G>::AbstractNodeList(int nodeId, float nodeValue, G *info, AbstractNodeList<G> *previous, AbstractNodeList<G> *next)
{
    this->nodeId = nodeId;
    this->nodeValue = nodeValue;
    this->info = info;
    this->previous = previous;
    this->next = next;
}

template <class G> AbstractNodeList<G>::~AbstractNodeList()
{
    delete this->info;
}

template <class G> G* AbstractNodeList<G>::getInfo()
{
    return this->info;
}

template <class G> void AbstractNodeList<G>::setInfo(G *info)
{
    this->info = info;
}

template <class G> int AbstractNodeList<G>::getNodeId()
{
    return this->nodeId;
}

template <class G> float AbstractNodeList<G>::getNodeValue()
{
    return this->nodeValue;
}


template <class G> AbstractNodeList<G>* AbstractNodeList<G>::getPrevious()
{
    return this->previous;
}

template <class G> void AbstractNodeList<G>::setPrevious(AbstractNodeList<G> *previous)
{
    this->previous = previous;
}

template <class G> AbstractNodeList<G>* AbstractNodeList<G>::getNext()
{
    return this->next;
}

template <class G> void AbstractNodeList<G>::setNext(AbstractNodeList<G> *next)
{
    this->next = next;
}

template class AbstractNodeList<int>;
template class AbstractNodeList<float>;
template class AbstractNodeList<Adjacencia>;
template class AbstractNodeList<InsertCalculation>;
