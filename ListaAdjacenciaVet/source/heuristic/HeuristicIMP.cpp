#include "../../header/heuristic/HeuristicIMP.h"

HeuristicIMP::HeuristicIMP(string filename)
{
    CVRPInstance *instance = FileHelper::readInstance(filename);

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
        cout << "[ Erro ]: A instância não foi carregada corretamente! " << endl;
    }

    delete instance;
}

HeuristicIMP::~HeuristicIMP()
{
    delete this->grafo;
}

bool HeuristicIMP::isReady()
{
    return this->ready;
}

float HeuristicIMP::runGulosa()
{
    // Se a instância não foi carregada corretamente, retorna
    if(!ready)
    {
        return INFINITE;
    }

    cout << "Gerando solução gulosa..." << endl;
    return this->heuristic(0); // Gera uma solução gulosa
}

float HeuristicIMP::runRandom(double alfa, int maxIteration)
{
    // Se a instância não foi carregada corretamente, retorna
    if(!ready)
    {
        return INFINITE;
    }

    cout << "Gerando solução randomizada [ Alfa = " << alfa << " | maxIteration = " << maxIteration << "]"<< endl;

    float minCost = INFINITE; // Custo mínimo
    float sum = 0; // Somatório dos custos
    float cost = 0; // Custo atual

    cout << "Iteração: " << endl;

    // Gera até maxIteration de soluções
    for(int i = 0; i < maxIteration; i++)
    {
        cost = this->heuristic(alfa);

        // Atualiza custo mínimo
        if(cost < minCost)
        {
            minCost = cost;
        }

        sum += cost; // Atualiza a soma do custo das soluções
        cout << i << " ";
    }

    cout << endl << endl << "Custo médio (" << alfa << "): " << (sum / maxIteration) << endl;
    return minCost;
}

float HeuristicIMP::runReativa(int alfaUpdate, int maxIteration)
{
    // Se a instância não foi carregada corretamente, retorna
    if(!ready)
    {
        return INFINITE;
    }

    // Quantidade de alfas
    float alfaLength = 10;

    // Alfa atual
    double alfa = 0.1;

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

    // Vetor com o somatório das soluções geradas pelo alfa
    vector<double> alfaSum;
    alfaSum.assign(alfaLength, 0.0);

    // Vetor que guarda a média dos resultados de cada alfa
    vector<double> alfaAvg;
	alfaAvg.assign(alfaLength, 0.0);

    // Vetor que guarda as probabilidades de cada alfa
	vector<double> alfaProb;
    alfaProb.assign(alfaLength, 0.1);

    // Melhor solução gerada
    float minSolution = INFINITE;

    // Custo gerado pelo alfa atual
    float alfaCost = INFINITE;

    // Iteração atual
    int iteration = 0;

    // Posição do alfa atual
    int alfaPos = 0;

    // Quantidade de execuções para o alfa atual
    int alfaUpdCount = 0;

    cout << "Gerando solução randomizada [ AlfaUpdate = " << alfaUpdate << " | maxIteration = " << maxIteration << "]"<< endl;
    cout << "Iteração: " << endl;

    // Executa o processo até o máximo de iterações
    while(iteration < maxIteration)
    {
        alfaUpdCount = 0;

        // Gera soluções com um determinado alfa até chegar no momento da troca de alfas
        while(alfaUpdCount < alfaUpdate)
        {
            cout << iteration << " ";

            alfa = alfaList[alfaPos];
            alfaCost = this->heuristic(alfa);

            // Atualiza a melhor solução gerada
            if(alfaCost < minSolution)
            {
                minSolution = alfaCost;
            }

            // Atualiza quantas vezes o alfa foi usado
            alfaCount[alfaPos] += 1;

            // Atualiza o somatório de soluções geradas para o alfa
            alfaSum[alfaPos] += alfaCost;

            // Atualizando a média de soluções do alfa
            alfaAvg[alfaPos] = (alfaSum[alfaPos] / alfaCount[alfaPos]);

            alfaUpdCount++;
            iteration++;
        }

        // Assumindo que é o melhor alfa
        alfaPos = 0;

        // Somatório da qualidade dos alfas
        float qSum = 0;

        for(int i = 0; i < alfaLength; i++)
        {
            qSum += (minSolution / alfaAvg[i]);
        }

        // Atualiza vetor de probabilidades
        for(int i = 0; i < alfaLength; i++)
        {
            // Qualidade do alfa sobre o somatório da qualidade dos alfas
            alfaProb[i] = ((minSolution / alfaAvg[i]) / qSum);

            // Escolhendo alfa com maior probabilidade para a próxima iteração
            if(alfaProb[alfaPos] < alfaProb[i])
            {
                alfaPos = i;
            }
        }
    }

    // Assumindo que o alfa da posição inicial é o melhor
    alfaPos = 0;

    // Procurando pelo alfa que tem a maior probabilidade
    for(int i = 0; i < alfaLength; i++)
    {
        if(alfaProb[alfaPos] < alfaProb[i])
        {
            alfaPos = i;
        }
    }

    cout << endl << "Melhor alfa: " << alfaList[alfaPos] << endl;
    cout << "Média dos custos gerados pelo melhor alfa: " << alfaAvg[alfaPos] << endl;

    return minSolution;
}

float HeuristicIMP::heuristic(float alfa)
{
    float dPath = 0; // Custo da solução atual
    int rotaCount = 0; // Quantidade de rotas encontradas para a solução atual

    vector<bool> visited;
    visited.assign(grafo->getVerticeCount(), false);

    visited[nodeBase] = true; // Marca o nó da base como visitado
    int visitedLength = 1; // Indica a quantidade de nós que foram visitados (A base já foi visitada)

    Vehicle *truck = new Vehicle(1, vehicleCapacity); // Cria um novo veículo para resolver o problema
    OrderedList<Adjacencia> *adjBase = grafo->getAdjacenciaList(nodeBase); // Pega todas as adjacências da base

    // Enquanto a quantidade de nós visitados for menor que a quantidade de nós do grafo
    while(visitedLength < grafo->getVerticeCount())
    {
        // Caminho feito em uma rota
        OrderedList<Adjacencia> *caminho = new OrderedList<Adjacencia>(false);

        // Lista de cálculos de novas inserções na rota
        OrderedList<InsertCalculation> *calculo = new OrderedList<InsertCalculation>(true);

        bool found = false;

        // Adiciona as duas primeiras arestas na solução
        adjBase->start();
        while(adjBase->getCurrentId() != -1 && !found)
        {
            // Pega o id do nó adjacente à base
            int idAdj = adjBase->getCurrentInfo()->getIdVertice2();

             // Se o nó ainda não foi visitado
            if(!visited[idAdj])
            {
                // Retira da capacidade do veículo a demanda do nó (Problema de entrega)
                truck->removeCapacity(grafo->getVerticeWeight(idAdj));

                // Adjacências de ida (base, nó) e volta (nó, base), formando um ciclo
                Adjacencia *ida =  grafo->getAdjacencia(idAdj, nodeBase);
                Adjacencia *volta = grafo->getAdjacencia(nodeBase, idAdj);

                // Insere as adjacências de ida e volta na solução
                caminho->insert(ida->getWeight(), ida, ListStart);
                caminho->insert(volta->getWeight(), volta, ListStart);

                // Marca o nó como visitado
                visited[idAdj] = true;
                visitedLength++;

                found = true;
            }

            adjBase->next();
        }

        // Trabalha em cima da solução adicionando novos vértices
        while(truck->getCapacity() >= 0)
        {
            // As duas últimas arestas adicionadas
            caminho->start();
            Adjacencia *a2 = caminho->getCurrentInfo();

            caminho->next();
            Adjacencia *a1 = caminho->getCurrentInfo();

            OrderedList<Adjacencia> *adj1 = grafo->getAdjacenciaList(a1->getIdVertice1());
            OrderedList<Adjacencia> *adj2 = grafo->getAdjacenciaList(a2->getIdVertice1());

            // Cálculo de a1
            adj1->start();
            while(adj1->getCurrentId() != -1)
            {
                int idAdj = adj1->getCurrentInfo()->getIdVertice2();

                // Verifica se o nó ainda não foi visitado, se o veículo tem capacidade e se existe adjacência entre um vértice da solução e o novo vértice
                if(!visited[idAdj] && ((truck->getCapacity() - grafo->getVerticeWeight(idAdj)) > 0) && grafo->existsAdjacencia(idAdj, a1->getIdVertice2()))
                {
                    InsertCalculation *ic = new InsertCalculation();

                    ic->nodeId = idAdj; // Id do vértice
                    ic->idVertice1 = a1->getIdVertice1(); // Id do vértice 1 da adjacência
                    ic->idVertice2 = a1->getIdVertice2(); // Id do vértice 2 da adjacência

                    // Diferença que a inserção irá produzir na solução
                    ic->difPath = (adj1->getCurrentInfo()->getWeight() + grafo->getAdjacencia(idAdj, a1->getIdVertice2())->getWeight()) - a1->getWeight();

                    // Insere o cálculo da diferença da inserção na lista de cálculos
                    calculo->insert(ic->difPath, ic, ListOrdered);
                }

                adj1->next();
            }

            // Cálculo de a2
            adj2->start();
            while(adj2->getCurrentId() != -1)
            {
                int idAdj = adj2->getCurrentInfo()->getIdVertice2();

                // Verifica se o nó ainda não foi visitado, se o veículo tem capacidade e se existe adjacência entre um vértice da solução e o novo vértice
                if(!visited[idAdj] && ((truck->getCapacity() - grafo->getVerticeWeight(idAdj)) > 0) && grafo->existsAdjacencia(idAdj, a2->getIdVertice2()))
                {
                    InsertCalculation *ic = new InsertCalculation();

                    ic->nodeId = idAdj; // Id do vértice
                    ic->idVertice1 = a2->getIdVertice1(); // Id do vértice 1 da adjacência
                    ic->idVertice2 = a2->getIdVertice2(); // Id do vértice 2 da adjacência

                    // Diferença que a inserção irá produzir na solução
                    ic->difPath = (adj2->getCurrentInfo()->getWeight() + grafo->getAdjacencia(idAdj, a2->getIdVertice2())->getWeight()) - a2->getWeight();

                    // Insere o cálculo da diferença da inserção na lista de cálculos
                    calculo->insert(ic->difPath, ic, ListOrdered);
                }

                adj2->next();
            }

            // Se a lista de cálculos estiver vazia, não há mais nós que podem ser inseridos no caminho
            if(calculo->isEmpty())
            {
                caminho->start();

                while(!caminho->isEnd())
                {
                    // Conta o custo do caminho atual
                    dPath += caminho->getCurrentInfo()->getWeight();
                    caminho->next();
                }

                break;
            }


            // Insere uma solução de forma randomizada
            int r = rand();
            int pos = (int)(alfa * calculo->getLength());
            int idSolution = (pos != 0) ? r % pos : 0;

            // Custo da inserção de novas arestas
            InsertCalculation *solution = calculo->get(idSolution);

            // Aresta a ser removida da solução
            Adjacencia *removed = grafo->getAdjacencia(solution->idVertice1, solution->idVertice2);

            // Novas arestas que substituirão a que será removida

            // Novas arestas da solução
            Adjacencia *s1 = grafo->getAdjacencia(removed->getIdVertice1(), solution->nodeId);
            Adjacencia *s2 = grafo->getAdjacencia(solution->nodeId, removed->getIdVertice2());

            // Insere as novas arestas na solução
            caminho->insert(s1->getWeight(), s1, ListStart);
            caminho->insert(s2->getWeight(), s2, ListStart);

            // Remove capacidade do caminhão
            truck->removeCapacity(grafo->getVerticeWeight(solution->nodeId));

            // Novo nó visitado
            visited[solution->nodeId] = true;
            visitedLength++;

            // Atualiza a lista de cálculos
            calculo->start();
            while(!calculo->isEnd() && !calculo->isEmpty())
            {
                InsertCalculation *ic = calculo->getCurrentInfo();

                if(removed->equals(ic->idVertice1, ic->idVertice2)|| (truck->getCapacity() - grafo->getVerticeWeight(ic->nodeId) < 0) || visited[ic->nodeId])
                {
                    calculo->remove(calculo->getCurrentId());
                }
                else
                {
                    calculo->next();
                }
            }

            // Remove do caminho a aresta que foi substituída
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

        delete caminho;
        delete calculo;

        // Atualiza a quantidade de rotas geradas
        rotaCount++;

        // Como uma rota foi fechada o veículo passa a ter capacidade máxima novamente
        truck->resetCapacity();
    }

    delete truck;

//    cout << endl << "Total de rotas: " << rotaCount << endl;
    return dPath;
}
