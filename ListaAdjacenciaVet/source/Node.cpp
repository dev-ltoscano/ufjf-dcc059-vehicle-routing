#include "../header/Node.h"

Node::Node()
{
    this->nodeInfo = new NodeInfo(0);
}

Node::~Node()
{
    for (list<Adjacencia*>::iterator it = adjacenciaList.begin(); it != adjacenciaList.end(); it++)
    {
        delete (*it);
    }

    delete this->nodeInfo;
}

Adjacencia* Node::getAdjacencia(int idNodeAdj)
{
    for (list<Adjacencia*>::iterator it = adjacenciaList.begin(); it != adjacenciaList.end(); it++)
    {
        if((*it)->getAdjacenciaInfo()->getIdNodeAdj() == idNodeAdj)
            return (*it);
    }

    return NULL;
}

NodeInfo* Node::getNodeInfo()
{
    return this->nodeInfo;
}

void Node::setNodeInfo(NodeInfo *nodeInfo)
{
    this->nodeInfo = nodeInfo;
}

void Node::addAdjacencia(int idNodeAdj)
{
    Adjacencia *nodeAdj = this->getAdjacencia(idNodeAdj);

    if(nodeAdj == NULL)
    {
        this->adjacenciaList.push_front(new Adjacencia(new AdjacenciaInfo(idNodeAdj, 0)));
    }
    else
    {
        cout << "[ Erro ]: Adjacência já existe!" << endl;
    }
}

void Node::removeAdjacencia(int idNodeAdj)
{
    Adjacencia *nodeAdj = this->getAdjacencia(idNodeAdj);

    if(nodeAdj != NULL)
    {
        this->adjacenciaList.remove(nodeAdj);
        delete nodeAdj;
    }
}

bool Node::existsAdjacencia(int idNodeAdj)
{
    return (this->getAdjacencia(idNodeAdj) != NULL);
}

list<Adjacencia*> Node::getAdjacenciaList()
{
    return this->adjacenciaList;
}

int Node::getGrau()
{
    return this->adjacenciaList.size();
}
