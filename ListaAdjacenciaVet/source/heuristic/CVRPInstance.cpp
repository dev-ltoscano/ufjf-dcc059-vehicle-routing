#include "../../header/heuristic/CVRPInstance.h"

CVRPInstance::CVRPInstance()
{
    this->verticeCount = 0;
    this->verticeBase = -1;
    this->vehicleCapacity = 0;
    this->grafo = NULL;
}

ListaAdjacenciaVet* CVRPInstance::getInstance()
{
    if(grafo != NULL)
    {
        for(int i = 0; i < verticeCount; i++)
        {
            for(int j = 0; j < verticeCount; j++)
            {
                if((i != j) && !grafo->existsAdjacencia(i, j)) // Sem arestas paralelas e sem laços
                {
                    Point *p1 = this->grafo->getVerticePoint(i);
                    Point *p2 = this->grafo->getVerticePoint(j);
                    float weight = p1->getDistance(p2);
                    grafo->addAdjacencia(i, j, weight);
                }
            }
        }
    }

    return grafo;
}

int CVRPInstance::getVerticeCount()
{
    return this->verticeCount;
}

void CVRPInstance::setVerticeCount(int verticeCount)
{
    if(verticeCount >= 2)
    {
        this->verticeCount = verticeCount;
        this->grafo = new ListaAdjacenciaVet(verticeCount, true, ListOrdered);
    }
    else
    {
        cout << "[ Erro ] : Quantidade de vértices inválida para o CVRP" << endl;
    }
}

int CVRPInstance::getVehicleCapacity()
{
    return this->vehicleCapacity;
}

void CVRPInstance::setVehicleCapacity(float vehicleCapacity)
{
    if(verticeCount >= 0)
    {
        this->vehicleCapacity = vehicleCapacity;
    }
    else
    {
        cout << "[ Erro ] : Capacidade do veículo inválida para o CVRP" << endl;
    }
}

int CVRPInstance::getVerticeBase()
{
    return this->verticeBase;
}

void CVRPInstance::setVerticeBase(int nodeId)
{
    if(grafo != NULL)
    {
        if((nodeId >= 0) && (nodeId < verticeCount))
        {
            this->verticeBase = nodeId;
            grafo->setVerticeWeight(verticeBase, 0);
        }
        else
        {
            cout << "[ Erro ] : Vértice da base inválido para a instância do CVRP" << endl;
        }
    }
    else
    {
        cout << "[ Erro ] : Não foi definida a quantidade de vértices para a instância do CVRP" << endl;
    }
}

void CVRPInstance::addVerticePoint(int idVertice, Point *verticePoint)
{
    if(grafo != NULL)
    {
        if(grafo->existsVertice(idVertice))
        {
            this->grafo->setVerticePoint(idVertice, verticePoint);
        }
        else
        {
            cout << "[ Erro ] : Vértice não existe na instância do CVRP" << endl;
        }
    }
    else
    {
        cout << "[ Erro ] : Não foi definida a quantidade de vértices para a instância do CVRP" << endl;
    }
}

void CVRPInstance::addVerticeDemand(int idVertice, float demand)
{
    if(grafo != NULL)
    {
        if((idVertice != verticeBase) && grafo->existsVertice(idVertice))
        {
            this->grafo->setVerticeWeight(idVertice, demand);
        }
        else
        {
            cout << "[ Erro ] : Vértice não existe na instância do CVRP" << endl;
        }
    }
    else
    {
        cout << "[ Erro ] : Não foi definida a quantidade de vértices para a instância do CVRP" << endl;
    }
}
