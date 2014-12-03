#include "../../header/grafo/ListaAdjacenciaVet.h"
#include "../../header/Helper.h"

ListaAdjacenciaVet::ListaAdjacenciaVet(int verticeCount, bool isDirected) : ListaAdjacenciaVet(verticeCount, isDirected, InsertNone) { }

ListaAdjacenciaVet::ListaAdjacenciaVet(int verticeCount, bool isDirected, InsertType type)
{
    this->verticeCount = verticeCount;
    this->isDirected = isDirected;

    this->verticeList = new Vertice[verticeCount];

    for(int i = 0; i < verticeCount; i++)
    {
        this->verticeList[i].setAdjInsertType(type);
    }
}

ListaAdjacenciaVet::~ListaAdjacenciaVet()
{
    delete this->verticeList;
}

bool ListaAdjacenciaVet::existsVertice(int idVertice)
{
    return ((idVertice >= 0) && (idVertice < this->verticeCount));
}

bool ListaAdjacenciaVet::depth(bool *visited)
{
    if((this->verticeCount > 0) && (visited != NULL))
    {
        for(int i = 0; i < this->verticeCount; i++)
        {
            visited[i] = false;
        }

        for(int i = 0; i < this->verticeCount; i++)
        {
            OrderedList<Adjacencia> *verticeAdjList = this->verticeList[i].getAdjacenciaList(); // Pega a lista de adjacência do nó
            verticeAdjList->start();

            while(!verticeAdjList->isEnd())
            {
                Adjacencia *verticeAdj = verticeAdjList->getCurrentInfo();
                verticeAdjList->next();
                visited[verticeAdj->getIdVertice1()] = true;
            }
        }

        for(int i = 0; i < this->verticeCount; i++)
        {
            if(!visited[i])
            {
                return false;
            }
        }
    }

    return true;
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

    visited[s] = true;
    OrderedList<int> queue1;
    queue1.insert(s, InsertEnd);

    while(!queue1.isEmpty())
    {
        s = queue1.getStartId();
        queue1.remove(InsertStart);

        OrderedList<Adjacencia> *verticeAdjList = this->verticeList[s].getAdjacenciaList(); // Pega a lista de adjacência do nó
        verticeAdjList->start();

        while(!verticeAdjList->isEnd())
        {
            Adjacencia *verticeAdj = verticeAdjList->getCurrentInfo();
            verticeAdjList->next();

            if(verticeAdj->getIdVertice1() == d)
                return true;

            if(!visited[verticeAdj->getIdVertice2()])
            {
                visited[verticeAdj->getIdVertice1()] = true;
                queue1.insert(verticeAdj->getIdVertice2(), InsertEnd);
            }
        }
    }

    return false;
}

Vertice* ListaAdjacenciaVet::getVerticeList()
{
    return this->verticeList;
}

Vertice ListaAdjacenciaVet::getVertice(int idVertice)
{
    return this->verticeList[idVertice];
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


float ListaAdjacenciaVet::getVerticeWeight(int idVertice)
{
    if(existsVertice(idVertice))
    {
        return this->verticeList[idVertice].getWeight();
    }
    else
    {
        cout << "[ Erro ]: Nó não existente no grafo!" << endl;
    }

    return 0;
}

void ListaAdjacenciaVet::setVerticeWeight(int idVertice, float weight)
{
    if(existsVertice(idVertice))
    {
        this->verticeList[idVertice].setWeight(weight);
    }
    else
    {
        cout << "[ Erro ]: Nó não existente no grafo!" << endl;
    }
}

void ListaAdjacenciaVet::addAdjacencia(int idVertice1, int idVertice2, float weight)
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
    bool *visited = new bool[this->verticeCount];
    bool conexo = this->depth(visited);
    delete visited;

    return conexo;
}

int ListaAdjacenciaVet::compConexaCount()
{
    int count = 1;
    bool *visited = new bool[this->verticeCount];

    this->depth(visited);

    for(int i = 0; i < this->verticeCount; i++)
    {
        if(!visited[i])
        {
            count++;
        }
    }

    delete visited;
    return count;
}

bool ListaAdjacenciaVet::containsCiclo(int startIdVertice)
{
    OrderedList<Adjacencia> *verticeAdjList = this->verticeList[startIdVertice].getAdjacenciaList();
    verticeAdjList->start();

    if(verticeAdjList->getCurrentInfo() != NULL)
    {
        return this->depth(verticeAdjList->getCurrentInfo()->getIdVertice2(), startIdVertice);
    }

    return false;
}

bool ListaAdjacenciaVet::containsCaminho(int startIdVertice, int endIdVertice)
{
    return this->depth(startIdVertice, endIdVertice);
}
