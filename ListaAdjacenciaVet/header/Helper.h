#ifndef HELPER_H_INCLUDED
#define HELPER_H_INCLUDED

#include "ListaAdjacenciaVet.h"

class Helper
{
    private:

    public:
        void quickSort(ListaAdjacenciaVet *grafo); // Ordena a lista de nós de acordo com o peso da aresta
        int getMinAdj(Node *nodeList, int nodeCount);
};

#endif // HELPER_H_INCLUDED
