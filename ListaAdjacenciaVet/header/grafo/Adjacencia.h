#ifndef ADJACENCIA_H_INCLUDED
#define ADJACENCIA_H_INCLUDED

#include <stdio.h>

class Adjacencia
{
    private:
        int idVertice1; // Nó i pertencente a adjacência
        int idVertice2; // Nó j pertencente a adjacência

        float weight; // Peso da aresta
    public:
        Adjacencia(int idVertice1, int idVertice2, float weight);
        ~Adjacencia();

        int getIdVertice1();
        int getIdVertice2();

        float getWeight();
        void setWeight(float weight);
};

#endif // ADJACENCIA_H_INCLUDED
