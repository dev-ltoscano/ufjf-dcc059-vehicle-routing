#ifndef HEURISTICIMP_H
#define HEURISTICIMP_H

#include "../Helper.h"
#include "../FileHelper.h"
#include "../structure/list/OrderedList.h"

#include "Vehicle.h"
#include "CVRPInstance.h"
#include "../grafo/ListaAdjacenciaVet.h"

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

/**
*   Heur�stica para o problema de roteamento de ve�culos capacitados
**/
class HeuristicIMP
{
    private:
        int nodeBase; // V�rtice base do problema
        float vehicleCapacity; // Capacidade m�xima do ve�culo utilizado no problema
        ListaAdjacenciaVet *grafo; // Grafo do problema

        bool ready; // Indica se a inst�ncia foi constru�da corretamente

        float heuristic(float alfa); // Heur�stica da inser��o mais pr�xima
    public:
        HeuristicIMP(string filename);
        ~HeuristicIMP();

        bool isReady();

        float runGulosa();
        float runRandom(float alfa, int maxIteration);
        float runReativa(int alfaUpdate, int maxIteration);
};

#endif // HEURISTICIMP_H
