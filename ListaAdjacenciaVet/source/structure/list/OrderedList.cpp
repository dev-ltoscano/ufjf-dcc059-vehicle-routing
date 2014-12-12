#include "../../../header/structure/list/OrderedList.h"

template <class G> OrderedList<G>::OrderedList()
{
    this->startNode = NULL;
    this->endNode = NULL;
    this->it = NULL;

    this->delayedRemoveList = NULL;

    this->currId = 0;
    this->length = 0;
}

template <class G> OrderedList<G>::~OrderedList()
{
    this->clear();
}

template <class G> void OrderedList<G>::clear()
{
    // Destruindo objetos atuais
    AbstractNodeList<G> *aux = startNode;

    while(aux != NULL)
    {
        startNode = startNode->getNext();
        delete aux;
        aux = startNode;
    }

    // Destruindo objetos atrasados
    aux = delayedRemoveList;

    while(aux != NULL)
    {
        delayedRemoveList = delayedRemoveList->getNext();
        delete aux;
        aux = delayedRemoveList;
    }

    this->startNode = NULL;
    this->endNode = NULL;
    this->it = NULL;

    this->delayedRemoveList = NULL;

    this->currId = 0;
    this->length = 0;
}

template <class G> void OrderedList<G>::searchById(int nodeId)
{
    this->start();

    // Caminha na lista enquanto não chegar ao fim e não encontrar o nó
    while((it != NULL) && (it->getNodeId() != nodeId))
    {
        this->next();
    }
}

template <class G> void OrderedList<G>::searchByValue(float value)
{
    this->start();

    // Caminha na lista enquanto não chegar ao último valor da lista e não encontrar um valor maior que o valor procurado
    while((it != NULL) && (it->getNodeValue() < value))
    {
        if(it->getNext() == NULL)
            break;

        this->next();
    }
}

template <class G> void OrderedList<G>::insert(float nodeValue, OperationType type)
{
    this->insert(this->currId, nodeValue, NULL, type);
}

template <class G> void OrderedList<G>::insert(G *info, OperationType type)
{
    this->insert(this->currId, this->currId, info, type);
}

template <class G> void OrderedList<G>::insert(float nodeValue, G *info, OperationType type)
{
    this->insert(this->currId, nodeValue, info, type);
}

template <class G> void OrderedList<G>::insert(int nodeId, float nodeValue, G *info, OperationType type)
{
    AbstractNodeList<G> *node = new AbstractNodeList<G>(nodeId, nodeValue, info);

    if(length == 0) // A lista está vazia
    {
        node->setPrevious(NULL); // Não há nó anterior
        node->setNext(NULL); // Não há nó sucessor

        this->startNode = node; // É o primeiro nó da lista
        this->endNode = node; // Também é o último

        this->currId++;
        this->length++;
    }
    else
    {
        if(type == ListOrdered) // Inserção ordenada
        {
            this->searchByValue(node->getNodeValue());
        }
        else if((type == ListStart) || (type == ListUnordered)) // Inserção no início da lista
        {
            this->start();
        }
        else if(type == ListEnd) // Inserção no final da lista
        {
            this->end();
        }

        if(it == endNode) // O novo nó tem valor maior que todos os outros
        {
            node->setPrevious(it); // O anterior ao nó atual é o fim da lista
            node->setNext(NULL); // Não existe nó após o novo nó

            this->endNode->setNext(node); // O próximo nó do atual fim da lista passa a ser o novo nó
            this->endNode = node; // O final da lista é o novo nó
        }
        else if(it == startNode) // O novo nó tem valor menor que todos os outros
        {
            node->setPrevious(NULL); // Não há nó anterior ao novo nó
            node->setNext(it); // O próximo nó é o nó de início da lista

            this->startNode->setPrevious(node); // O anterior ao atual nó da lista é o novo nó
            this->startNode = node; // O novo nó é o início da lista
        }
        else // O novo nó tem valor intermediário na lista
        {
            node->setPrevious(it->getPrevious()); // O anterior do novo nó é o anterior do nó da posição atual
            node->setNext(it); // O próximo do novo nó é a posição atual

            this->it->getPrevious()->setNext(node); // O próximo do anterior da posição atual é o novo nó
            this->it->setPrevious(node); // O anterior do nó da posição atual é o novo nó
        }

        this->currId++;
        this->length++;
    }
}

template <class G> void OrderedList<G>::remove(int nodeId)
{
    this->remove(nodeId, ListUnordered);
}

template <class G> void OrderedList<G>::remove(OperationType type)
{
    this->remove(-1, type);
}

template <class G> void OrderedList<G>::remove(int nodeId, OperationType type)
{
    if(length == 1)
    {
        this->startNode = NULL;
        this->endNode = NULL;

        this->length--;

        this->start();
    }
    else if(length > 1)
    {
        // Coloca it na posição do nó a ser removido
        if((type == ListOrdered) || (type == ListUnordered))
        {
            this->searchById(nodeId);
        }
        else if(type == ListStart)
        {
            this->start();
        }
        else if(type == ListEnd)
        {
            this->end();
        }

        if(it == endNode) // A adjacência é a última da lista
        {
            AbstractNodeList<G> *aux = this->endNode;

            aux->getPrevious()->setNext(NULL);
            this->endNode = aux->getPrevious();

            aux->setNext(delayedRemoveList);
            this->delayedRemoveList = aux;

            this->length--;
        }
        else if(it == startNode) // A adjacência é a primeira da lista
        {
            AbstractNodeList<G> *aux = this->startNode;

            aux->getNext()->setPrevious(NULL);
            this->startNode = aux->getNext();

            aux->setNext(delayedRemoveList);
            this->delayedRemoveList = aux;

            this->length--;
        }
        else if(it != NULL) // A adjacência é intermediária na lista
        {
            AbstractNodeList<G> *aux = this->it;
            it = it->getNext();

            aux->getPrevious()->setNext(aux->getNext());
            aux->getNext()->setPrevious(aux->getPrevious());

            aux->setNext(delayedRemoveList);
            this->delayedRemoveList = aux;

            this->length--;
        }
        else
        {
            cout << "[ Erro ]: Item não existe na lista!" << endl;
        }

        this->start();
    }
    else
    {
        cout << "[ Erro ]: Lista vazia!" << endl;
    }
}

template <class G> bool OrderedList<G>::search(int nodeId)
{
    this->searchById(nodeId);
    return (it != NULL);
}

template <class G> void OrderedList<G>::print()
{
    cout << "# OrderedList: " << this->length << " item(s)" << endl << endl;

    this->start();

    while(!isEnd())
    {
        cout << "ID [" << this->it->getNodeId() << "] | Value [" << this->it->getNodeValue() << "]" << endl;
        this->next();
    }

    cout << endl << "# End" << endl << endl;
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
    return (this->length == 0);
}

template <class G> int OrderedList<G>::getLength()
{
    return this->length;
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

template <class G> G* OrderedList<G>::getCurrentInfo()
{
    if(it != NULL)
    {
        return this->it->getInfo();
    }

    return NULL;
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

template <class G> G* OrderedList<G>::get(int position)
{
    int count = 0;
    this->start();

    // Caminha pela lista até a posição desejada
    while(!isEnd() && (count != position))
    {
        count++;
        this->next();
    }

    if(it != NULL)
    {
        return it->getInfo();
    }

    return NULL;
}

template class OrderedList<int>;
template class OrderedList<float>;
template class OrderedList<Adjacencia>;
template class OrderedList<InsertCalculation>;
