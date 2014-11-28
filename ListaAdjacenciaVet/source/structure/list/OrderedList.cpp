#include "../../../header/structure/list/OrderedList.h"

template <class G> OrderedList<G>::OrderedList()
{
    this->startNode = NULL;
    this->endNode = NULL;
    this->it = NULL;

    this->isOrdered = true;
    this->length = 0;
}

template <class G> OrderedList<G>::~OrderedList()
{
    if(length != 0)
    {
        AbstractNodeList<G> *aux = startNode;

        while(aux != NULL)
        {
            startNode = startNode->getNext();
            delete aux;
            aux = startNode;
        }
    }
}

template <class G> void OrderedList<G>::setOrder(bool isOrdered)
{
    this->isOrdered = isOrdered;
}

template <class G> void OrderedList<G>::insert(int nodeId, int nodeValue, G *info)
{
    AbstractNodeList<G> *node = new AbstractNodeList<G>(nodeId, nodeValue, info);

    if(length == 0) // A lista está vazia
    {
        this->startNode = node;
        this->endNode = node;
    }
    else
    {
        if(isOrdered)
        {
            this->searchByValue(node->getNodeValue()); // Coloca o ponteiro it em um nó maior que o novo nó
        }
        else
        {
            this->start(); // Coloca o ponteiro it no início da lista
        }

        if(it->getNodeId() != node->getNodeId()) // Verifica se a adjacência já existe na lista
        {
            if(it == endNode) // A adjacência tem peso maior que todas as outras da lista
            {
                node->setPrevious(it); // O anterior ao nó atual é o fim da lista
                node->setNext(NULL); // Não existe nó após o novo nó

                this->endNode->setNext(node); // O próximo nó do atual fim da lista passa a ser o novo nó
                this->endNode = node; // O final da lista é o novo nó
            }
            else if(it == startNode) // A adjacência tem peso menor que todas as outras da lista
            {
                node->setPrevious(NULL); // Não há nó anterior ao novo nó
                node->setNext(it); // O próximo nó é o nó de início da lista

                this->startNode->setPrevious(node); // O anterior ao atual nó da lista é o novo nó
                this->startNode = node; // O novo nó é o início da lista
            }
            else if(it != NULL) // A adjacência tem peso intermediário na lista
            {
                node->setPrevious(it->getPrevious()); // O anterior do novo nó é o anterior do nó da posição atual
                node->setNext(it); // O próximo do novo nó é a posição atual

                this->it->getPrevious()->setNext(node); // O próximo do anterior da posição atual é o novo nó
                this->it->setPrevious(node); // O anterior do nó da posição atual é o novo nó
            }
        }
        else
        {
            cout << "[ Erro ]: Adjacência já existe!" << endl;
        }
    }

    this->length++;
}

template <class G> void OrderedList<G>::searchById(int nodeId)
{
    this->start();

    while((it != NULL) && (it->getNodeId() != nodeId))
    {
        this->next(); // Caminha na lista enquanto não chegar ao fim ou não encontrar o nó
    }
}

template <class G> void OrderedList<G>::searchByValue(int value)
{
    this->start();

    while((it != NULL) && (it->getNodeValue() < value))
    {
        if(it->getNext() == NULL)
            break;

        this->next(); // Caminha na lista enquanto não chegar ao fim ou encontrar um nó maior que o procurado
    }
}

template <class G> void OrderedList<G>::remove(int nodeId)
{
    if(length != 0) // A lista não está vazia
    {
        this->searchById(nodeId); // Coloca it na posição do nó a ser removido

        if(it == endNode) // A adjacência é a última da lista
        {
            AbstractNodeList<G> *aux = this->endNode;

            aux->getPrevious()->setNext(NULL);
            this->endNode = aux->getPrevious();

            delete aux;
        }
        else if(it == startNode) // A adjacência é a primeira da lista
        {
            AbstractNodeList<G> *aux = this->startNode;

            aux->getNext()->setPrevious(NULL);
            this->startNode = aux->getNext();

            delete aux;
        }
        else if(it != NULL) // A adjacência é intermediária na lista
        {
            AbstractNodeList<G> *aux = this->it;

            aux->getPrevious()->setNext(aux->getNext());
            aux->getNext()->setPrevious(aux->getPrevious());

            delete aux;
        }
        else
        {
            cout << "[ Erro ]: Adjacência não existe!" << endl;
        }
    }
    else
    {
        cout << "[ Erro ]: Lista de adjacência vazia!" << endl;
    }

    this->start();
}

template <class G> void OrderedList<G>::print()
{
    this->start();

    while(!isEnd())
    {
        cout << "ID [" << this->it->getNodeId() << "] | Value [" << this->it->getNodeValue() << "]" << endl;
        this->next();
    }
}

template <class G> void OrderedList<G>::start()
{
    this->it = this->startNode;
}

template <class G> void OrderedList<G>::end()
{
    this->it = this->endNode;
}

template <class G> void OrderedList<G>::previous()
{
    if(it != NULL)
    {
        this->it = this->it->getPrevious();
    }
}

template <class G> void OrderedList<G>::next()
{
    if(it != NULL)
    {
        this->it = this->it->getNext();
    }
}

template <class G> bool OrderedList<G>::isEnd()
{
    return (it == NULL);
}

template <class G> G* OrderedList<G>::getInfo()
{
    if(it != NULL)
    {
        return this->it->getInfo();
    }

    return NULL;
}

template <class G> G* OrderedList<G>::getInfo(int nodeId)
{
    this->start();

    while(!isEnd())
    {
        if(it->getNodeId() == nodeId)
        {
            return this->it->getInfo();
        }

        this->next();
    }

    return NULL;
}

template <class G> int OrderedList<G>::getLength()
{
    return this->length;
}

template class OrderedList<int>;
template class OrderedList<Adjacencia>;
