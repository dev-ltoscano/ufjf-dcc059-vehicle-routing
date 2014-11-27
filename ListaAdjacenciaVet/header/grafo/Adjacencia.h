#ifndef ADJACENCIA_H_INCLUDED
#define ADJACENCIA_H_INCLUDED

class Adjacencia
{
    private:
        int idVertice1; // N� i pertencente a adjac�ncia
        int idVertice2; // N� j pertencente a adjac�ncia

        int weight; // Peso da aresta
    public:
        Adjacencia(int idVertice1, int idVertice2, int weight);

        int getIdVertice1();
        int getIdVertice2();

        int getWeight();
        void setWeight(int weight);
};

#endif // ADJACENCIA_H_INCLUDED
