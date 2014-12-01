#include "../../header/grafo/Adjacencia.h"

Adjacencia::Adjacencia(int idVertice1, int idVertice2, float weight)
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

float Adjacencia::getWeight()
{
    return this->weight;
}

void Adjacencia::setWeight(float weight)
{
    this->weight = weight;
}
