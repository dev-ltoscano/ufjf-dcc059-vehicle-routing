#include <iostream>
#include <string>
#include <stdlib.h> // rand();
#include <locale> // setlocale();

#include "header/grafo/ListaAdjacenciaVet.h"
#include "header/structure/list/OrderedList.h"
#include "header/Helper.h"
#include "header/FileHelper.h"
#include "header/heuristic/HeuristicCVRP.h"

using namespace std;

ListaAdjacenciaVet* createGrafo(int maxNodes, int maxGrau, bool isDirected, InsertType type)
{
    ListaAdjacenciaVet *grafo = new ListaAdjacenciaVet(maxNodes, isDirected, type);

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
                cout << j << " > " << i << " ----- " << nodeAdj << endl;
                grafo->addAdjacencia(i, nodeAdj, rand() % 100);
                grafo->setVerticeWeight(i, rand() % 100);
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

//    cout << argv[1] << endl;

    ListaAdjacenciaVet *grafo = createGrafo(45, 45, false, InsertOrdered);

//    ListaAdjacenciaVet *grafo = new ListaAdjacenciaVet(5, false, InsertOrdered);
//
//    grafo->addAdjacencia(0, 1, 1);
//    grafo->addAdjacencia(0, 2, INFINITE);
//    grafo->addAdjacencia(0, 3, INFINITE);
//    grafo->addAdjacencia(1, 3, INFINITE);
//    grafo->addAdjacencia(1, 2, 3);
//    grafo->addAdjacencia(3, 2, 5);
//    grafo->addAdjacencia(4, 2, 6);
//
//    grafo->setVerticeWeight(0, 0);
//    grafo->setVerticeWeight(1, 25);
//    grafo->setVerticeWeight(2, 25);
//    grafo->setVerticeWeight(3, 25);
//    grafo->setVerticeWeight(4, 25);



//    ListaAdjacenciaVet *grafo = new ListaAdjacenciaVet(7, false, InsertOrdered);

//    grafo->addAdjacencia(0, 1, 2);
////    grafo->addAdjacencia(0, 4, 2);
//    grafo->addAdjacencia(3, 0, 3);
//    grafo->addAdjacencia(1, 2, 1);
//    grafo->addAdjacencia(2, 3, 1);
//    grafo->addAdjacencia(2, 4, 3);
//    grafo->addAdjacencia(2, 5, 2);
//    grafo->addAdjacencia(3, 1, 3);
//    grafo->addAdjacencia(3, 4, 2);
//    grafo->addAdjacencia(4, 6, 2);
//    grafo->addAdjacencia(5, 4, 3);
//    grafo->addAdjacencia(6, 5, 3);
//
//    grafo->setVerticeWeight(0, 0);
//    grafo->setVerticeWeight(1, 25);
//    grafo->setVerticeWeight(2, 100);
//    grafo->setVerticeWeight(3, 50);
//    grafo->setVerticeWeight(4, 25);
//    grafo->setVerticeWeight(5, 100);
//    grafo->setVerticeWeight(6, 100);

//    Floyd floyd = FloydWarshall::get(grafo);
//
//    for(int i = 0; i < grafo->getVerticeCount(); i++)
//    {
//        for(int j = 0; j < grafo->getVerticeCount(); j++)
//        {
//            cout << "i: " << i << ", j: " << j << " | " << FloydWarshall::getShortestStringPath(floyd, i, j) << " | dij: " << floyd.dij[i][j] << endl;
//        }
//    }

    HeuristicCVRP *heuristic = new HeuristicCVRP(grafo, Gulosa, 0);
    cout << "Min: " << heuristic->run(0, 100) << endl;
//    heuristic->printNodeRateList();

//    OrderedList<int> *lista = new OrderedList<int>();
//
//    lista->insert(1, 1);
//    lista->insert(2, 2);
//    lista->insert(3, 3);
//
//    cout << "Length: " << lista->getLength() << endl;

//    cout << "Conexo: " << grafo->isConexo() << endl;
//    cout << "Componentes: " << grafo->compConexaCount() << endl;
//    cout << "Ciclo: " << grafo->containsCiclo(2) << endl;

//    Floyd floyd = FloydWarshall::get(grafo);
//    FileHelper::writeGraphInfoFile(grafo, floyd);

//    system("PAUSE");

    delete grafo;
    return 0;
}
