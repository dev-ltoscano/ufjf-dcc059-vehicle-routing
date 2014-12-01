#include "../../header/heuristic/HeuristicCVRP.h"

HeuristicCVRP::HeuristicCVRP(ListaAdjacenciaVet *grafo, HeuristicType heuristic, int itCount)
{
    this->grafo = grafo;
    this->heuristic = heuristic;
    this->itCount = (heuristic == Gulosa) ? 1 : itCount;
    this->nodeRateList = NULL;
}

HeuristicCVRP::~HeuristicCVRP()
{
    delete this->grafo;
    delete this->nodeRateList;
}

void HeuristicCVRP::calculateNodeRates(Floyd floyd)
{
    OrderedList<Adjacencia> *nodeRateList = new OrderedList<Adjacencia>();

    for(int i = 0; i < this->grafo->getVerticeCount(); i++)
    {
        for(int j = 0; j < this->grafo->getVerticeCount(); j++)
        {
            if(i != j)
            {
                nodeRateList->insert(j, floyd.dij[i][j], grafo->getVerticeList()[i].getAdjacencia(j));
            }
        }
    }

    this->nodeRateList = nodeRateList;
}

void HeuristicCVRP::printNodeRateList()
{
    Floyd floyd = FloydWarshall::get(this->grafo);
    this->calculateNodeRates(floyd);
    this->nodeRateList->start();

    while(!this->nodeRateList->isEnd())
    {
        cout << "Vértice: " << this->nodeRateList->getCurrentId() << " -- Rate: " << this->nodeRateList->getCurrentValue() << endl;
        this->nodeRateList->next();
    }
}

int HeuristicCVRP::run(int nodeBase, float vehicleCapacity)
{
    int minDij = 0;

    if(!this->grafo->isConexo())
    {
        return minDij;
    }

    Floyd floyd = FloydWarshall::get(this->grafo);
    this->calculateNodeRates(floyd);

    int iteration = 0;
    int visitedLength = 0;
    bool *visited = new bool[grafo->getVerticeCount() * grafo->getVerticeCount()];
    Vehicle *truck = new Vehicle(1, vehicleCapacity, nodeBase);

    visited[nodeBase] = true;

    while(iteration < itCount)
    {
        while(visitedLength < (grafo->getVerticeCount() - 1))
        {
//            float decrease = (truck->getCapacity() - grafo->getVerticeWeight(nodeRateList->getStartId()));

            while(!nodeRateList->isEmpty() && (truck->getCapacity() > 0)
                  && ((truck->getCapacity() - grafo->getVerticeWeight(nodeRateList->getStartId())) >= 0))
            {
//                cout << "Id: " << nodeRateList->getStartId() << " -- " << truck->getCapacity() << " --- " << (truck->getCapacity() - grafo->getVerticeWeight(nodeRateList->getStartId())) << endl;
//                cout << "Id: " << nodeRateList->getStartId() << " -- Base: " << nodeBase << endl;

                if((nodeRateList->getStartId() != nodeBase) && !visited[nodeRateList->getStartId()]
                   && ((floyd.dij[truck->getCurrentPosition()][this->nodeRateList->getStartId()]) != INFINITE))
                {
                    cout << "Passei pelo nó " << nodeRateList->getStartId() << endl;
                    visited[nodeRateList->getStartId()] = true;
//                cout << "Capacidade atual: " << truck->getCapacity() << endl;
//                cout << "Removendo capacidade: " << grafo->getVerticeWeight(nodeRateList->getStartId()) << endl;

//                    cout << "Add current Value: " << floyd.dij[truck->getCurrentPosition()][this->nodeRateList->getStartId()] << endl;
                    minDij += floyd.dij[truck->getCurrentPosition()][this->nodeRateList->getStartId()];

                    truck->removeCapacity(grafo->getVerticeWeight(nodeRateList->getStartId()));
                    truck->setCurrentPosition(nodeRateList->getStartId());

//                    minDij += this->nodeRateList->getCurrentValue();
                    this->nodeRateList->remove(InsertStart);
                    visitedLength++;

                }
                else
                {
//                    visitedLength++;
//                    cout << "Estou aqui!" << endl;
                    this->nodeRateList->remove(InsertStart);
                }
            }

            if(grafo->getVerticeWeight(nodeRateList->getStartId()) == INFINITE)
            {
                this->nodeRateList->remove(InsertStart);
            }

//            cout << "Add base value: " << floyd.dij[truck->getCurrentPosition()][nodeBase] << endl;
            minDij += floyd.dij[truck->getCurrentPosition()][nodeBase];

            truck->setCurrentPosition(nodeBase);
            truck->resetCapacity();

            cout << "Voltei para base!" << endl;
        }

        iteration++;
    }

    return minDij;
}
