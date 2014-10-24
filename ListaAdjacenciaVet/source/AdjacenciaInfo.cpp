#include "../header/AdjacenciaInfo.h"

AdjacenciaInfo::AdjacenciaInfo(int idNodeAdj, float weight)
{
    this->idNodeAdj = idNodeAdj;
    this->weight = weight;
}

int AdjacenciaInfo::getIdNodeAdj()
{
    return this->idNodeAdj;
}

float AdjacenciaInfo::getWeight()
{
    return this->weight;
}

void AdjacenciaInfo::setWeight(float weight)
{
    this->weight = weight;
}
