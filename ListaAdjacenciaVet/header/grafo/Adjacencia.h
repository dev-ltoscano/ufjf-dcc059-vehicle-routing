#ifndef ADJACENCIA_H_INCLUDED
#define ADJACENCIA_H_INCLUDED

#include <iostream>

using namespace std;

/**
*   Classe que representa as adjacências do grafo,
*   contém os ids dos nós pertencentes ao par (i, j)
*   e o custo da adjacência
**/
class Adjacencia
{
    private:
        int idVertice1; // Nó i pertencente a adjacência
        int idVertice2; // Nó j pertencente a adjacência

        float weight; // Peso da adjacência
    public:
        Adjacencia(int idVertice1, int idVertice2, float weight);
        ~Adjacencia();

        int getIdVertice1();
        int getIdVertice2();

        float getWeight();
        void setWeight(float weight);

        bool equals(int idVertice1, int idVertice2);
        bool equals(Adjacencia* adj);
};

#endif // ADJACENCIA_H_INCLUDED
