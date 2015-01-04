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
*   Heurística para o problema de roteamento de veículos capacitados
**/
class HeuristicIMP
{
    private:
        int nodeBase; // Vértice base do problema
        float vehicleCapacity; // Capacidade máxima do veículo utilizado no problema
        ListaAdjacenciaVet *grafo; // Grafo do problema

        bool ready; // Indica se a instância foi construída corretamente

        float heuristic(float alfa); // Heurística da inserção mais próxima
    public:
        HeuristicIMP(string filename);
        ~HeuristicIMP();

        bool isReady();

        float runGulosa();
        float runRandom(float alfa, int maxIteration);
        float runReativa(int alfaUpdate, int maxIteration);
};

#endif // HEURISTICIMP_H
