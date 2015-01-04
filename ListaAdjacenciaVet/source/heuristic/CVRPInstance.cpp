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
                if((i != j) && !grafo->existsAdjacencia(i, j)) // Sem arestas paralelas e sem la�os
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
        cout << "[ Erro ] : Quantidade de v�rtices inv�lida para o CVRP" << endl;
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
        cout << "[ Erro ] : Capacidade do ve�culo inv�lida para o CVRP" << endl;
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
            cout << "[ Erro ] : V�rtice da base inv�lido para a inst�ncia do CVRP" << endl;
        }
    }
    else
    {
        cout << "[ Erro ] : N�o foi definida a quantidade de v�rtices para a inst�ncia do CVRP" << endl;
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
            cout << "[ Erro ] : V�rtice n�o existe na inst�ncia do CVRP" << endl;
        }
    }
    else
    {
        cout << "[ Erro ] : N�o foi definida a quantidade de v�rtices para a inst�ncia do CVRP" << endl;
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
            cout << "[ Erro ] : V�rtice n�o existe na inst�ncia do CVRP" << endl;
        }
    }
    else
    {
        cout << "[ Erro ] : N�o foi definida a quantidade de v�rtices para a inst�ncia do CVRP" << endl;
    }
}
