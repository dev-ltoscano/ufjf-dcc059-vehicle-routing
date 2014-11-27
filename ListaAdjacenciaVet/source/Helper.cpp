#include "../header/Helper.h"

int Helper::getAdjWeight(Vertice *verticeList, int idVertice1, int idVertice2)
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

int** Helper::initializeIntegerMatriz(int length)
{
    int **dij = new int *[length];

    for(int i = 0; i < length; i++)
    {
        dij[i] = new int[length];
    }

    return dij;
}

void Helper::shortestPath(int **pij, int i, int j)
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

string Helper::shortestStringPath(int **pij, int i, int j)
{
    stringstream path;

    if((i != -1) && (j != -1))
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

string Helper::printShortestStringPath(FloydWarshall floyd, int i, int j)
{
    stringstream path;

    if(floyd.dij[i][j] < INFINITE)
    {
        path << "O caminho entre os nós " << i << " e " << j << " é: ";
        path << i;
        path << shortestStringPath(floyd.pij, i, j);
        path << " " << j << endl;
    }
    else
    {
        path << "Não há caminho entre o nó " << i << " e o nó " << j << endl;
    }

    return path.str();
}

void Helper::printShortestPath(FloydWarshall floyd, int i, int j)
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

FloydWarshall Helper::floydWarshall(ListaAdjacenciaVet *grafo)
{
    FloydWarshall floyd;
    int **pij = initializeIntegerMatriz(grafo->getVerticeCount());
    int **dij = initializeIntegerMatriz(grafo->getVerticeCount());

    for(int i = 0; i < grafo->getVerticeCount(); i++)
    {
        for(int j = 0; j < grafo->getVerticeCount(); j++)
        {
            pij[i][j] = -1;
            dij[i][j] = getAdjWeight(grafo->getVerticeList(), i, j);
        }
    }

    for(int k = 0; k < grafo->getVerticeCount(); k++)
    {
        for(int i = 0; i < grafo->getVerticeCount(); i++)
        {
            for(int j = 0; j < grafo->getVerticeCount(); j++)
            {
                int dikj = INFINITE;

                if((dij[i][k] != INFINITE) && (dij[k][j] != INFINITE))
                {
                    dikj = (dij[i][k] + dij[k][j]);
                }

                if(dij[i][j] > dikj)
                {
                    pij[i][j] = k;
                    dij[i][j] = dikj;
                }
            }
        }
    }

    floyd.pij = pij;
    floyd.dij = dij;

    return floyd;
}
