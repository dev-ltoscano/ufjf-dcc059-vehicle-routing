#ifndef VEHICLE_H_INCLUDED
#define VEHICLE_H_INCLUDED

#include <iostream>

using namespace std;

/**
*   Classe que representa um veículo capacitado
*   para a resolução do problema de roteamento
*   de veículos capacitados
**/
class Vehicle
{
    private:
        int id; // Id do veículo
        float initialCapacity; // Capacidade máxima do veículo
        float capacity; // Capacidade atual do veículo
    public:
        Vehicle(int id, float initialCapacity);

        int getId();

        float getInitialCapacity();
        float getCapacity();

        // Aumenta a capacidade do veículo, caso o problema seja de coleta (Limitado à capacidade inicial)
        void addCapacity(float increase);

        // Diminui a capacidade do veículo, caso o problema seja de entrega
        void removeCapacity(float decrease);

        // Restaura a capacidade do veículo para a capacidade inicial
        void resetCapacity();
};

#endif // VEHICLE_H_INCLUDED
