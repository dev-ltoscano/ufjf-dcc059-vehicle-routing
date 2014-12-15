#include "../../header/heuristic/HeuristicIMP.h"

HeuristicIMP::HeuristicIMP(string filename)
{
    shared_ptr<CVRPInstance> instance = FileHelper::readInstance(filename);

    if(instance != NULL)
    {
        this->nodeBase = instance->getVerticeBase();
        this->vehicleCapacity = instance->getVehicleCapacity();
        this->grafo = instance->getInstance();

        ready = true;
    }
    else
    {
        ready = false;
        cout << "[ Erro ]: A inst�ncia n�o foi carregada corretamente! " << endl;
    }
}

bool HeuristicIMP::isReady()
{
    return this->ready;
}

float HeuristicIMP::runGulosa()
{
    // Se a inst�ncia n�o foi carregada corretamente, retorna
    if(!ready)
    {
        return -1;
    }

    cout << "Gerando solu��o gulosa..." << endl;
    return this->heuristic(0); // Gera uma solu��o gulosa
}

float HeuristicIMP::runRandom(float alfa, int maxIteration)
{
    // Se a inst�ncia n�o foi carregada corretamente, retorna
    if(!ready)
    {
        return -1;
    }

    cout << "Gerando solu��o randomizada [ Alfa = " << alfa << " | maxIteration = " << maxIteration << "]"<< endl;

    float minCost = INFINITE; // Custo m�nimo
    float sum = 0; // Somat�rio dos custos
    float cost = 0; // Custo atual

    cout << "Itera��o: " << endl;

    // Gera at� maxIteration de solu��es
    for(int i = 0; i < maxIteration; i++)
    {
        cost = this->heuristic(alfa);

        // Atualiza custo m�nimo
        if(cost < minCost)
        {
            minCost = cost;
        }

        sum += cost; // Atualiza a soma do custo das solu��es
        cout << i << " ";
    }

    cout << endl << endl << "Custo m�dio (" << alfa << "): " << (sum / maxIteration) << endl;
    return minCost;
}

float HeuristicIMP::runReativa(string outputFile, int alfaUpdate, int maxIteration)
{
    // Se a inst�ncia n�o foi carregada corretamente, retorna
    if(!ready)
    {
        return -1;
    }

    // Quantidade de alfas
    float alfaLength = 10;

    // Alfa atual
    float alfa = 0.1;

    // Vetor de alfas
    vector<float> alfaList;

    for(int i = 0; i < alfaLength; i++)
    {
        alfaList.push_back(alfa);
        alfa += 0.1;
    }

    // Vetor que guarda quantas vezes um alfa foi utilizado
    vector<int> alfaCount;
    alfaCount.assign(alfaLength, 0);

    // Vetor com o somat�rio das solu��es geradas pelo alfa
    vector<float> alfaSum;
    alfaSum.assign(alfaLength, 0);

    // Vetor que guarda a m�dia dos resultados de cada alfa
    vector<float> alfaAvg;
    alfaAvg.assign(alfaLength, 0);

    // Vetor que guarda as probabilidades de cada alfa
    vector<float> alfaProb;
    alfaProb.assign(alfaLength, 0.1);

    // Melhor solu��o gerada
    float minSolution = INFINITE;

    // Custo gerado pelo alfa atual
    float alfaCost = INFINITE;

    // Itera��o atual
    int iteration = 0;

    // Posi��o do alfa atual
    int alfaPos = 0;

    // Gerando solu��es iniciais para cada alfa
    for(int i = 0; i < alfaLength; i++)
    {
        alfa = alfaList[i];

        // Gera um custo usando o alfa atual
        alfaCost = this->heuristic(alfa);

        // Atualiza a melhor solu��o gerada
        if(alfaCost < minSolution)
        {
            minSolution = alfaCost;
        }

        // Atualiza quantas vezes o alfa foi usado
        alfaCount[i] += 1;

        // Atualiza o somat�rio de solu��es geradas para o alfa
        alfaSum[i] += alfaCost;

        // Atualizando a m�dia de solu��es do alfa
        alfaAvg[i] = (alfaSum[i] / alfaCount[i]);
    }

    cout << "Itera��o: " << endl;

    // Executa o processo at� o m�ximo de itera��es
    while(iteration < maxIteration)
    {
        cout << iteration << " ";

        alfaPos = 0;

        // Somat�rio da qualidade dos alfas
        float qSum = 0;

        for(int i = 0; i < alfaLength; i++)
        {
            qSum += (minSolution / alfaAvg[i]);
        }

        // Atualiza vetor de probabilidades
        for(int i = 0; i < alfaLength; i++)
        {
            // Qualidade do alfa sobre o somat�rio da qualidade dos alfas
            alfaProb[i] = ((minSolution / alfaAvg[i]) / qSum);

            // Escolhendo alfa com maior probabilidade para a pr�xima itera��o
            if(alfaProb[alfaPos] < alfaProb[i])
            {
                alfaPos = i;
            }
        }

        int alfaUpdCount = 0;

        // Gera solu��es com um determinado alfa at� chegar no momento da troca de alfas
        while(alfaUpdCount < alfaUpdate)
        {
            alfa = alfaList[alfaPos];
            alfaCost = this->heuristic(alfa);

            // Atualiza a melhor solu��o gerada
            if(alfaCost < minSolution)
            {
                minSolution = alfaCost;
            }

            // Atualiza quantas vezes o alfa foi usado
            alfaCount[alfaPos] += 1;

            // Atualiza o somat�rio de solu��es geradas para o alfa
            alfaSum[alfaPos] += alfaCost;

            // Atualizando a m�dia de solu��es do alfa
            alfaAvg[alfaPos] = (alfaSum[alfaPos] / alfaCount[alfaPos]);

            alfaUpdCount++;
        }

        iteration++;
    }

    // Procurando pelo alfa que tem a maior probabilidade
    int alfaBest = 0;

    for(int i = 0; i < alfaLength; i++)
    {
        if(alfaProb[alfaBest] < alfaProb[i])
        {
            alfaBest = i;
        }
    }

    cout << "Melhor alfa: " << alfaList[alfaBest] << endl;
    cout << "M�dia dos custos gerados pelo melhor alfa: " << alfaAvg[alfaBest] << endl;

    return minSolution;
}

float HeuristicIMP::heuristic(float alfa)
{
    float dPath = 0; // Custo da solu��o atual
    int rotaCount = 0; // Quantidade de rotas encontradas para a solu��o atual

    vector<bool> visited;
    visited.assign(grafo->getVerticeCount(), false);

    visited[nodeBase] = true; // Marca o n� da base como visitado
    int visitedLength = 1; // Indica a quantidade de n�s que foram visitados (A base j� foi visitada)

    shared_ptr<Vehicle> truck = make_shared<Vehicle>(1, vehicleCapacity); // Cria um novo ve�culo para resolver o problema
    shared_ptr<OrderedList<Adjacencia>> adjBase = grafo->getAdjacenciaList(nodeBase); // Pega todas as adjac�ncias da base

    // Enquanto a quantidade de n�s visitados for menor que a quantidade de n�s do grafo
    while(visitedLength < grafo->getVerticeCount())
    {
        // Caminho feito em uma rota
        shared_ptr<OrderedList<Adjacencia>> caminho = make_shared<OrderedList<Adjacencia>>();

        // Lista de c�lculos de novas inser��es na rota
        shared_ptr<OrderedList<InsertCalculation>> calculo = make_shared<OrderedList<InsertCalculation>>();

        bool found = false;

        // Adiciona as duas primeiras arestas na solu��o
        adjBase->start();
        while(adjBase->getCurrentId() != -1 && !found)
        {
            // Pega o id do n� adjacente � base
            int idAdj = adjBase->getCurrentInfo()->getIdVertice2();

             // Se o n� ainda n�o foi visitado
            if(!visited[idAdj])
            {
                // Retira da capacidade do ve�culo a demanda do n� (Problema de entrega)
                truck->removeCapacity(grafo->getVerticeWeight(idAdj));

                // Adjac�ncias de ida (base, n�) e volta (n�, base), formando um ciclo
                shared_ptr<Adjacencia> ida =  grafo->getAdjacencia(idAdj, nodeBase);
                shared_ptr<Adjacencia> volta = grafo->getAdjacencia(nodeBase, idAdj);

                // Insere as adjac�ncias de ida e volta na solu��o
                caminho->insert(ida->getWeight(), ida, ListStart);
                caminho->insert(volta->getWeight(), volta, ListStart);

                // Marca o n� como visitado
                visited[idAdj] = true;
                visitedLength++;

                found = true;
            }

            adjBase->next();
        }

        // Trabalha em cima da solu��o adicionando novos v�rtices
        while(truck->getCapacity() >= 0)
        {
            // As duas �ltimas arestas adicionadas
            caminho->start();
            shared_ptr<Adjacencia> a2 = caminho->getCurrentInfo();

            caminho->next();
            shared_ptr<Adjacencia> a1 = caminho->getCurrentInfo();

//            // Custo da inser��o de novas arestas
//            shared_ptr<InsertCalculation> solution;

//            // Novas arestas da solu��o
//            shared_ptr<Adjacencia> s1;
//            shared_ptr<Adjacencia> s2;

//            // Aresta a ser removida da solu��o
//            shared_ptr<Adjacencia> removed;

            shared_ptr<OrderedList<Adjacencia>> adj1 = grafo->getAdjacenciaList(a1->getIdVertice1());
            shared_ptr<OrderedList<Adjacencia>> adj2 = grafo->getAdjacenciaList(a2->getIdVertice1());

            // C�lculo de a1
            adj1->start();
            while(adj1->getCurrentId() != -1)
            {
                int idAdj = adj1->getCurrentInfo()->getIdVertice2();

                // Verifica se o n� ainda n�o foi visitado, se o ve�culo tem capacidade e se existe adjac�ncia entre um v�rtice da solu��o e o novo v�rtice
                if(!visited[idAdj] && ((truck->getCapacity() - grafo->getVerticeWeight(idAdj)) > 0) && grafo->existsAdjacencia(idAdj, a1->getIdVertice2()))
                {
                    shared_ptr<InsertCalculation> ic = make_shared<InsertCalculation>();

                    ic->nodeId = idAdj; // Id do v�rtice
                    ic->idVertice1 = a1->getIdVertice1(); // Id do v�rtice 1 da adjac�ncia
                    ic->idVertice2 = a1->getIdVertice2(); // Id do v�rtice 2 da adjac�ncia

                    // Diferen�a que a inser��o ir� produzir na solu��o
                    ic->difPath = (adj1->getCurrentInfo()->getWeight() + grafo->getAdjacencia(idAdj, a1->getIdVertice2())->getWeight()) - a1->getWeight();

                    // Insere o c�lculo da diferen�a da inser��o na lista de c�lculos
                    calculo->insert(ic->difPath, ic, ListOrdered);
                }

                adj1->next();
            }

            // C�lculo de a2
            adj2->start();
            while(adj2->getCurrentId() != -1)
            {
                int idAdj = adj2->getCurrentInfo()->getIdVertice2();

                // Verifica se o n� ainda n�o foi visitado, se o ve�culo tem capacidade e se existe adjac�ncia entre um v�rtice da solu��o e o novo v�rtice
                if(!visited[idAdj] && ((truck->getCapacity() - grafo->getVerticeWeight(idAdj)) > 0) && grafo->existsAdjacencia(idAdj, a2->getIdVertice2()))
                {
                    shared_ptr<InsertCalculation> ic = make_shared<InsertCalculation>();

                    ic->nodeId = idAdj; // Id do v�rtice
                    ic->idVertice1 = a2->getIdVertice1(); // Id do v�rtice 1 da adjac�ncia
                    ic->idVertice2 = a2->getIdVertice2(); // Id do v�rtice 2 da adjac�ncia

                    // Diferen�a que a inser��o ir� produzir na solu��o
                    ic->difPath = (adj2->getCurrentInfo()->getWeight() + grafo->getAdjacencia(idAdj, a2->getIdVertice2())->getWeight()) - a2->getWeight();

                    // Insere o c�lculo da diferen�a da inser��o na lista de c�lculos
                    calculo->insert(ic->difPath, ic, ListOrdered);
                }

                adj2->next();
            }

            // Se a lista de c�lculos estiver vazia, n�o h� mais n�s que podem ser inseridos no caminho
            if(calculo->isEmpty())
            {
                caminho->start();

                while(!caminho->isEnd())
                {
                    // Conta o custo do caminho atual
                    dPath += caminho->getCurrentInfo()->getWeight();
                    caminho->next();
                }

                // Atualiza a quantidade de rotas geradas
                rotaCount++;
                break;
            }


            // Insere uma solu��o de forma randomizada
            int r = rand();
            int pos = (int)(alfa * calculo->getLength());
            int idSolution = (pos != 0) ? r % pos : 0;

            // Custo da inser��o de novas arestas
            shared_ptr<InsertCalculation> solution = calculo->get(idSolution);

            // Aresta a ser removida da solu��o
            shared_ptr<Adjacencia> removed = grafo->getAdjacencia(solution->idVertice1, solution->idVertice2);

            // Novas arestas que substituir�o a que ser� removida

            // Novas arestas da solu��o
            shared_ptr<Adjacencia> s1 = grafo->getAdjacencia(removed->getIdVertice1(), solution->nodeId);
            shared_ptr<Adjacencia> s2 = grafo->getAdjacencia(solution->nodeId, removed->getIdVertice2());

            // Insere as novas arestas na solu��o
            caminho->insert(s1->getWeight(), s1, ListStart);
            caminho->insert(s2->getWeight(), s2, ListStart);

            // Remove capacidade do caminh�o
            truck->removeCapacity(grafo->getVerticeWeight(solution->nodeId));

            // Novo n� visitado
            visited[solution->nodeId] = true;
            visitedLength++;

            // Atualiza a lista de c�lculos
            calculo->start();
            while(!calculo->isEnd() && !calculo->isEmpty())
            {
                shared_ptr<InsertCalculation> ic = calculo->getCurrentInfo();

                if(removed->equals(ic->idVertice1, ic->idVertice2)|| (truck->getCapacity() - grafo->getVerticeWeight(ic->nodeId) < 0) || visited[ic->nodeId])
                {
                    calculo->remove(calculo->getCurrentId());
                }
                else
                {
                    calculo->next();
                }
            }

            // Remove do caminho a aresta que foi substitu�da
            caminho->start();
            while(!caminho->isEnd() && !caminho->isEmpty())
            {
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

        // Como uma rota foi fechada o ve�culo passa a ter capacidade m�xima novamente
        truck->resetCapacity();
    }

//    cout << "Total de rotas: " << rotaCount << endl;
    return dPath;
}
