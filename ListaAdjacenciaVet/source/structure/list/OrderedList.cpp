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

    if(length == 0) // A lista est� vazia
    {
        this->startNode = node;
        this->endNode = node;
    }
    else
    {
        if(isOrdered)
        {
            this->searchByWeight(adj->getWeight()); // Coloca o ponteiro it em um n� maior que o novo n�
        }
        else
        {
            this->start(); // Coloca o ponteiro it no in�cio da lista
        }

        if(it->getAdjacencia()->getIdVertice2() != adj->getIdVertice2()) // Verifica se a adjac�ncia j� existe na lista
        {
            if(it == endNode) // A adjac�ncia tem peso maior que todas as outras da lista
            {
                node->setPrevious(it); // O anterior ao n� atual � o fim da lista
                node->setNext(NULL); // N�o existe n� ap�s o novo n�

                this->endNode->setNext(node); // O pr�ximo n� do atual fim da lista passa a ser o novo n�
                this->endNode = node; // O final da lista � o novo n�
            }
            else if(it == startNode) // A adjac�ncia tem peso menor que todas as outras da lista
            {
                node->setPrevious(NULL); // N�o h� n� anterior ao novo n�
                node->setNext(it); // O pr�ximo n� � o n� de in�cio da lista

                this->startNode->setPrevious(node); // O anterior ao atual n� da lista � o novo n�
                this->startNode = node; // O novo n� � o in�cio da lista
            }
            else if(it != NULL) // A adjac�ncia tem peso intermedi�rio na lista
            {
                node->setPrevious(it->getPrevious()); // O anterior do novo n� � o anterior do n� da posi��o atual
                node->setNext(it); // O pr�ximo do novo n� � a posi��o atual

                this->it->getPrevious()->setNext(node); // O pr�ximo do anterior da posi��o atual � o novo n�
                this->it->setPrevious(node); // O anterior do n� da posi��o atual � o novo n�
            }
        }
        else
        {
            cout << "[ Erro ]: Adjac�ncia j� existe!" << endl;
        }
    }

    this->length++;
}

void OrderedList::searchById(int idVertice2)
{
    this->start();

    while((it != NULL) && (it->getAdjacencia()->getIdVertice2() != idVertice2))
    {
        this->next(); // Caminha na lista enquanto n�o chegar ao fim ou n�o encontrar o n�
    }
}

void OrderedList::searchByWeight(int weight)
{
    this->start();

    while((it != NULL) && (it->getAdjacencia()->getWeight() < weight))
    {
        if(it->getNext() != NULL)
            this->next(); // Caminha na lista enquanto n�o chegar ao fim ou encontrar um n� maior que o procurado
        else
            break;
    }
}

void OrderedList::remove(int idVertice2)
{
    if(length != 0) // A lista n�o est� vazia
    {
        this->searchById(idVertice2); // Coloca it na posi��o do n� a ser removido

        if(it == endNode) // A adjac�ncia � a �ltima da lista
        {
            NodeList *aux = this->endNode;

            aux->getPrevious()->setNext(NULL);
            this->endNode = aux->getPrevious();

            delete aux;
        }
        else if(it == startNode) // A adjac�ncia � a primeira da lista
        {
            NodeList *aux = this->startNode;

            aux->getNext()->setPrevious(NULL);
            this->startNode = aux->getNext();

            delete aux;
        }
        else if(it != NULL) // A adjac�ncia � intermedi�ria na lista
        {
            NodeList *aux = this->it;

            aux->getPrevious()->setNext(aux->getNext());
            aux->getNext()->setPrevious(aux->getPrevious());

            delete aux;
        }
        else
        {
            cout << "[ Erro ]: Adjac�ncia n�o existe!" << endl;
        }
    }
    else
    {
        cout << "[ Erro ]: Lista de adjac�ncia vazia!" << endl;
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
