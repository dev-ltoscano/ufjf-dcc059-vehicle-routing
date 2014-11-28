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

    if(length == 0) // A lista est� vazia
    {
        this->startNode = node;
        this->endNode = node;
    }
    else
    {
        if(isOrdered)
        {
            this->searchByValue(node->getNodeValue()); // Coloca o ponteiro it em um n� maior que o novo n�
        }
        else
        {
            this->start(); // Coloca o ponteiro it no in�cio da lista
        }

        if(it->getNodeId() != node->getNodeId()) // Verifica se a adjac�ncia j� existe na lista
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

template <class G> void OrderedList<G>::searchById(int nodeId)
{
    this->start();

    while((it != NULL) && (it->getNodeId() != nodeId))
    {
        this->next(); // Caminha na lista enquanto n�o chegar ao fim ou n�o encontrar o n�
    }
}

template <class G> void OrderedList<G>::searchByValue(int value)
{
    this->start();

    while((it != NULL) && (it->getNodeValue() < value))
    {
        if(it->getNext() == NULL)
            break;

        this->next(); // Caminha na lista enquanto n�o chegar ao fim ou encontrar um n� maior que o procurado
    }
}

template <class G> void OrderedList<G>::remove(int nodeId)
{
    if(length != 0) // A lista n�o est� vazia
    {
        this->searchById(nodeId); // Coloca it na posi��o do n� a ser removido

        if(it == endNode) // A adjac�ncia � a �ltima da lista
        {
            AbstractNodeList<G> *aux = this->endNode;

            aux->getPrevious()->setNext(NULL);
            this->endNode = aux->getPrevious();

            delete aux;
        }
        else if(it == startNode) // A adjac�ncia � a primeira da lista
        {
            AbstractNodeList<G> *aux = this->startNode;

            aux->getNext()->setPrevious(NULL);
            this->startNode = aux->getNext();

            delete aux;
        }
        else if(it != NULL) // A adjac�ncia � intermedi�ria na lista
        {
            AbstractNodeList<G> *aux = this->it;

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
