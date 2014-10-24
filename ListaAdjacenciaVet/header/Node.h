#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include <iostream>
#include <list>

#include "NodeInfo.h"
#include "Adjacencia.h"

using namespace std;

class Node
{
    private:
        NodeInfo *nodeInfo;
        list<Adjacencia*> adjacenciaList;

        Adjacencia* getAdjacencia(int idNodeAdj);
    public:
        Node();
        ~Node();

        NodeInfo* getNodeInfo();
        void setNodeInfo(NodeInfo *nodeInfo);

        void addAdjacencia(int idNodeAdj);
        void removeAdjacencia(int idNodeAdj);
        bool existsAdjacencia(int idNodeAdj);
        list<Adjacencia*> getAdjacenciaList();

        int getGrau();
};

#endif // NODE_H_INCLUDED
