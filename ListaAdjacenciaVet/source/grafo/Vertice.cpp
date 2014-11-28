#include "../../header/grafo/Vertice.h"

Vertice::Vertice()
{
    this->adjacenciaList = new OrderedList<Adjacencia>();
    this->adjacenciaList->setOrder(false);
}

Vertice::~Vertice()
{
    delete this->adjacenciaList;
}

void Vertice::setAdjOrderList(bool isOrderAdjList)
{
    this->adjacenciaList->setOrder(isOrderAdjList);
}

Adjacencia* Vertice::getAdjacencia(int idVertice2)
{
    return this->adjacenciaList->getInfo(idVertice2);
}

int Vertice::getWeight()
{
    return this->weight;
}

void Vertice::setWeight(int weight)
{
    this->weight = weight;
}

int Vertice::getGrau()
{
    return this->adjacenciaList->getLength();
}

void Vertice::addAdjacencia(int idVertice1, int idVertice2, int weight)
{
    this->adjacenciaList->insert(idVertice2, weight, new Adjacencia(idVertice1, idVertice2, weight));
}

void Vertice::removeAdjacencia(int idVertice2)
{
    this->adjacenciaList->remove(idVertice2);
}

bool Vertice::existsAdjacencia(int idVertice2)
{
    return (this->getAdjacencia(idVertice2) != NULL);
}

OrderedList<Adjacencia>* Vertice::getAdjacenciaList()
{
    return this->adjacenciaList;
}
