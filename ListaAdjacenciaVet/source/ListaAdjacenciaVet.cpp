#include "../header/ListaAdjacenciaVet.h"

ListaAdjacenciaVet::ListaAdjacenciaVet(int nodeCount, bool isDirected)
{
    this->nodeCount = nodeCount;
    this->nodeList = new Node[nodeCount];

    this->isDirected = isDirected;
}

ListaAdjacenciaVet::~ListaAdjacenciaVet()
{
    delete this->nodeList;
}

bool ListaAdjacenciaVet::existsNode(int idNode)
{
    return ((idNode >= 0) && (idNode < nodeCount));
}

void ListaAdjacenciaVet::depth(int idNode, int *nodeVet)
{
    nodeVet[idNode] = 1; // Marca o nó como visitado
    list<Adjacencia*> nodeAdjList = this->nodeList[idNode].getAdjacenciaList(); // Pega a lista de adjacência do nó

    for (typename list<Adjacencia*>::iterator it = nodeAdjList.begin(); it != nodeAdjList.end(); it++)
    {
        Adjacencia *nodeAdj = (*it);
        int idNodeAdj = nodeAdj->getAdjacenciaInfo()->getIdNodeAdj(); // Pega o id do nó adjacente

        if(nodeVet[idNodeAdj] != 1)
        {
            this->depth(idNodeAdj, nodeVet); // Busca em profundidade no nó adjacente
        }
    }
}

bool ListaAdjacenciaVet::cicle(int idNode, int startIdNode, int *nodeVet)
{
    if(idNode == startIdNode)
    {
        delete nodeVet;
        return true;
    }

    nodeVet[idNode] = 1; // Marca o nó como visitado
    list<Adjacencia*> nodeAdjList = this->nodeList[idNode].getAdjacenciaList(); // Pega a lista de adjacência do nó

    for (typename list<Adjacencia*>::iterator it = nodeAdjList.begin(); it != nodeAdjList.end(); it++)
    {
        Adjacencia *nodeAdj = (*it);
        int idNodeAdj = nodeAdj->getAdjacenciaInfo()->getIdNodeAdj(); // Pega o id do nó adjacente

        if(nodeVet[idNodeAdj] != 1)
        {
            return this->cicle(idNodeAdj, startIdNode, nodeVet);
        }
    }

    return false;
}

bool ListaAdjacenciaVet::path(int idNode, int endIdNode,  int *nodeVet)
{
    if(idNode == endIdNode)
    {
        delete nodeVet;
        return true;
    }

    nodeVet[idNode] = 1; // Marca o nó como visitado
    list<Adjacencia*> nodeAdjList = this->nodeList[idNode].getAdjacenciaList(); // Pega a lista de adjacência do nó

    for (typename list<Adjacencia*>::iterator it = nodeAdjList.begin(); it != nodeAdjList.end(); it++)
    {
        Adjacencia *nodeAdj = (*it);
        int idNodeAdj = nodeAdj->getAdjacenciaInfo()->getIdNodeAdj(); // Pega o id do nó adjacente

        if(nodeVet[idNodeAdj] != 1)
        {
            return this->path(idNodeAdj, endIdNode, nodeVet);
        }
    }

    return false;
}

void ListaAdjacenciaVet::addAdjacencia(int idNode1, int idNode2)
{
    if(existsNode(idNode1) && existsNode(idNode2))
    {
        if(isDirected)
        {
            (this->nodeList[idNode1]).addAdjacencia(idNode2);
        }
        else
        {
            (this->nodeList[idNode1]).addAdjacencia(idNode2);
            (this->nodeList[idNode2]).addAdjacencia(idNode1);
        }
    }
    else
    {
        cout << "[ Erro ]: Nó não existente no grafo!" << endl;
    }
}

void ListaAdjacenciaVet::removeAdjacencia(int idNode1, int idNode2)
{
    if(existsNode(idNode1) && existsNode(idNode2))
    {
        if(isDirected)
        {
            (this->nodeList[idNode1]).removeAdjacencia(idNode2);
        }
        else
        {
            (this->nodeList[idNode1]).removeAdjacencia(idNode2);
            (this->nodeList[idNode2]).removeAdjacencia(idNode1);
        }
    }
    else
    {
        cout << "[ Erro ]: Nó não existente no grafo!" << endl;
    }
}

bool ListaAdjacenciaVet::existsAdjacencia(int idNode1, int idNode2)
{
    if(existsNode(idNode1) && existsNode(idNode2))
    {
        return (this->nodeList[idNode1]).existsAdjacencia(idNode2);
    }
    else
    {
        cout << "[ Erro ]: Nó não existente no grafo!" << endl;
    }

    return false;
}

int ListaAdjacenciaVet::getGrau(int idNode)
{
    if(existsNode(idNode))
    {
        return this->nodeList[idNode].getGrau();
    }
    else
    {
        cout << "[ Erro ]: Nó não existente no grafo!" << endl;
    }

    return -1;
}

bool ListaAdjacenciaVet::isConexo()
{
    int *nodeVet = new int[this->nodeCount];
    this->depth(0, nodeVet);

    for (int i = 0; i < this->nodeCount; i++)
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
    int *nodeVet = new int[this->nodeCount];

    for (int i = 0; i < this->nodeCount; i++)
    {
        if(nodeVet[i] != 1)
        {
            compCount++;
            this->depth(i, nodeVet);
        }
    }

    return compCount;
}

bool ListaAdjacenciaVet::containsCiclo(int startIdNode)
{
    list<Adjacencia*>::iterator it = this->nodeList[startIdNode].getAdjacenciaList().begin();
    return this->path((*it)->getAdjacenciaInfo()->getIdNodeAdj(), startIdNode, new int[this->nodeCount]);
}

bool ListaAdjacenciaVet::containsCaminho(int startIdNode, int endIdNode)
{
    return this->path(startIdNode, endIdNode, new int[this->nodeCount]);
}
