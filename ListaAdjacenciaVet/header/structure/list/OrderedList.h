#ifndef ORDEREDLIST_H_INCLUDED
#define ORDEREDLIST_H_INCLUDED

#include "AbstractNodeList.h"

// Tipos de inser��o e remo��o da lista
enum OperationType
{
    ListOrdered, // Inser��o ordenada de forma crescente pelo valor do n�
    ListStart, // Inser��o ou remo��o da primeira posi��o
    ListEnd, // Inser��o ou remo��o da �ltima posi��o
    ListUnordered // Inser��es e remo��es por padr�o no in�cio da lista
};

/**
*   Lista duplamente encadeada com a possibilidade de inser��es ordenadas
**/
template <class G> class OrderedList
{
    private:
        shared_ptr<AbstractNodeList<G>> startNode; // N� inicial da lista
        shared_ptr<AbstractNodeList<G>> endNode; // N� final da lista
        shared_ptr<AbstractNodeList<G>> it; // N� atual da itera��o

        int currId; // Ids autom�ticos
        int length; // Tamanho da lista

        void searchById(int nodeId); // Auxilia na remo��o de um n� colocando o iterador na posi��o correta
        void searchByValue(float nodeValue); // Auxilia na inser��o ordenada colocando o iterador na posi��o correta
    public:
        OrderedList();

        void insert(float nodeValue, OperationType type);
        void insert(shared_ptr<G> info, OperationType type);
        void insert(float nodeValue, shared_ptr<G> info, OperationType type);
        void insert(int nodeId, float nodeValue, shared_ptr<G> info, OperationType type);

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

        int getStartId(); // Retorna o id do n� inicial
        int getStartValue(); // Retorna o valor do n� inicial
        shared_ptr<G> getStartInfo(); // Retorna o objeto guardado pelo n� inicial

        int getCurrentId(); // Retorna o id da posi��o atual do iterador
        float getCurrentValue(); // Retorna o valor da posi��o atual do iterador
        shared_ptr<G> getCurrentInfo(); // Retorna o objeto guardado pela posi��o atual do iterador

        float getNodeValue(int nodeId); // Busca pelo id do n� e retorna seu valor
        shared_ptr<G> getNodeInfo(int nodeId); // Busca pelo id do n� e retorna seu objeto guardado

        shared_ptr<G> get(int position); // Retorna o objeto guardado na posi��o
};

#endif // ORDEREDLIST_H_INCLUDED
