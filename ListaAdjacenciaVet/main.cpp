#include <iostream>
#include <string>
#include <stdlib.h> // rand();
#include <locale> // setlocale();

#include "header/grafo/ListaAdjacenciaVet.h"
#include "header/structure/list/OrderedList.h"
#include "header/Helper.h"
#include "header/FileHelper.h"
#include "header/heuristic/HeuristicCVRP.h"
#include "header/heuristic/HeuristicIMP.h"

using namespace std;

ListaAdjacenciaVet* createGrafo(int maxNodes, InsertType type)
{
    ListaAdjacenciaVet *grafo = new ListaAdjacenciaVet(maxNodes, true, type);

    for(int i = 0; i < maxNodes; i++)
    {
        for(int j = 0; j < maxNodes; j++)
        {
            if(i != j)
            {
                grafo->addAdjacencia(i, j, rand() % 10);
            }
        }
    }

    for(int i = 0; i < maxNodes; i++)
    {
        grafo->setVerticeWeight(i, rand() % 100);
    }

    return grafo;
}

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

//    ListaAdjacenciaVet *grafo = createGrafo(15, 15, true, InsertEnd);

//    ListaAdjacenciaVet *grafo = createGrafo(5, InsertEnd);

    ListaAdjacenciaVet *grafo = new ListaAdjacenciaVet(4, true, InsertOrdered);

//    grafo->addAdjacencia(0, 1, 5);
//    grafo->addAdjacencia(0, 2, 5);
//    grafo->addAdjacencia(0, 3, 5);
//    grafo->addAdjacencia(0, 4, 5);
//    grafo->addAdjacencia(0, 5, 5);
//    grafo->addAdjacencia(2, 1, 5);
//    grafo->addAdjacencia(2, 3, 5);
//    grafo->addAdjacencia(2, 4, 5);
//    grafo->addAdjacencia(2, 5, 5);
//    grafo->addAdjacencia(3, 1, 5);
//    grafo->addAdjacencia(3, 2, 5);
//    grafo->addAdjacencia(3, 4, 5);
//    grafo->addAdjacencia(3, 5, 5);
//    grafo->addAdjacencia(4, 1, 5);
//    grafo->addAdjacencia(4, 2, 5);
//    grafo->addAdjacencia(4, 3, 5);
//    grafo->addAdjacencia(4, 5, 5);
//    grafo->addAdjacencia(5, 1, 5);
//    grafo->addAdjacencia(5, 2, 5);
//    grafo->addAdjacencia(5, 3, 5);
//    grafo->addAdjacencia(5, 4, 5);




//    grafo->addAdjacencia(0, 1, 20);
//    grafo->addAdjacencia(1, 0, 20);
//    grafo->addAdjacencia(1, 3, 5);
//    grafo->addAdjacencia(0, 4, 10);
//    grafo->addAdjacencia(5, 4, 15);
//
//    grafo->addAdjacencia(0, 2, 10);
//    grafo->addAdjacencia(2, 1, 5);
//
//    grafo->addAdjacencia(0, 3, 5);
//    grafo->addAdjacencia(3, 2, 2);
//    grafo->addAdjacencia(3, 0, 5);
//
//    grafo->addAdjacencia(1, 4, 5);
//    grafo->addAdjacencia(4, 5, 5);
//    grafo->addAdjacencia(4, 0, 15);
//    grafo->addAdjacencia(4, 3, 15);
//    grafo->addAdjacencia(5, 3, 10);
//
//    grafo->setVerticeWeight(0, 0);
//    grafo->setVerticeWeight(1, 20);
//    grafo->setVerticeWeight(2, 15);
//    grafo->setVerticeWeight(3, 10);
//    grafo->setVerticeWeight(4, 5);
//    grafo->setVerticeWeight(5, 15);

    grafo->addAdjacencia(0,1,1);
    grafo->addAdjacencia(0,2,1);
    grafo->addAdjacencia(0,3,1);

    grafo->addAdjacencia(1,0,1);
    grafo->addAdjacencia(1,2,1);
    grafo->addAdjacencia(1,3,1);

    grafo->addAdjacencia(2,0,1);
    grafo->addAdjacencia(2,1,1);
    grafo->addAdjacencia(2,3,1);

    grafo->addAdjacencia(3,0,1);
    grafo->addAdjacencia(3,1,1);
    grafo->addAdjacencia(3,2,1);

    grafo->setVerticeWeight(0,0);
    grafo->setVerticeWeight(1,40);
    grafo->setVerticeWeight(2,50);
    grafo->setVerticeWeight(3,5);



//    grafo->addAdjacencia(0, 2, 10);
//    grafo->addAdjacencia(0, 3, 5);
//    grafo->addAdjacencia(0, 4, INFINITE);
//
//    grafo->addAdjacencia(1, 0, 20);
//    grafo->addAdjacencia(1, 2, INFINITE);
//    grafo->addAdjacencia(1, 4, INFINITE);
//
//    grafo->addAdjacencia(2, 0, 10);
//    grafo->addAdjacencia(2, 1, 5);
//    grafo->addAdjacencia(2, 3, INFINITE);
//
//
//    grafo->addAdjacencia(3, 0, 5);
//    grafo->addAdjacencia(3, 2, 2);


//    grafo->addAdjacencia(0, 1, 1);
//    grafo->addAdjacencia(0, 2, 10);
//    grafo->addAdjacencia(0, 3, 4);
//    grafo->addAdjacencia(1, 3, 8);
//    grafo->addAdjacencia(1, 2, 3);
//    grafo->addAdjacencia(3, 2, 5);
//    grafo->addAdjacencia(4, 2, 6);

//    grafo->setVerticeWeight(0, 0);
//    grafo->setVerticeWeight(1, 0);
//    grafo->setVerticeWeight(2, 0);
//    grafo->setVerticeWeight(3, 25);
//    grafo->setVerticeWeight(4, 25);


//    HeuristicCVRP *h = new HeuristicCVRP(grafo, Gulosa, 0);
//    int dij = h->run(0, 100);
//
//    cout << "Custo da solução: " << dij << endl;


    HeuristicIMP *heuristic = new HeuristicIMP(grafo, Gulosa, 0);
    cout << "Custo: " << heuristic->run(0, 100);



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

//    HeuristicCVRP *heuristic = new HeuristicCVRP(grafo, Gulosa, 0);
//    cout << "Min: " << heuristic->run(0, 100) << endl;
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
