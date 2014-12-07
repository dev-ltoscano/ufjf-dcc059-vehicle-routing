#include "../../header/heuristic/HeuristicCVRP.h"
//
HeuristicCVRP::HeuristicCVRP(ListaAdjacenciaVet *grafo, HeuristicType heuristic, int itCount)
{
    this->grafo = grafo;
    this->heuristic = heuristic;
    this->itCount = (heuristic == Gulosa) ? 1 : itCount;
//    this->nodeRateList = NULL;
}

int HeuristicCVRP::run(int nodeBase, float vehicleCapacity)
{
    int dij = 0;

    int visitedLength = 0;
    bool *visited = new bool[grafo->getVerticeCount()];
    OrderedList<Adjacencia> *solution = new OrderedList<Adjacencia>();

    Vehicle *truck = new Vehicle(1, vehicleCapacity, nodeBase);

//    // Defeito aqui, escolher melhor o nó de saida!
//    Adjacencia *baseIda = grafo->getAdjacencia(nodeBase, grafo->getVerticeList()[nodeBase].getAdjacenciaList()->getStartId());
//    Adjacencia *baseVolta = grafo->getAdjacencia(baseIda->getIdVertice2(), nodeBase);
//
////    cout << "Ida: " << baseIda->getIdVertice1() << " -- " << baseIda->getIdVertice2() << endl;
////    cout << "Volta: " << baseVolta->getIdVertice1() << " -- " << baseVolta->getIdVertice2() << endl;
//
//    solution->insert(baseIda, InsertEnd);
//    visitedLength++;
//
//    solution->insert(baseVolta, InsertEnd);
//
//    truck->removeCapacity(grafo->getVerticeWeight(baseIda->getIdVertice2()));

    OrderedList<Adjacencia> *adjBaseList = grafo->getAdjacenciaList(nodeBase);

    while(visitedLength < grafo->getVerticeCount() - 1)
    {
        cout << "Nova solução!" << endl;
//        solution->print();
//        solution->clear();

        Adjacencia *baseIda = NULL;
        Adjacencia *baseVolta = NULL;

        adjBaseList->start();

        while(!adjBaseList->isEnd())
        {
            Adjacencia *adj = adjBaseList->getCurrentInfo();

            if(!visited[adj->getIdVertice2()])
            {
                baseIda = adj;
                baseVolta = grafo->getAdjacencia(baseIda->getIdVertice2(), nodeBase);

                solution->insert(baseIda, InsertEnd);
//                visited[baseIda->getIdVertice2()] = true;
//                visitedLength++;

                solution->insert(baseVolta, InsertEnd);
                truck->removeCapacity(grafo->getVerticeWeight(baseIda->getIdVertice2()));
                break;
            }
            else
            {
                cout << "Estou aqui!" << endl;
            }

            adjBaseList->next();
        }

//
//        // Defeito aqui, escolher melhor o nó de saida!
//        Adjacencia *baseIda = grafo->getAdjacencia(nodeBase, grafo->getVerticeList()[nodeBase].getAdjacenciaList()->getStartId());
//        Adjacencia *baseVolta = grafo->getAdjacencia(baseIda->getIdVertice2(), nodeBase);
//
//        //    cout << "Ida: " << baseIda->getIdVertice1() << " -- " << baseIda->getIdVertice2() << endl;
//        //    cout << "Volta: " << baseVolta->getIdVertice1() << " -- " << baseVolta->getIdVertice2() << endl;
//
//        solution->insert(baseIda, InsertEnd);
//        visited++;
//
//        solution->insert(baseVolta, InsertEnd);
//
//        truck->removeCapacity(grafo->getVerticeWeight(baseIda->getIdVertice2()));

        while((truck->getCapacity() > 0) && (visitedLength < grafo->getVerticeCount() - 1))
        {
            visitedLength++;

            int idAdjIda = solution->getLength() - 2;
            int idAdjVolta = solution->getLength() - 1;

            Adjacencia *aIda = solution->getNodeInfo(idAdjIda);
            Adjacencia *aVolta = solution->getNodeInfo(idAdjVolta);

//            cout << "v1: " << aIda->getIdVertice1() << " -- v2: " << aIda->getIdVertice2() << endl;
//            cout << "v1: " << aVolta->getIdVertice1() << " -- v2: " << aVolta->getIdVertice2() << endl;
//
//            if(visitedLength > 2)
//            {
//                break;
//            }

//            Adjacencia *currAdjIda = aIda;
            Adjacencia *newAdjIda = NULL;
            Adjacencia *newAdjIda2 = NULL;

//            Adjacencia *currAdjVolta = aVolta;
            Adjacencia *newAdjVolta = NULL;
            Adjacencia *newAdjVolta2 = NULL;

            if((aIda != NULL) && aVolta != NULL)
            {
                for(int i = 0; i < grafo->getVerticeCount(); i++)
                {
//                    cout << "v1: " << aIda->getIdVertice1() << " -- i: " << i << endl;
//                    cout << "i: " << i << " -- v2: " << aIda->getIdVertice2() << endl;
//
//                    cout << grafo->existsAdjacencia(aIda->getIdVertice1(), i) << endl;
//                    cout << grafo->existsAdjacencia(i, aIda->getIdVertice2()) << endl;

                    if(!visited[i] && grafo->existsAdjacencia(aIda->getIdVertice1(), i) && grafo->existsAdjacencia(i, aIda->getIdVertice2()))
                    {
                        Adjacencia *adj1 = grafo->getAdjacencia(aIda->getIdVertice1(), i);
                        Adjacencia *adj2 = grafo->getAdjacencia(i, aIda->getIdVertice2());

//                cout << "Current: " << currAdjIda->getWeight() << endl;
//                cout << "Value: " << (adj1->getWeight() + adj2->getWeight()) << endl;

                        if((adj1 != NULL) && (adj2 != NULL)
                            && (truck->getCapacity() >= grafo->getVerticeWeight(adj1->getIdVertice2()))
                            && ((adj1->getWeight() + adj2->getWeight()) < aIda->getWeight()))
                        {
                            if(newAdjIda != NULL)
                            {
//                                cout << "Adicionando capacidade" << endl;
//                                cout << "Capacidade atual: " << truck->getCapacity() << endl;

                            // Adjacência anterior não é mais interessante
                                truck->addCapacity(grafo->getVerticeWeight(adj1->getIdVertice2()));

//                                cout << "Capacidade atualizada: " << truck->getCapacity() << endl;
//                                visited[adj1->getIdVertice2()] = false;
//                                visitedLength--;

                                //Não preciso remover um dos visitados porque estou trocando um pelo outro
                            }
                            else
                            {
//                                cout << "Removendo capacidade" << endl;
//                                cout << "Capacidade atual: " << truck->getCapacity() << endl;

                                truck->removeCapacity(grafo->getVerticeWeight(adj1->getIdVertice2()));

//                                cout << "Capacidade atualizada: " << truck->getCapacity() << endl;
//                                visited[adj1->getIdVertice2()] = true;
//                                visitedLength++;
                            }

//                            cout << "Substituindo ida" << endl << endl;
                            newAdjIda = adj1;
                            newAdjIda2 = adj2;
                        }
                    }

//            cout << "v1: " << aVolta->getIdVertice1() << " -- i: " << i << endl;
//            cout << "i: " << i << " -- v2: " << aVolta->getIdVertice2() << endl;
//
//            cout << grafo->existsAdjacencia(aVolta->getIdVertice1(), i) << endl;
//            cout << grafo->existsAdjacencia(i, aVolta->getIdVertice2()) << endl;

                    if(!visited[i] && grafo->existsAdjacencia(aVolta->getIdVertice1(), i) && grafo->existsAdjacencia(i, aVolta->getIdVertice2()))
                    {
                        Adjacencia *adj1 = grafo->getAdjacencia(aVolta->getIdVertice1(), i);
                        Adjacencia *adj2 = grafo->getAdjacencia(i, aVolta->getIdVertice2());

//                        cout << "Current: " << truck->getCapacity() << endl;
//                        cout << "Value: " << grafo->getVerticeWeight(adj1->getIdVertice2()) << endl;

                        if((adj1 != NULL) && (adj2 != NULL)
                            && (truck->getCapacity() >= grafo->getVerticeWeight(adj1->getIdVertice2()))
                            && ((adj1->getWeight() + adj2->getWeight()) < aVolta->getWeight()))
                        {
                            if(newAdjVolta != NULL)
                            {
//                                cout << "Adicionando capacidade" << endl;
//                                cout << "Capacidade atual: " << truck->getCapacity() << endl;

                            // Adjacência anterior não é mais interessante
                                truck->addCapacity(grafo->getVerticeWeight(adj1->getIdVertice2()));

//                                cout << "Capacidade atualizada: " << truck->getCapacity() << endl;
//                                visited[adj1->getIdVertice2()] = false;
//                                visited--;
                            }
                            else
                            {
//                                cout << "Removendo capacidade" << endl;
//                                cout << "Capacidade atual: " << truck->getCapacity() << endl;

                                truck->removeCapacity(grafo->getVerticeWeight(adj1->getIdVertice2()));

//                                cout << "Capacidade atualizada: " << truck->getCapacity() << endl;
//                                visited[adj1->getIdVertice2()] = true;
//                                visitedLength++;
                            }

//                            cout << "Substituindo volta" << endl;
//                        truck->addCapacity(grafo->getVerticeWeight(aVolta->getIdVertice2()));
                            newAdjVolta = adj1;
                            newAdjVolta2 = adj2;
                        }
                    }
//            cout << endl << endl;
                }

                if((newAdjIda != NULL) && (newAdjIda2 != NULL))
                {
//                cout << "Capacidade atual: " << truck->getCapacity() << endl;
//                truck->removeCapacity(grafo->getVerticeWeight(newAdjIda->getIdVertice2()));
//                cout << "Capacidade atualizada: " << truck->getCapacity() << endl;

                    solution->remove(idAdjIda);
                    solution->insert(newAdjIda, InsertEnd);
                    solution->insert(newAdjIda2, InsertEnd);
                    visited[newAdjIda->getIdVertice2()] = true;
                    visitedLength++;
                }

                if((newAdjVolta != NULL) && (newAdjVolta2 != NULL))
                {
//                truck->removeCapacity(grafo->getVerticeWeight(newAdjVolta->getIdVertice2()) + grafo->getVerticeWeight(newAdjVolta2->getIdVertice2()));
                    solution->remove(idAdjVolta);
                    solution->insert(newAdjVolta, InsertEnd);
                    solution->insert(newAdjVolta2, InsertEnd);
                    visited[newAdjVolta->getIdVertice2()] = true;
                    visitedLength++;
                }
            }
            else
            {
                cout << "[ Erro ] > Ida ou volta nulas!" << endl;
            }

            cout << "Truck: " << truck->getCapacity() << endl;
            cout << "Visited: " << visitedLength << " -- Count: " << grafo->getVerticeCount() - 1 << endl;
//        break;
        }

        if((visitedLength < grafo->getVerticeCount() - 1))
        {
            truck->resetCapacity();
        }

        solution->start();

        cout << "---------- Solução ----------" << endl;

        for(int i = 0; i < solution->getLength(); i++)
        {
            Adjacencia *adj = solution->getCurrentInfo();

            cout << "IdVertice1: " << adj->getIdVertice1() << " -- IdVertice2: " << adj->getIdVertice2() << endl;
            cout << "Weigth: " << adj->getWeight() << endl;

            dij += adj->getWeight();
            solution->next();
        }

        cout << "-----------------------------" << endl;

//        solution->print();
        solution->clear();
        cout << endl;
    }

    return dij;
}



//
//HeuristicCVRP::~HeuristicCVRP()
//{
//    delete this->grafo;
//    delete this->nodeRateList;
//}
//
//void HeuristicCVRP::calculateNodeRates(Floyd floyd)
//{
//    OrderedList<Adjacencia> *nodeRateList = new OrderedList<Adjacencia>();
//
//    for(int i = 0; i < this->grafo->getVerticeCount(); i++)
//    {
//        for(int j = 0; j < this->grafo->getVerticeCount(); j++)
//        {
//            if(i != j)
//            {
//                nodeRateList->insert(j, floyd.dij[i][j], grafo->getVerticeList()[i].getAdjacencia(j));
//            }
//        }
//    }
//
//    this->nodeRateList = nodeRateList;
//}
//
//void HeuristicCVRP::printNodeRateList()
//{
//    Floyd floyd = FloydWarshall::get(this->grafo);
//    this->calculateNodeRates(floyd);
//    this->nodeRateList->start();
//
//    while(!this->nodeRateList->isEnd())
//    {
//        cout << "Vértice: " << this->nodeRateList->getCurrentId() << " -- Rate: " << this->nodeRateList->getCurrentValue() << endl;
//        this->nodeRateList->next();
//    }
//}
//
//int HeuristicCVRP::run(int nodeBase, float vehicleCapacity)
//{
//    int minDij = 0;
//
//    if(!this->grafo->isConexo())
//    {
//        return minDij;
//    }
//
//    Floyd floyd = FloydWarshall::get(this->grafo);
//    this->calculateNodeRates(floyd);
//
//    int iteration = 0;
//    int visitedLength = 0;
//    bool *visited = new bool[grafo->getVerticeCount() * grafo->getVerticeCount()];
//    Vehicle *truck = new Vehicle(1, vehicleCapacity, nodeBase);
//
//    visited[nodeBase] = true;
//
//    while(iteration < itCount)
//    {
//        while(visitedLength < (grafo->getVerticeCount() - 1))
//        {
////            float decrease = (truck->getCapacity() - grafo->getVerticeWeight(nodeRateList->getStartId()));
//
//            while(!nodeRateList->isEmpty() && (truck->getCapacity() > 0)
//                  && ((truck->getCapacity() - grafo->getVerticeWeight(nodeRateList->getStartId())) >= 0))
//            {
////                cout << "Id: " << nodeRateList->getStartId() << " -- " << truck->getCapacity() << " --- " << (truck->getCapacity() - grafo->getVerticeWeight(nodeRateList->getStartId())) << endl;
////                cout << "Id: " << nodeRateList->getStartId() << " -- Base: " << nodeBase << endl;
//
//                if((nodeRateList->getStartId() != nodeBase) && !visited[nodeRateList->getStartId()]
//                   && ((floyd.dij[truck->getCurrentPosition()][this->nodeRateList->getStartId()]) != INFINITE))
//                {
//                    cout << "Passei pelo nó " << nodeRateList->getStartId() << endl;
//                    visited[nodeRateList->getStartId()] = true;
////                cout << "Capacidade atual: " << truck->getCapacity() << endl;
////                cout << "Removendo capacidade: " << grafo->getVerticeWeight(nodeRateList->getStartId()) << endl;
//
////                    cout << "Add current Value: " << floyd.dij[truck->getCurrentPosition()][this->nodeRateList->getStartId()] << endl;
//                    minDij += floyd.dij[truck->getCurrentPosition()][this->nodeRateList->getStartId()];
//
//                    truck->removeCapacity(grafo->getVerticeWeight(nodeRateList->getStartId()));
//                    truck->setCurrentPosition(nodeRateList->getStartId());
//
////                    minDij += this->nodeRateList->getCurrentValue();
//                    this->nodeRateList->remove(InsertStart);
//                    visitedLength++;
//
//                }
//                else
//                {
////                    visitedLength++;
////                    cout << "Estou aqui!" << endl;
//                    this->nodeRateList->remove(InsertStart);
//                }
//            }
//
//            if(grafo->getVerticeWeight(nodeRateList->getStartId()) == INFINITE)
//            {
//                this->nodeRateList->remove(InsertStart);
//            }
//
////            cout << "Add base value: " << floyd.dij[truck->getCurrentPosition()][nodeBase] << endl;
//            minDij += floyd.dij[truck->getCurrentPosition()][nodeBase];
//
//            truck->setCurrentPosition(nodeBase);
//            truck->resetCapacity();
//
//            cout << "Voltei para base!" << endl;
//        }
//
//        iteration++;
//    }
//
//    return minDij;
//}
