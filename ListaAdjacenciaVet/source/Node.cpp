#include "../header/Node.h"

Node::Node() { }

Node::~Node()
{
    for (list<Adjacencia*>::iterator it = adjacenciaList.begin(); it != adjacenciaList.end(); it++)
    {
        delete (*it);
    }
}

Adjacencia* Node::getAdjacencia(int idNodeAdj)
{
    for (list<Adjacencia*>::iterator it = adjacenciaList.begin(); it != adjacenciaList.end(); it++)
    {
        if((*it)->getIdNode2() == idNodeAdj)
            return (*it);
    }

    return NULL;
}

float Node::getWeight()
{
    return this->weight;
}

void Node::setWeight(float weight)
{
    this->weight = weight;
}

void Node::addAdjacencia(int idNode1, int idNode2, float weight)
{
    Adjacencia *nodeAdj = this->getAdjacencia(idNode2);

    if(nodeAdj == NULL)
    {
        this->adjacenciaList.push_front(new Adjacencia(idNode1, idNode2, weight));
    }
    else
    {
        cout << "[ Erro ]: Adjacência já existe!" << endl;
    }
}

void Node::removeAdjacencia(int idNode2)
{
    Adjacencia *nodeAdj = this->getAdjacencia(idNode2);

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
