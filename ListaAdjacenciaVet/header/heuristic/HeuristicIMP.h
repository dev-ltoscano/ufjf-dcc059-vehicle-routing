#ifndef HEURISTICIMP_H
#define HEURISTICIMP_H

#include "../structure/list/OrderedList.h"
#include "../grafo/ListaAdjacenciaVet.h"
#include "Vehicle.h"
#include "../Helper.h"

enum HeuristicType
{
    Gulosa, Randomizada, Reativa
};

class HeuristicIMP
{
    public:
        HeuristicIMP(ListaAdjacenciaVet *grafo, HeuristicType heuristic, int itCount);
        int run(int nodeBase, float vehicleCapacity);
        virtual ~HeuristicIMP();
    protected:
    private:
        ListaAdjacenciaVet *grafo;
        HeuristicType heuristic;
        int itCount;
};

#endif // HEURISTICIMP_H
