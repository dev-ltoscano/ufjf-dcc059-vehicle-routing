#ifndef ADJACENCIA_H_INCLUDED
#define ADJACENCIA_H_INCLUDED

#include "AdjacenciaInfo.h"

class Adjacencia
{
    private:
        AdjacenciaInfo *adjInfo;
    public:
        Adjacencia(AdjacenciaInfo *adjInfo);
        ~Adjacencia();

        AdjacenciaInfo* getAdjacenciaInfo();
};

#endif // ADJACENCIA_H_INCLUDED
