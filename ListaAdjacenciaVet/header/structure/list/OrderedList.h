#ifndef ORDEREDLIST_H_INCLUDED
#define ORDEREDLIST_H_INCLUDED

#include "AbstractNodeList.h"

// Tipos de inserção e remoção da lista
enum OperationType
{
    ListOrdered, // Inserção ordenada de forma crescente pelo valor do nó
    ListStart, // Inserção ou remoção da primeira posição
    ListEnd, // Inserção ou remoção da última posição
    ListUnordered // Inserções e remoções por padrão no início da lista
};

/**
*   Lista duplamente encadeada com a possibilidade de inserções ordenadas
**/
template <class G> class OrderedList
{
    private:
        AbstractNodeList<G> *startNode; // Nó inicial da lista
        AbstractNodeList<G> *endNode; // Nó final da lista
        AbstractNodeList<G> *it; // Nó atual da iteração

        bool cleanUp;
        int currId; // Ids automáticos
        int length; // Tamanho da lista

        void searchById(int nodeId); // Auxilia na remoção de um nó colocando o iterador na posição correta
        void searchByValue(float nodeValue); // Auxilia na inserção ordenada colocando o iterador na posição correta
    public:
        OrderedList();
        OrderedList(bool cleanUp);
        ~OrderedList();

        void insert(float nodeValue, OperationType type);
        void insert(G *info, OperationType type);
        void insert(float nodeValue, G *info, OperationType type);
        void insert(int nodeId, float nodeValue, G *info, OperationType type);

        void remove(int nodeId);
        void remove(OperationType type);
        void remove(int nodeId, OperationType type);

        bool search(int nodeId);
        void print();

        void start();
        void end();
        void previous();
        void next();
        bool isEnd();
        bool isEmpty();
        int getLength();

        int getStartId(); // Retorna o id do nó inicial
        int getStartValue(); // Retorna o valor do nó inicial
        G* getStartInfo(); // Retorna o objeto guardado pelo nó inicial

        int getCurrentId(); // Retorna o id da posição atual do iterador
        float getCurrentValue(); // Retorna o valor da posição atual do iterador
        G* getCurrentInfo(); // Retorna o objeto guardado pela posição atual do iterador

        float getNodeValue(int nodeId); // Busca pelo id do nó e retorna seu valor
        G* getNodeInfo(int nodeId); // Busca pelo id do nó e retorna seu objeto guardado

        G* get(int position); // Retorna o objeto guardado na posição
};

#endif // ORDEREDLIST_H_INCLUDED
