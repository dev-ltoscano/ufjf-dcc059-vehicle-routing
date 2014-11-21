#include "../header/Helper.h"

void Helper::quickSort(ListaAdjacenciaVet *grafo)
{
    cout << "[ Erro ]: Quicksort não implementado!" << endl;
}

int Helper::getMinAdj(Node *nodeList, int nodeCount)
{
    int idAdj = -1;
    float minWeight = -999;

    for(int i = 0; i < nodeCount; i++)
    {
        if(nodeList[i].getWeight() < minWeight)
        {
            idAdj = i;
            minWeight = nodeList[i].getWeight();
        }
    }

    return idAdj;
}
