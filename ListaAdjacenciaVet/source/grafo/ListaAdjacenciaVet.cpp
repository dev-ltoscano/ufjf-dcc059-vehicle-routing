#include "../../header/grafo/ListaAdjacenciaVet.h"
#include "../../header/Helper.h"

ListaAdjacenciaVet::ListaAdjacenciaVet(int verticeCount, bool isDirected) : ListaAdjacenciaVet(verticeCount, isDirected, ListUnordered) { }

ListaAdjacenciaVet::ListaAdjacenciaVet(int verticeCount, bool isDirected, OperationType type)
{
    this->verticeCount = verticeCount;
    this->isDirected = isDirected;

    // Inicializa o vetor de vértices
    for(int i = 0; i < verticeCount; i++)
    {
        this->verticeList.push_back(new Vertice());
    }
}

ListaAdjacenciaVet::~ListaAdjacenciaVet()
{
    for(int i = 0; i < verticeCount; i++)
    {
        delete this->verticeList[i];
    }
}

bool ListaAdjacenciaVet::existsVertice(int idVertice)
{
    return ((idVertice >= 0) && (idVertice < this->verticeCount));
}

bool ListaAdjacenciaVet::depth(bool *visited)
{
    if((this->verticeCount > 0) && (visited != NULL))
    {
        // Marca todos como não visitado
        for(int i = 0; i < this->verticeCount; i++)
        {
            visited[i] = false;
        }

        // Para cada vértice do grafo
        for(int i = 0; i < this->verticeCount; i++)
        {
            // Pega a lista de adjacência do nó
            OrderedList<Adjacencia> *verticeAdjList = (*this->verticeList[i]).getAdjacenciaList();

            verticeAdjList->start();
            while(!verticeAdjList->isEnd())
            {
                Adjacencia *verticeAdj = verticeAdjList->getCurrentInfo();
                verticeAdjList->next();

                // Marca como visitado
                visited[verticeAdj->getIdVertice1()] = true;
            }
        }

        // Verifica se todos os nós foram visitados
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

    // Marca todos como não visitado
    for(int i = 0; i < this->verticeCount; i++)
    {
        visited[i] = false;
    }

    visited[s] = true;

    // Usando a lista como uma fila
    OrderedList<int> queue1;
    queue1.insert(s, ListEnd);

    while(!queue1.isEmpty())
    {
        s = queue1.getStartId();
        queue1.remove(ListStart);

        // Pega a lista de adjacência do nó
        OrderedList<Adjacencia> *verticeAdjList = (*this->verticeList[s]).getAdjacenciaList();
        verticeAdjList->start();

        while(!verticeAdjList->isEnd())
        {
            Adjacencia *verticeAdj = verticeAdjList->getCurrentInfo();
            verticeAdjList->next();

            if(verticeAdj->getIdVertice1() == d)
                return true;

            if(!visited[verticeAdj->getIdVertice2()])
            {
                // Marca o nó atual como visitado
                visited[verticeAdj->getIdVertice1()] = true;

                // Insere na fila o adjacente
                queue1.insert(verticeAdj->getIdVertice2(), ListEnd);
            }
        }
    }

    delete [] visited;
    return false;
}

int ListaAdjacenciaVet::getVerticeCount()
{
    return this->verticeCount;
}

int ListaAdjacenciaVet::getVerticeGrau(int idVertice)
{
    if(existsVertice(idVertice))
    {
        return (*this->verticeList[idVertice]).getGrau();
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
        return (*this->verticeList[idVertice]).getWeight();
    }
    else
    {
        cout << "[ Erro ]: Nó não existente no grafo!" << endl;
    }

    return 0;
}

Point* ListaAdjacenciaVet::getVerticePoint(int idVertice)
{
    if(existsVertice(idVertice))
    {
        return (*this->verticeList[idVertice]).getCoord();
    }
    else
    {
        cout << "[ Erro ]: Nó não existente no grafo!" << endl;
    }

    return NULL;
}

void ListaAdjacenciaVet::setVerticePoint(int idVertice, Point *coord)
{
    if(existsVertice(idVertice))
    {
        (*this->verticeList[idVertice]).setCoord(coord);
    }
    else
    {
        cout << "[ Erro ]: Nó não existente no grafo!" << endl;
    }
}

void ListaAdjacenciaVet::setVerticeWeight(int idVertice, float weight)
{
    if(existsVertice(idVertice))
    {
        (*this->verticeList[idVertice]).setWeight(weight);
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
        // Se o grafo é direcionado
        if(isDirected)
        {
            // Insere apenas o arco (id1, id2)
            (*this->verticeList[idVertice1]).addAdjacencia(idVertice1, idVertice2, weight);
        }
        else
        {
            // Caso contrário, arco de ida e volta
            (*this->verticeList[idVertice1]).addAdjacencia(idVertice1, idVertice2, weight);
            (*this->verticeList[idVertice2]).addAdjacencia(idVertice2, idVertice1, weight);
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
        // Se o grafo é direcionado
        if(isDirected)
        {
            // Remover o arco (id1, id2)
            (*this->verticeList[idVertice1]).removeAdjacencia(idVertice2);
        }
        else
        {
            // Caso contrário remover ida e volta
            (*this->verticeList[idVertice1]).removeAdjacencia(idVertice2);
            (*this->verticeList[idVertice2]).removeAdjacencia(idVertice1);
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
        return (*this->verticeList[idVertice1]).existsAdjacencia(idVertice2);
    }
    else
    {
        cout << "[ Erro ]: Nó não existente no grafo!" << endl;
    }

    return false;
}

OrderedList<Adjacencia>* ListaAdjacenciaVet::getAdjacenciaList(int idVertice)
{
    if(existsVertice(idVertice))
    {
        return (*this->verticeList[idVertice]).getAdjacenciaList();
    }

    return NULL;
}

Adjacencia* ListaAdjacenciaVet::getAdjacencia(int idVertice1, int idVertice2)
{
    if(existsVertice(idVertice1) && existsVertice(idVertice2) && existsAdjacencia(idVertice1, idVertice2))
    {
        return ((*this->verticeList[idVertice1]).getAdjacencia(idVertice2));
    }

    return NULL;
}

int ListaAdjacenciaVet::getAdjacenciaCount()
{
    int count = 0;

    for(int i = 0; i < this->verticeCount; i++)
    {
        count += (*this->verticeList[i]).getAdjacenciaList()->getLength();
    }

    return count;
}

bool ListaAdjacenciaVet::isConexo()
{
    bool *visited = new bool[this->verticeCount];

    bool conexo = this->depth(visited);

    delete [] visited;
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

    delete [] visited;
    return count;
}

bool ListaAdjacenciaVet::containsCiclo(int startIdVertice)
{
    OrderedList<Adjacencia> *verticeAdjList = (*this->verticeList[startIdVertice]).getAdjacenciaList();
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
