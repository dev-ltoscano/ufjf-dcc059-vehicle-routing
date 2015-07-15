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
        int initialCapacity; // Capacidade máxima do veículo
        int capacity; // Capacidade atual do veículo
    public:
        Vehicle(int id, int initialCapacity);

        int getId();

        // Retorna a capacidade máxima
        int getInitialCapacity();

        // Retorna a capacidade atual
		int getCapacity();

        // Aumenta a capacidade do veículo, caso o problema seja de coleta (Limitado à capacidade máxima)
		void addCapacity(int increase);

        // Diminui a capacidade do veículo, caso o problema seja de entrega
		void removeCapacity(int decrease);

        // Restaura a capacidade do veículo para a capacidade máxima
        void resetCapacity();
};

#endif // VEHICLE_H_INCLUDED
