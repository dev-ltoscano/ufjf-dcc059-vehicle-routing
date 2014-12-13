#ifndef CVRPINSTANCE_H_INCLUDED
#define CVRPINSTANCE_H_INCLUDED

#include "../grafo/ListaAdjacenciaVet.h"

#include <iostream>

using namespace std;

class CVRPInstance
{
    private:
        int verticeCount;
        int vehicleCapacity;
        int verticeBase;

        shared_ptr<ListaAdjacenciaVet> grafo;
    public:
        CVRPInstance();

        int getVerticeCount();
        void setVerticeCount(int verticeCount);

        int getVehicleCapacity();
        void setVehicleCapacity(float vehicleCapacity);

        int getVerticeBase();
        void setVerticeBase(int nodeId);

        void addVerticePoint(int idVertice, shared_ptr<Point> verticePoint);
        void addVerticeDemand(int idVertice, float demand);

        shared_ptr<ListaAdjacenciaVet> getInstance();
};

#endif // CVRPINSTANCE_H_INCLUDED
