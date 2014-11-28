#include <iostream>
#include <string>
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

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "Portuguese");

    cout << argv[1] << endl;

//    ListaAdjacenciaVet *grafo = createGrafo(500, 250, false, true);

    ListaAdjacenciaVet *grafo = new ListaAdjacenciaVet(7, true, true);

    grafo->addAdjacencia(1, 2, 1);
    grafo->addAdjacencia(2, 3, 1);
    grafo->addAdjacencia(2, 4, 3);
    grafo->addAdjacencia(2, 5, 2);
    grafo->addAdjacencia(3, 1, 3);
    grafo->addAdjacencia(3, 4, 2);
    grafo->addAdjacencia(4, 6, 2);
    grafo->addAdjacencia(5, 4, -3); // Bug com grafo não direcionado!
    grafo->addAdjacencia(6, 5, 3);

    Floyd floyd = FloydWarshall::get(grafo);
    FileHelper::writeGraphInfoFile(grafo, floyd);

//    system("PAUSE");

    delete grafo;
    return 0;
}
