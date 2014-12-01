#include "../../header/heuristic/FloydWarshall.h"

float FloydWarshall::getAdjWeight(Vertice *verticeList, int idVertice1, int idVertice2)
{
    if(idVertice1 == idVertice2)
    {
        return 0;
    }
    else
    {
        Adjacencia *verticeAdj = verticeList[idVertice1].getAdjacencia(idVertice2);
        return (verticeAdj != NULL) ? verticeAdj->getWeight() : INFINITE;
    }
}


void FloydWarshall::shortestPath(int **pij, int i, int j)
{
    if((i != -1) && (j != -1))
    {
        int k = pij[i][j];

        if(k > 0)
        {
            shortestPath(pij, i, k);
            cout << " " << k;
            shortestPath(pij, k, j);
        }
    }
}

string FloydWarshall::shortestStringPath(int **pij, int i, int j)
{
    stringstream path;

    if((i > -1) && (j > -1))
    {
        int k = pij[i][j];

        if(k > 0)
        {
            path << shortestStringPath(pij, i, k);
            path << " " << k;
            path << shortestStringPath(pij, k, j);
        }
    }

    return path.str();
}

string FloydWarshall::getShortestStringPath(Floyd floyd, int i, int j)
{
    stringstream path;

    if((floyd.dij[i][j] < INFINITE) && (floyd.dij[i][j] >= 0))
    {
        path << "O caminho entre os nós " << i << " e " << j << " é: ";
        path << i;
        path << shortestStringPath(floyd.pij, i, j);
        path << " " << j << endl;
    }
    else if(floyd.dij[i][j] < 0)
    {
        path << "Ciclo negativo!" << endl;
    }
    else if(floyd.dij[i][j] == INFINITE)
    {
        path << "Não há caminho entre o nó " << i << " e o nó " << j << endl;
    }

    return path.str();
}

void FloydWarshall::printShortestPath(Floyd floyd, int i, int j)
{
    if(floyd.dij[i][j] < INFINITE)
    {
        cout << "O caminho entre os nós " << i << " e " << j << " é: ";
        cout << i;
        shortestPath(floyd.pij, i, j);
        cout << " " << j << endl;
    }
    else
    {
        cout << "[ Erro ]: Não há caminho entre o nó " << i << " e o nó " << j << endl;
    }
}

Floyd FloydWarshall::get(ListaAdjacenciaVet *grafo)
{
    Floyd floyd;
    int **pij = Helper::initializeIntegerMatriz(grafo->getVerticeCount());
    float **dij = Helper::initializeFloatMatriz(grafo->getVerticeCount());
//    float **vij = Helper::initializeFloatMatriz(grafo->getVerticeCount());

    for(int i = 0; i < grafo->getVerticeCount(); i++)
    {
        for(int j = 0; j < grafo->getVerticeCount(); j++)
        {
            pij[i][j] = -1;
            dij[i][j] = getAdjWeight(grafo->getVerticeList(), i, j);
//            vij[i][j] = grafo->getVerticeWeight(j);
        }
    }

    for(int k = 0; k < grafo->getVerticeCount(); k++)
    {
        for(int i = 0; i < grafo->getVerticeCount(); i++)
        {
            for(int j = 0; j < grafo->getVerticeCount(); j++)
            {
                float dikj = INFINITE;

                // Verifica se há aresta
                if((dij[i][k] != INFINITE) && (dij[k][j] != INFINITE))
                {
                    dikj = (dij[i][k] + dij[k][j]);
                }

                if(dij[i][j] > dikj)
                {
                    pij[i][j] = k;
//                    vij[i][j] = vij[i][k] + vij[k][j];
                    dij[i][j] = dikj;
                }
            }
        }
    }

    floyd.pij = pij;
    floyd.dij = dij;
//    floyd.vij = vij;

    return floyd;
}
