#include "../header/Adjacencia.h"

Adjacencia::Adjacencia(int idNode1, int idNode2, float weight)
{
    this->idNode1 = idNode1;
    this->idNode2 = idNode2;
    this->weight = weight;
}

int Adjacencia::getIdNode1()
{
    return this->idNode1;
}

int Adjacencia::getIdNode2()
{
    return this->idNode2;
}

float Adjacencia::getWeight()
{
    return this->weight;
}

void Adjacencia::setWeight(float weight)
{
    this->weight = weight;
}
