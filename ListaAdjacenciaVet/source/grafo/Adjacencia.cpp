#include "../../header/grafo/Adjacencia.h"

Adjacencia::Adjacencia(int idVertice1, int idVertice2, int weight)
{
    this->idVertice1 = idVertice1;
    this->idVertice2 = idVertice2;
    this->weight = weight;
}

int Adjacencia::getIdVertice1()
{
    return this->idVertice1;
}

int Adjacencia::getIdVertice2()
{
    return this->idVertice2;
}

int Adjacencia::getWeight()
{
    return this->weight;
}

void Adjacencia::setWeight(int weight)
{
    this->weight = weight;
}
