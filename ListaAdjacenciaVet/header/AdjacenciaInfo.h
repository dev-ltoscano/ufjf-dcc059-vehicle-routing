#ifndef ADJACENCIAINFO_H_INCLUDED
#define ADJACENCIAINFO_H_INCLUDED

class AdjacenciaInfo
{
    private:
        float idNodeAdj;
        float weight;
    public:
        AdjacenciaInfo(int idNodeAdj, float weight);

        int getIdNodeAdj();
        float getWeight();
        void setWeight(float weight);
};

#endif // ADJACENCIAINFO_H_INCLUDED
