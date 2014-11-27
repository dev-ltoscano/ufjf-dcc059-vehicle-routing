#ifndef ADJACENCIA_H_INCLUDED
#define ADJACENCIA_H_INCLUDED

class Adjacencia
{
    private:
        int idVertice1; // Nó i pertencente a adjacência
        int idVertice2; // Nó j pertencente a adjacência

        int weight; // Peso da aresta
    public:
        Adjacencia(int idVertice1, int idVertice2, int weight);

        int getIdVertice1();
        int getIdVertice2();

        int getWeight();
        void setWeight(int weight);
};

#endif // ADJACENCIA_H_INCLUDED
