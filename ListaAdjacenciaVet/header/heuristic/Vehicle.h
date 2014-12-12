#ifndef VEHICLE_H_INCLUDED
#define VEHICLE_H_INCLUDED

#include <iostream>

using namespace std;

/**
*   Classe que representa um ve�culo capacitado
*   para a resolu��o do problema de roteamento
*   de ve�culos capacitados
**/
class Vehicle
{
    private:
        int id; // Id do ve�culo
        float initialCapacity; // Capacidade m�xima do ve�culo
        float capacity; // Capacidade atual do ve�culo
    public:
        Vehicle(int id, float initialCapacity);

        int getId();

        float getInitialCapacity();
        float getCapacity();

        // Aumenta a capacidade do ve�culo, caso o problema seja de coleta (Limitado � capacidade inicial)
        void addCapacity(float increase);

        // Diminui a capacidade do ve�culo, caso o problema seja de entrega
        void removeCapacity(float decrease);

        // Restaura a capacidade do ve�culo para a capacidade inicial
        void resetCapacity();
};

#endif // VEHICLE_H_INCLUDED
