#include "../../../header/structure/list/OrderedList.h"

OrderedList::OrderedList()
{
    this->startNode = NULL;
    this->endNode = NULL;
    this->it = NULL;

    this->isOrdered = true;
    this->length = 0;
}

OrderedList::~OrderedList()
{
    if(length != 0)
    {
        NodeList *aux = startNode;

        while(aux != NULL)
        {
            startNode = startNode->getNext();
            delete aux;
            aux = startNode;
        }
    }
}

void OrderedList::setOrder(bool isOrdered)
{
    this->isOrdered = isOrdered;
}

void OrderedList::insert(Adjacencia *adj)
{
    NodeList *node = new NodeList(adj);

    if(length == 0) // A lista está vazia
    {
        this->startNode = node;
        this->endNode = node;
    }
    else
    {
        if(isOrdered)
        {
            this->searchByWeight(adj->getWeight()); // Coloca o ponteiro it em um nó maior que o novo nó
        }
        else
        {
            this->start(); // Coloca o ponteiro it no início da lista
        }

        if(it->getAdjacencia()->getIdVertice2() != adj->getIdVertice2()) // Verifica se a adjacência já existe na lista
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

void OrderedList::searchById(int idVertice2)
{
    this->start();

    while((it != NULL) && (it->getAdjacencia()->getIdVertice2() != idVertice2))
    {
        this->next(); // Caminha na lista enquanto não chegar ao fim ou não encontrar o nó
    }
}

void OrderedList::searchByWeight(int weight)
{
    this->start();

    while((it != NULL) && (it->getAdjacencia()->getWeight() < weight))
    {
        if(it->getNext() != NULL)
            this->next(); // Caminha na lista enquanto não chegar ao fim ou encontrar um nó maior que o procurado
        else
            break;
    }
}

void OrderedList::remove(int idVertice2)
{
    if(length != 0) // A lista não está vazia
    {
        this->searchById(idVertice2); // Coloca it na posição do nó a ser removido

        if(it == endNode) // A adjacência é a última da lista
        {
            NodeList *aux = this->endNode;

            aux->getPrevious()->setNext(NULL);
            this->endNode = aux->getPrevious();

            delete aux;
        }
        else if(it == startNode) // A adjacência é a primeira da lista
        {
            NodeList *aux = this->startNode;

            aux->getNext()->setPrevious(NULL);
            this->startNode = aux->getNext();

            delete aux;
        }
        else if(it != NULL) // A adjacência é intermediária na lista
        {
            NodeList *aux = this->it;

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

void OrderedList::start()
{
    this->it = this->startNode;
}

void OrderedList::end()
{
    this->it = this->endNode;
}

void OrderedList::previous()
{
    if(it != NULL)
    {
        this->it = this->it->getPrevious();
    }
}

void OrderedList::next()
{
    if(it != NULL)
    {
        this->it = this->it->getNext();
    }
}

bool OrderedList::isEnd()
{
    return (it == NULL);
}

Adjacencia* OrderedList::getAdjacencia()
{
    if(it != NULL)
    {
        return this->it->getAdjacencia();
    }

    return NULL;
}

Adjacencia* OrderedList::getAdjacencia(int idVertice2)
{
    this->start();

    while(!isEnd())
    {
        if(it->getAdjacencia()->getIdVertice2() == idVertice2)
        {
            return this->it->getAdjacencia();
        }

        this->next();
    }

    return NULL;
}

int OrderedList::getLength()
{
    return this->length;
}
