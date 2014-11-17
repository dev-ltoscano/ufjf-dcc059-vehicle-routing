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
        NodeInfo *info = nodeList[i].getNodeInfo();

        if(info->getWeight() < minWeight)
        {
            idAdj = i;
            minWeight = info->getWeight();
        }
    }

    return idAdj;
}
