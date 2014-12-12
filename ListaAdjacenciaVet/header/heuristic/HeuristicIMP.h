#ifndef HEURISTICIMP_H
#define HEURISTICIMP_H

#include "../structure/list/OrderedList.h"
#include "../grafo/ListaAdjacenciaVet.h"
#include "Vehicle.h"
#include "../Helper.h"
#include "CVRPInstance.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class HeuristicIMP
{
    private:
        HeuristicType heuristic;
        float alfa;
    public:
        HeuristicIMP(HeuristicType heuristic, float alfa);

        void setAlfa(float alfa);

        int run(ListaAdjacenciaVet *grafo, int nodeBase, float vehicleCapacity);
        int run(CVRPInstance *instance);
};

#endif // HEURISTICIMP_H
