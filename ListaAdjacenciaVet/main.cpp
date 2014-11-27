#include <iostream>
#include <stdlib.h> // rand();
#include <locale> // setlocale();

#include "header/grafo/ListaAdjacenciaVet.h"
#include "header/structure/list/OrderedList.h"
#include "header/Helper.h"
#include "header/FileHelper.h"

using namespace std;

ListaAdjacenciaVet* createGrafo(int maxNodes, int maxGrau, bool isDirected, bool isOrderAdjList)
{
    ListaAdjacenciaVet *grafo = new ListaAdjacenciaVet(maxNodes, isDirected, isOrderAdjList);

    for(int i = 0; i < maxNodes; i++)
    {
        int j = 0;
        int attempt = 0;
        int maxAdj = rand() % maxGrau;

        while((j < maxAdj) && (attempt < 10))
        {
            int nodeAdj = rand() % maxNodes;

            if((i != nodeAdj) && (!grafo->existsAdjacencia(i, nodeAdj)))
            {
//                cout << j << " > " << i << " ----- " << nodeAdj << endl;
                grafo->addAdjacencia(i, nodeAdj, rand() % 100);
                j++;
            }
            else
            {
                attempt++;
            }
        }
    }

    return grafo;
}

int main()
{
    setlocale(LC_ALL, "Portuguese");

    ListaAdjacenciaVet *grafo = createGrafo(500, 250, false, false);

//    ListaAdjacenciaVet *grafo = new ListaAdjacenciaVet(7, true, false);
//
//    grafo->addAdjacencia(1, 2, 1);
//    grafo->addAdjacencia(2, 3, 1);
//    grafo->addAdjacencia(2, 4, 3);
//    grafo->addAdjacencia(2, 5, 2);
//    grafo->addAdjacencia(3, 1, 3);
//    grafo->addAdjacencia(3, 4, 2);
//    grafo->addAdjacencia(4, 6, 2);
//    grafo->addAdjacencia(5, 4, -3); // Bug com grafo não direcionado!
//    grafo->addAdjacencia(6, 5, 3);

    FloydWarshall floyd = Helper::floydWarshall(grafo);

//    for(int i = 0; i < grafo->getVerticeCount(); i++)
//    {
//        for(int j = 0; j < grafo->getVerticeCount(); j++)
//        {
//            Helper::printShortestPath(floyd, i, j);
//        }
//    }

    FileHelper::writeGraphInfoFile(grafo, floyd);

//    for(int i = 0; i < grafo->getVerticeCount(); i++)
//    {
//        for(int j = 0; j < grafo->getVerticeCount(); j++)
//        {
//            cout << "i: " << i << "| j: " << j << " --- " << floyd.pij[i][j] << endl;
//        }
//    }

//    cout << "Conexo: " << grafo->isConexo() << endl;
//    cout << "Componentes: " << grafo->compConexaCount() << endl;
//    cout << "Ciclo: " << grafo->containsCiclo(1) << endl;
//
//    for(int i = 0; i < grafo->getVerticeCount(); i++)
//    {
//        for(int j = 0; j < grafo->getVerticeCount(); j++)
//        {
//            cout << "Existe caminho entre [" << i << "] e [" << j << "]: " << grafo->containsCaminho(i, j) << endl;
//        }
//    }

//    system("PAUSE");
    delete grafo;
    return 0;
}
