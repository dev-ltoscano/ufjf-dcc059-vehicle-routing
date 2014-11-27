#include "../../header/grafo/ListaAdjacenciaVet.h"
#include "../../header/Helper.h"

ListaAdjacenciaVet::ListaAdjacenciaVet(int verticeCount, bool isDirected)
{
    this->verticeCount = verticeCount;
    this->verticeList = new Vertice[verticeCount];

    this->isDirected = isDirected;
}

ListaAdjacenciaVet::ListaAdjacenciaVet(int verticeCount, bool isDirected, bool isOrderAdjList)
{
    this->verticeCount = verticeCount;
    this->verticeList = new Vertice[verticeCount];

    this->isDirected = isDirected;
}

ListaAdjacenciaVet::~ListaAdjacenciaVet()
{
    delete this->verticeList;
}

int ListaAdjacenciaVet::getVerticeCount()
{
    return this->verticeCount;
}

int ListaAdjacenciaVet::getVerticeGrau(int idVertice)
{
    if(existsVertice(idVertice))
    {
        return this->verticeList[idVertice].getGrau();
    }
    else
    {
        cout << "[ Erro ]: Nó não existente no grafo!" << endl;
    }

    return -1;
}

int ListaAdjacenciaVet::getVerticeWeight(int idVertice)
{
    if(existsVertice(idVertice))
    {
        return this->verticeList[idVertice].getWeight();
    }
    else
    {
        cout << "[ Erro ]: Nó não existente no grafo!" << endl;
    }

    return -1;
}

Vertice* ListaAdjacenciaVet::getVerticeList()
{
    return this->verticeList;
}

bool ListaAdjacenciaVet::existsVertice(int idVertice)
{
    return ((idVertice >= 0) && (idVertice < this->verticeCount));
}

bool ListaAdjacenciaVet::depth(int s, int d)
{
    if(s == d)
        return true;

    bool *visited = new bool[this->verticeCount];

    for(int i = 0; i < this->verticeCount; i++)
    {
        visited[i] = false;
    }

    list<int> queue;
    visited[s] = true;
    queue.push_back(s);

    while(!queue.empty())
    {
        s = queue.front();
        queue.pop_front();

        OrderedList *verticeAdjList = this->verticeList[s].getAdjacenciaList(); // Pega a lista de adjacência do nó
        verticeAdjList->start();

        while(!verticeAdjList->isEnd())
        {
            Adjacencia *verticeAdj = verticeAdjList->getAdjacencia();
            verticeAdjList->next();

            if(verticeAdj->getIdVertice1() == d)
                return true;

            if(!visited[verticeAdj->getIdVertice2()])
            {
                visited[verticeAdj->getIdVertice1()] = true;
                queue.push_back(verticeAdj->getIdVertice2());
            }
        }
    }

    return false;
}

void ListaAdjacenciaVet::depth(int idNode, int *verticeList)
{
    verticeList[idNode] = 1; // Marca o nó como visitado
    OrderedList *verticeAdjList = this->verticeList[idNode].getAdjacenciaList(); // Pega a lista de adjacência do nó

    verticeAdjList->start();

    while(!verticeAdjList->isEnd())
    {
        Adjacencia *verticeAdj = verticeAdjList->getAdjacencia();
        verticeAdjList->next();

        int idVertice2 = verticeAdj->getIdVertice2(); // Pega o id do nó adjacente

        if(verticeList[idVertice2] != 1)
        {
            this->depth(idVertice2, verticeList); // Busca em profundidade no nó adjacente
        }
    }
}

bool ListaAdjacenciaVet::depth(int startIdVertice, int *verticeList, int idVerticeCurrent)
{
    if(idVerticeCurrent == startIdVertice)
    {
        delete verticeList;
        return true;
    }

    verticeList[idVerticeCurrent] = 1; // Marca o nó como visitado
    OrderedList *verticeAdjList = this->verticeList[idVerticeCurrent].getAdjacenciaList(); // Pega a lista de adjacência do nó

    verticeAdjList->start();

    while(!verticeAdjList->isEnd())
    {
        Adjacencia *verticeAdj = verticeAdjList->getAdjacencia();
        verticeAdjList->next();

        int idVertice2 = verticeAdj->getIdVertice2(); // Pega o id do nó adjacente

        if(verticeList[idVertice2] != 1)
        {
            return this->depth(startIdVertice, verticeList, idVertice2);
        }
    }

    return false;
}

void ListaAdjacenciaVet::addAdjacencia(int idVertice1, int idVertice2, int weight)
{
    if(existsVertice(idVertice1) && existsVertice(idVertice2))
    {
        if(isDirected)
        {
            (this->verticeList[idVertice1]).addAdjacencia(idVertice1, idVertice2, weight);
        }
        else
        {
            (this->verticeList[idVertice1]).addAdjacencia(idVertice1, idVertice2, weight);
            (this->verticeList[idVertice2]).addAdjacencia(idVertice2, idVertice1, weight);
        }
    }
    else
    {
        cout << "[ Erro ]: Nó não existente no grafo!" << endl;
    }
}

void ListaAdjacenciaVet::removeAdjacencia(int idVertice1, int idVertice2)
{
    if(existsVertice(idVertice1) && existsVertice(idVertice2))
    {
        if(isDirected)
        {
            (this->verticeList[idVertice1]).removeAdjacencia(idVertice2);
        }
        else
        {
            (this->verticeList[idVertice1]).removeAdjacencia(idVertice2);
            (this->verticeList[idVertice2]).removeAdjacencia(idVertice1);
        }
    }
    else
    {
        cout << "[ Erro ]: Nó não existente no grafo!" << endl;
    }
}

bool ListaAdjacenciaVet::existsAdjacencia(int idVertice1, int idVertice2)
{
    if(existsVertice(idVertice1) && existsVertice(idVertice2))
    {
        return (this->verticeList[idVertice1]).existsAdjacencia(idVertice2);
    }
    else
    {
        cout << "[ Erro ]: Nó não existente no grafo!" << endl;
    }

    return false;
}

int ListaAdjacenciaVet::getAdjacenciaCount()
{
    int count = 0;

    for(int i = 0; i < this->verticeCount; i++)
    {
        count += this->verticeList[i].getAdjacenciaList()->getLength();
    }

    return count;
}

bool ListaAdjacenciaVet::isConexo()
{
    int *nodeVet = new int[this->verticeCount];
    this->depth(0, nodeVet);

    for (int i = 0; i < this->verticeCount; i++)
    {
        if(nodeVet[i] != 1)
        {
            delete nodeVet;
            return false;
        }
    }

    return true;
}

int ListaAdjacenciaVet::compConexaCount()
{
    int compCount = 0;
    int *nodeVet = new int[this->verticeCount];

    for (int i = 0; i < this->verticeCount; i++)
    {
        if(nodeVet[i] != 1)
        {
            compCount++;
            this->depth(i, nodeVet);
        }
    }

    return compCount;
}

bool ListaAdjacenciaVet::containsCiclo(int startIdVertice)
{
    OrderedList *verticeAdjList = this->verticeList[startIdVertice].getAdjacenciaList();
    verticeAdjList->start();

    return this->depth(startIdVertice, new int[this->verticeCount], verticeAdjList->getAdjacencia()->getIdVertice2());
}

bool ListaAdjacenciaVet::containsCaminho(int startIdVertice, int endIdVertice)
{
    return this->depth(startIdVertice, endIdVertice);

//    return this->depth(endIdVertice, Helper::initializeVector(this->verticeCount), startIdVertice);
}
