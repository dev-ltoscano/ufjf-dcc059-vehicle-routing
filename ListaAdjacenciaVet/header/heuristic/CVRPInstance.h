#ifndef CVRPINSTANCE_H_INCLUDED
#define CVRPINSTANCE_H_INCLUDED

#include "../grafo/ListaAdjacenciaVet.h"

#include <iostream>

using namespace std;

/**
*   Classe que representa uma instância do problema CVRP
**/
class CVRPInstance
{
    private:
        int verticeCount; // Quantidade de vértices da instância
        int vehicleCapacity; // Capacidade do veículo utilizado
        int verticeBase; // Id do vértice da base

        ListaAdjacenciaVet *grafo; // Grafo do problema
    public:
        CVRPInstance();

        int getVerticeCount();
        void setVerticeCount(int verticeCount);

        int getVehicleCapacity();
        void setVehicleCapacity(float vehicleCapacity);

        int getVerticeBase();
        void setVerticeBase(int nodeId);

        void addVerticePoint(int idVertice, Point *verticePoint); // Define as coordenadas do vértice
        void addVerticeDemand(int idVertice, float demand); // Define a demanda do vértice

        ListaAdjacenciaVet* getInstance(); // Cria um grafo completo para o problema
};

#endif // CVRPINSTANCE_H_INCLUDED
