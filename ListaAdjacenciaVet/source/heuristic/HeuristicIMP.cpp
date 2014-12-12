#include "../../header/heuristic/HeuristicIMP.h"

HeuristicIMP::HeuristicIMP(HeuristicType heuristic, float alfa)
{
//    this->grafo = grafo;
    this->heuristic = heuristic;
    this->alfa = alfa;
}

void HeuristicIMP::setAlfa(float alfa)
{
    this->alfa = alfa;
}

int HeuristicIMP::run(CVRPInstance *instance)
{
    if(instance == NULL)
    {
        cout << "[ Erro ]: A inst�ncia � nula!" << endl;
        return -1;
    }

    return this->run(instance->createInstance(), instance->getVerticeBase(), instance->getVehicleCapacity());
}

int HeuristicIMP::run(ListaAdjacenciaVet *grafo, int nodeBase, float vehicleCapacity)
{
    int dPath = 0; // Custo da solu��o atual
    int rotaCount = 0; // Quantidade de rotas encontradas para a solu��o atual

    bool *visited = new bool[grafo->getVerticeCount()]; // Vetor para indicar n�s que j� foram visitados
    visited[nodeBase] = true; // Marca o n� da base como visitado
    int visitedLength = 1; // Indica a quantidade de n�s que foram visitados (A base j� foi visitada)

    Vehicle *truck = new Vehicle(1, vehicleCapacity); // Cria um novo ve�culo para resolver o problema
    OrderedList<Adjacencia> *adjBase = grafo->getAdjacenciaList(nodeBase); // Pega todas as adjac�ncias da base

    // Enquanto a quantidade de n�s visitados for menor que a quantidade de n�s do grafo
    while(visitedLength < grafo->getVerticeCount())
    {
        OrderedList<Adjacencia> *caminho = new OrderedList<Adjacencia>(); // Caminho feito em uma rota
        OrderedList<InsertCalculation> *calculo = new OrderedList<InsertCalculation>(); // ??

        bool found = false; // ??

        //ADICIONA AS DUAS PRIMEIRAS ARESTAS A SOLU��O
        adjBase->start();
        while(adjBase->getCurrentId() != -1 && !found)
        {
            int idAdj = adjBase->getCurrentInfo()->getIdVertice2(); // Pega o id do n� adjacente � base

            if(!visited[idAdj]) // Se o n� ainda n�o foi visitado
            {
                /**
                *
                * Eu deveria verificar aqui se o meu caminh�o consegue atender esse v�rtice?
                *
                **/

                truck->removeCapacity(grafo->getVerticeWeight(idAdj)); // Retira da capacidade do ve�culo a demanda do n� (Problema de entrega)

                // Adjac�ncias de ida (base, n�) e volta (n�, base), formando um ciclo
                Adjacencia* ida =  grafo->getAdjacencia(idAdj, nodeBase);
                Adjacencia* volta = grafo->getAdjacencia(nodeBase, idAdj);

                // Insere as adjac�ncias de ida e volta na solu��o
                caminho->insert(ida->getWeight(), ida, ListStart);
                caminho->insert(volta->getWeight(), volta, ListStart);

                // Mais um n� foi visitado

                /**
                *
                * N�o seria melhor usar o id l� de cima?
                *
                **/

                visited[adjBase->getCurrentId()] = true;
                visitedLength++;

//                    cout << "PRIMEIRO NO: " << adjBase->getCurrentId() << endl;
//                    for(int i = 0; i < grafo->getVerticeCount(); i ++)
//                        cout << i << ": visited = " << visited[i] << endl;

                found = true;
            }

            adjBase->next();
        }

        //TRABALHA EM CIMA DA SOLU��O ADICIONANDO V�RTICES ENQUANTO O VE�CULO POSSUI CAPACIDADE
        while(truck->getCapacity() > 0)
        {
            //AS DUAS U�LTIMAS ARESTAS ADICIONADAS (a1, a2)
            caminho->start();
            Adjacencia* a2 = caminho->getCurrentInfo();

            caminho->next();
            Adjacencia* a1 = caminho->getCurrentInfo();

            // CUSTO DA INSER��O DE NOVAS ARESTAS
            InsertCalculation* solution;

            // NOVAS ARESTAS DA SOLU��O (s1, s2)
            Adjacencia* s1;
            Adjacencia* s2;

            //ARESTA A SER REMOVIDA DA SOLU��O
            Adjacencia* removed;

            OrderedList<Adjacencia>* adj1 = grafo->getAdjacenciaList(a1->getIdVertice1());
            OrderedList<Adjacencia>* adj2 = grafo->getAdjacenciaList(a2->getIdVertice1());

//                printf("a1: %d -> %d\n",a1->getIdVertice1(),a1->getIdVertice2());

            //C�LCULO DE a1
            adj1->start();
            while(adj1->getCurrentId() != -1)
            {
                int idAdj = adj1->getCurrentInfo()->getIdVertice2();

                // Verifica se o n� ainda n�o foi visitado, se o ve�culo tem capacidade e se existe adjac�ncia entre um v�rtice da solu��o e o novo v�rtice
                if(!visited[idAdj] && ((truck->getCapacity() - grafo->getVerticeWeight(idAdj)) > 0) && grafo->existsAdjacencia(idAdj, a1->getIdVertice2()))
                {
                    InsertCalculation* ic = new InsertCalculation();

                    ic->nodeId = idAdj; // Id do v�rtice
                    ic->idVertice1 = a1->getIdVertice1(); // Id do v�rtice 1 da adjac�ncia
                    ic->idVertice2 = a1->getIdVertice2(); // Id do v�rtice 2 da adjac�ncia

                    // Diferen�a que a inser��o ir� produzir na solu��o
                    ic->difPath = (adj1->getCurrentInfo()->getWeight() + grafo->getAdjacencia(idAdj, a1->getIdVertice2())->getWeight()) - a1->getWeight();

                    // Insere o c�lculo da diferen�a da inser��o na lista de c�lculos
                    calculo->insert(ic->difPath, ic, ListUnordered);
                }

                adj1->next();
            }


//                printf("a2: %d -> %d\n",a2->getIdVertice1(),a2->getIdVertice2());

            //C�LCULO DE a2
            adj2->start();
            while(adj2->getCurrentId() != -1)
            {
                int idAdj = adj2->getCurrentInfo()->getIdVertice2();

                // Verifica se o n� ainda n�o foi visitado, se o ve�culo tem capacidade e se existe adjac�ncia entre um v�rtice da solu��o e o novo v�rtice
                if(!visited[idAdj] && ((truck->getCapacity() - grafo->getVerticeWeight(idAdj)) > 0) && grafo->existsAdjacencia(idAdj, a2->getIdVertice2()))
                {
                    InsertCalculation* ic = new InsertCalculation();

                    ic->nodeId = idAdj; // Id do v�rtice
                    ic->idVertice1 = a2->getIdVertice1(); // Id do v�rtice 1 da adjac�ncia
                    ic->idVertice2 = a2->getIdVertice2(); // Id do v�rtice 2 da adjac�ncia

                    // Diferen�a que a inser��o ir� produzir na solu��o
                    ic->difPath = (adj2->getCurrentInfo()->getWeight() + grafo->getAdjacencia(idAdj, a2->getIdVertice2())->getWeight()) - a2->getWeight();

                    // Insere o c�lculo da diferen�a da inser��o na lista de c�lculos
                    calculo->insert(ic->difPath, ic, ListUnordered);
                }

                adj2->next();
            }

//                cout << " -- CALCULOS -- " << endl;
//                calculo->start();
//
//                while(calculo->getCurrentId() != -1)
//                {
//                    InsertCalculation* ic = calculo->getNodeInfo(calculo->getCurrentId());
////                    cout << ic->idVertice1 << " -> " << ic->idVertice2 << ": node= " << ic->nodeId << " deltaPath= " << ic->difPath << " visited[i] " << visited[ic->nodeId] << endl;
//                    calculo->next();
//
//                }
//                cout << endl << endl;


            //SE A LISTA DE C�LCULOS ESTIVER VAZIA N�O H� MAIS N�S QUE SEJA POSS�VEL INSERIR NO CAMINHO
            if(calculo->isEmpty())
            {
                caminho->start();
//                cout << " --- CAMINHO FINAL --- " << endl;

                while(caminho->getCurrentId() != -1)
                {
                    dPath += caminho->getCurrentInfo()->getWeight();
//                    cout << caminho->getCurrentInfo()->getIdVertice1() << " -> " << caminho->getCurrentInfo()->getIdVertice2() << endl;
                    caminho->next();
                }

//                cout << endl << endl;
                rotaCount++;
                break;
            }


            // Insere uma solu��o de forma randomizada
//                cout << "Length: " << calculo->getLength() << endl;
            int r = rand();
//                cout << "Rand: " << r << endl;
            int pos = (int)(alfa * calculo->getLength());
//                cout << "Position: " << pos << endl;
            int idSolution = (pos != 0) ? r % pos : 0;
            solution = calculo->get(idSolution);

//                //INSERE A MELHOR SOLU��O (GULOSA)
//                calculo->start();
//                solution = calculo->getCurrentInfo();
//                cout << "ADD NO: " << solution->nodeId << endl;

            removed = grafo->getAdjacencia(solution->idVertice1, solution->idVertice2); // Adjac�ncia que ser� removida da solu��o
//                cout << "REMOVE PATH: " << removed->getIdVertice1() << " -> " << removed->getIdVertice2() << endl;

            // Novas arestas que substituir�o a que ser� removida
            s1 = grafo->getAdjacencia(removed->getIdVertice1(), solution->nodeId);
            s2 = grafo->getAdjacencia(solution->nodeId, removed->getIdVertice2());

            // Insere as novas arestas na solu��o
            caminho->insert(s1->getWeight(), s1, ListStart);
            caminho->insert(s2->getWeight(), s2, ListStart);

            truck->removeCapacity(grafo->getVerticeWeight(solution->nodeId)); // ??

            visited[solution->nodeId] = true;
            visitedLength++;

//                for(int i = 0; i < grafo->getVerticeCount(); i ++)
//                    cout << i << ": visited = " << visited[i] << endl;


            //ATUALIZA OS C�LCULOS
            calculo->start();
//                cout << "CALC TAM -> " << calculo->getLength() << endl;
            while(!calculo->isEnd() && !calculo->isEmpty())
            {
                InsertCalculation* ic = calculo->getCurrentInfo();

//                    cout << "REMOVED (" << removed->getIdVertice1() << " -> " << removed->getIdVertice2();
//                    cout << ") == (" << ic->idVertice1 << " -> " << ic->idVertice2 << ")" << endl;

                if(removed->equals(ic->idVertice1, ic->idVertice2)|| (truck->getCapacity() - grafo->getVerticeWeight(ic->nodeId) < 0) || visited[ic->nodeId])
                {
//                        cout << "TIREI " << ic->idVertice1 << " -> " << ic->idVertice2 << ": node= " << ic->nodeId << " deltaPath= " << ic->difPath << " visited[i] " << visited[ic->nodeId] << endl;

                    calculo->remove(calculo->getCurrentId());
                }
                else
                {
                    calculo->next();
                }
            }

            //REMOVE DO CAMINHO A ARESTA QUE FOI SUBSTITU�DA
            caminho->start();
            while(!caminho->isEnd() && !caminho->isEmpty())
            {
//                    cout << " --- REMOVE ARESTA --- " << endl;
//                    cout << caminho->getCurrentInfo()->getIdVertice1() << " - > " << caminho->getCurrentInfo()->getIdVertice2();
//                    cout << " == " <<removed->getIdVertice1() << " -> " << removed->getIdVertice2() << endl;

                if(removed->equals(caminho->getCurrentInfo()))
                {
                    caminho->remove(caminho->getCurrentId());
                    break;
                }
                else
                {
                    caminho->next();
                }
            }
        }

//        cout << "dPath: " << dPath << " -- minPath: " << minDPath << endl;

//            if(dPath < minDPath)
//            {
//                minDPath = dPath;
//            }
//
//            if(rotaCount < minRotaCount)
//            {
//                minRotaCount = rotaCount;
//            }

            // Como uma rota foi fechada, retorna o caminh�o para capacidade m�xima
        truck->resetCapacity();
    }

    cout << "Total de rotas: " << rotaCount << endl;
//    cout << "Custo da solu��o: " << dPath << endl;
    return dPath;
}
