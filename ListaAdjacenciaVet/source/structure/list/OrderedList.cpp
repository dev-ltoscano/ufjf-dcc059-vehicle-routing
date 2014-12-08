#include "../../../header/structure/list/OrderedList.h"

template <class G> OrderedList<G>::OrderedList()
{
    this->startNode = NULL;
    this->endNode = NULL;
    this->it = NULL;

    this->currId = 0;
    this->length = 0;
}

template <class G> OrderedList<G>::~OrderedList()
{
    this->clear();
}

template <class G> void OrderedList<G>::clear()
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

        this->startNode = NULL;
        this->endNode = NULL;
        this->it = NULL;

        this->currId = 0;
        this->length = 0;
    }
}

template <class G> void OrderedList<G>::insert(float nodeValue, InsertType type)
{
    this->insert(this->currId, nodeValue, NULL, type);
}

template <class G> void OrderedList<G>::insert(G *info, InsertType type)
{
    this->insert(this->currId, this->currId, info, type);
}

template <class G> void OrderedList<G>::insert(float nodeValue, G *info, InsertType type)
{
    this->insert(this->currId, nodeValue, info, type);
}

template <class G> void OrderedList<G>::insert(int nodeId, float nodeValue, G *info, InsertType type)
{
    AbstractNodeList<G> *node = new AbstractNodeList<G>(nodeId, nodeValue, info);

    if(length == 0) // A lista est� vazia
    {
        node->setPrevious(NULL);
        node->setNext(NULL);

        this->startNode = node;
        this->endNode = node;

        this->currId++;
        this->length++;
    }
    else
    {
        if(type == InsertOrdered)
        {
            this->searchByValue(node->getNodeValue()); // Coloca o ponteiro it em um n� maior que o novo n�
        }
        else if((type == InsertStart) || (type == InsertNone))
        {
            this->start(); // Coloca o ponteiro it no in�cio da lista
        }
        else if(type == InsertEnd)
        {
            this->end();
        }

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
        else // A adjac�ncia tem peso intermedi�rio na lista
        {
            node->setPrevious(it->getPrevious()); // O anterior do novo n� � o anterior do n� da posi��o atual
            node->setNext(it); // O pr�ximo do novo n� � a posi��o atual

            this->it->getPrevious()->setNext(node); // O pr�ximo do anterior da posi��o atual � o novo n�
            this->it->setPrevious(node); // O anterior do n� da posi��o atual � o novo n�
        }

        this->currId++;
        this->length++;
    }
}

template <class G> void OrderedList<G>::searchById(int nodeId)
{
    this->start();

    while((it != NULL) && (it->getNodeId() != nodeId))
    {
        this->next(); // Caminha na lista enquanto n�o chegar ao fim ou n�o encontrar o n�
    }
}

template <class G> void OrderedList<G>::searchByValue(float value)
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
    this->remove(nodeId, InsertNone);
}

template <class G> void OrderedList<G>::remove(InsertType type)
{
    this->remove(-1, type);
}

template <class G> void OrderedList<G>::remove(int nodeId, InsertType type)
{
    if(length == 1)
    {
        delete this->startNode;

        this->startNode = NULL;
        this->endNode = NULL;

        this->length--;
    }
    else if(length > 1) // A lista n�o est� vazia
    {
        if(type == InsertNone)
        {
            this->searchById(nodeId); // Coloca it na posi��o do n� a ser removido
        }
        else if(type == InsertStart)
        {
            this->start();
        }
        else if(type == InsertEnd)
        {
            this->end();
        }

        if(it == endNode) // A adjac�ncia � a �ltima da lista
        {
            AbstractNodeList<G> *aux = this->endNode;

            aux->getPrevious()->setNext(NULL);
            this->endNode = aux->getPrevious();

            delete aux;
            this->length--;
        }
        else if(it == startNode) // A adjac�ncia � a primeira da lista
        {
            AbstractNodeList<G> *aux = this->startNode;

            aux->getNext()->setPrevious(NULL);
            this->startNode = aux->getNext();

            delete aux;
            this->length--;
        }
        else if(it != NULL) // A adjac�ncia � intermedi�ria na lista
        {
            AbstractNodeList<G> *aux = this->it;

            aux->getPrevious()->setNext(aux->getNext());
            aux->getNext()->setPrevious(aux->getPrevious());

            delete aux;
            this->length--;
        }
        else
        {
            cout << "[ Erro ]: Item n�o existe na lista!" << endl;
        }

        this->start();
    }
    else
    {
        cout << "[ Erro ]: Lista vazia!" << endl;
    }
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

template <class G> bool OrderedList<G>::isEmpty()
{
    return (length == 0);
}

template <class G> int OrderedList<G>::getStartId()
{
    this->start();

    if(it != NULL)
    {
        return this->it->getNodeId();
    }

    return -1;
}

template <class G> int OrderedList<G>::getStartValue()
{
    this->start();

    if(it != NULL)
    {
        return this->it->getNodeValue();
    }

    return -1;
}

template <class G> G* OrderedList<G>::getStartInfo()
{
    this->start();

    if(it != NULL)
    {
        return this->it->getInfo();
    }

    return NULL;
}

template <class G> int OrderedList<G>::getCurrentId()
{
    if(it != NULL)
    {
        return this->it->getNodeId();
    }

    return -1;
}

template <class G> float OrderedList<G>::getCurrentValue()
{
    if(it != NULL)
    {
        return this->it->getNodeValue();
    }

    return -1;
}

template <class G> float OrderedList<G>::getNodeValue(int nodeId)
{
    this->searchById(nodeId);

    if(it != NULL)
    {
        return this->it->getNodeValue();
    }

    return -1;
}

template <class G> G* OrderedList<G>::getCurrentInfo()
{
    if(it != NULL)
    {
        return this->it->getInfo();
    }

    return NULL;
}

template <class G> G* OrderedList<G>::getNodeInfo(int nodeId)
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
template class OrderedList<float>;
template class OrderedList<Adjacencia>;
template class OrderedList<InsertCalculation>;
