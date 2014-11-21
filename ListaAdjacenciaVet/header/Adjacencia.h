#ifndef ADJACENCIA_H_INCLUDED
#define ADJACENCIA_H_INCLUDED

class Adjacencia
{
    private:
        int idNode1; // N� i pertencente a adjac�ncia
        int idNode2; // N� j pertencente a adjac�ncia

        float weight; // Peso da aresta
    public:
        Adjacencia(int idNode, int idNodeAdj, float weight);

        int getIdNode1();
        int getIdNode2();

        float getWeight();
        void setWeight(float weight);
};

#endif // ADJACENCIA_H_INCLUDED
