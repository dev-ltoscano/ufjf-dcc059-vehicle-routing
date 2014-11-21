#include <iostream>
#include <stdlib.h> // rand();

#include "header/ListaAdjacenciaVet.h"

using namespace std;

ListaAdjacenciaVet* createGrafo(int maxNodes, int maxGrau)
{
    ListaAdjacenciaVet *grafo = new ListaAdjacenciaVet(maxNodes, false);

    for(int i = 0; i < maxNodes; i++)
    {
        int j = 0;
        int maxAdj = rand() % maxGrau;

        while(j < maxAdj)
        {
            int nodeAdj = rand() % maxNodes;

            if((i != nodeAdj) && (!grafo->existsAdjacencia(i, nodeAdj)))
            {
                grafo->addAdjacencia(i, nodeAdj, 0);
                j++;
            }
        }
    }

    return grafo;
}

int main()
{
    ListaAdjacenciaVet *grafo = createGrafo(50, 25);

//    ListaAdjacenciaVet *grafo = new ListaAdjacenciaVet(4, false);
//
//    grafo->addAdjacencia(0, 1, 0);
//    grafo->addAdjacencia(1, 2, 0);
//    grafo->addAdjacencia(2, 3, 0);
//    grafo->addAdjacencia(3, 0, 0);

    cout << "Conexo: " << grafo->isConexo() << endl;
    cout << "Componentes: " << grafo->compConexaCount() << endl;
    cout << "Ciclo: " << grafo->containsCiclo(0) << endl;

//    system("PAUSE");

    delete grafo;
    return 0;
}
