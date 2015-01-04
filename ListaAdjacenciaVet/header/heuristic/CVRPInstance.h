#ifndef CVRPINSTANCE_H_INCLUDED
#define CVRPINSTANCE_H_INCLUDED

#include "../grafo/ListaAdjacenciaVet.h"

#include <iostream>

using namespace std;

/**
*   Classe que representa uma inst�ncia do problema CVRP
**/
class CVRPInstance
{
    private:
        int verticeCount; // Quantidade de v�rtices da inst�ncia
        int vehicleCapacity; // Capacidade do ve�culo utilizado
        int verticeBase; // Id do v�rtice da base

        ListaAdjacenciaVet *grafo; // Grafo do problema
    public:
        CVRPInstance();

        int getVerticeCount();
        void setVerticeCount(int verticeCount);

        int getVehicleCapacity();
        void setVehicleCapacity(float vehicleCapacity);

        int getVerticeBase();
        void setVerticeBase(int nodeId);

        void addVerticePoint(int idVertice, Point *verticePoint); // Define as coordenadas do v�rtice
        void addVerticeDemand(int idVertice, float demand); // Define a demanda do v�rtice

        ListaAdjacenciaVet* getInstance(); // Cria um grafo completo para o problema
};

#endif // CVRPINSTANCE_H_INCLUDED
