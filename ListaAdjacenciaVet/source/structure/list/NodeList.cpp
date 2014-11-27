#include "../../../header/structure/list/NodeList.h"

NodeList::NodeList(Adjacencia *adj) : NodeList(adj, NULL, NULL) { }

NodeList::NodeList(Adjacencia *adj, NodeList *previous, NodeList *next)
{
    this->adj = adj;
    this->previous = previous;
    this->next = next;
}

NodeList::~NodeList()
{
    delete this->adj;
}

Adjacencia* NodeList::getAdjacencia()
{
    return this->adj;
}

void NodeList::setAdjacencia(Adjacencia *adj)
{
    this->adj = adj;
}

NodeList* NodeList::getPrevious()
{
    return this->previous;
}

void NodeList::setPrevious(NodeList *previous)
{
    this->previous = previous;
}

NodeList* NodeList::getNext()
{
    return this->next;
}

void NodeList::setNext(NodeList *next)
{
    this->next = next;
}
