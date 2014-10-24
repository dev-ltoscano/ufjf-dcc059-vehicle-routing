#include "../header/Adjacencia.h"

Adjacencia::Adjacencia(AdjacenciaInfo *adjInfo)
{
    this->adjInfo = adjInfo;
}

Adjacencia::~Adjacencia()
{
    delete this->adjInfo;
}

AdjacenciaInfo* Adjacencia::getAdjacenciaInfo()
{
    return this->adjInfo;
}
