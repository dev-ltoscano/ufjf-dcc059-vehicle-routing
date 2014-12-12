#include "../../header/grafo/Adjacencia.h"

Adjacencia::Adjacencia(int idVertice1, int idVertice2, float weight)
{
    this->idVertice1 = idVertice1;
    this->idVertice2 = idVertice2;
    this->weight = weight;
}

Adjacencia::~Adjacencia()
{
//    cout << "Removendo adjacência!" << endl;
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

bool Adjacencia::equals(Adjacencia* adj)
{
    return this->equals(adj->getIdVertice1(),adj->getIdVertice2());
}

bool Adjacencia::equals(int idVertice1, int idVertice2)
{
    if((this->getIdVertice1() == idVertice1) && (this->getIdVertice2() == idVertice2))
    {
        return true;
    }

    return false;
}
