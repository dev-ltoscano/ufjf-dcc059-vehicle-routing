#include "../../../header/structure/list/AbstractNodeList.h"

template <class G> AbstractNodeList<G>::AbstractNodeList(int nodeId, float nodeValue, shared_ptr<G> info) : AbstractNodeList(nodeId, nodeValue, info, NULL, NULL) { }

template <class G> AbstractNodeList<G>::AbstractNodeList(int nodeId, float nodeValue, shared_ptr<G> info, shared_ptr<AbstractNodeList<G>> previous, shared_ptr<AbstractNodeList<G>> next)
{
    this->nodeId = nodeId;
    this->nodeValue = nodeValue;
    this->info = info;
    this->previous = previous;
    this->next = next;
}

template <class G> shared_ptr<G> AbstractNodeList<G>::getInfo()
{
    return this->info;
}

template <class G> void AbstractNodeList<G>::setInfo(shared_ptr<G> info)
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


template <class G> shared_ptr<AbstractNodeList<G>> AbstractNodeList<G>::getPrevious()
{
    return this->previous;
}

template <class G> void AbstractNodeList<G>::setPrevious(shared_ptr<AbstractNodeList<G>> previous)
{
    this->previous = previous;
}

template <class G> shared_ptr<AbstractNodeList<G>> AbstractNodeList<G>::getNext()
{
    return this->next;
}

template <class G> void AbstractNodeList<G>::setNext(shared_ptr<AbstractNodeList<G>> next)
{
    this->next = next;
}

template class AbstractNodeList<int>;
template class AbstractNodeList<float>;
template class AbstractNodeList<Adjacencia>;
template class AbstractNodeList<InsertCalculation>;
