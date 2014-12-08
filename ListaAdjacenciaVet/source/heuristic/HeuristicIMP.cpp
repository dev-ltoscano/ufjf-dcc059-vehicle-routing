#include "../../header/heuristic/HeuristicIMP.h"

HeuristicIMP::HeuristicIMP(ListaAdjacenciaVet *grafo, HeuristicType heuristic, int itCount)
{
    this->grafo = grafo;
    this->heuristic = heuristic;
    this->itCount = (heuristic == Gulosa) ? 1 : itCount;
}

int HeuristicIMP::run(int nodeBase, float vehicleCapacity){
    int visitedLength = 1;
    int iteration = 0;
    int path = 0;
    bool *visited = new bool[grafo->getVerticeCount()];
    Vehicle *truck = new Vehicle(1, vehicleCapacity, nodeBase);
    OrderedList<Adjacencia> *adjBase = grafo->getAdjacenciaList(nodeBase);

    for(int i = 0; i < grafo->getVerticeCount(); i ++){
        visited[i] = false;
    }
    visited[nodeBase] = true;

    while(iteration < itCount){
        while(visitedLength < grafo->getAdjacenciaCount()){
            OrderedList<Adjacencia>* caminho = new OrderedList<Adjacencia>();
            OrderedList<InsertCalculation>* calculo = new OrderedList<InsertCalculation>();

            //ADICIONA AS DUAS PRIMEIRAS ARESTAS A SOLUÇÃO
            adjBase->start();
            while(adjBase->getCurrentId() != -1){
                int id = adjBase->getCurrentInfo()->getIdVertice2();
                if(!visited[id]){
                    truck->removeCapacity(grafo->getVerticeWeight(id));
                    Adjacencia* ida =  grafo->getAdjacencia(id,nodeBase);
                    Adjacencia* volta = grafo->getAdjacencia(nodeBase,id);

                    caminho->insert(ida->getWeight(), ida, InsertStart);
                    caminho->insert(volta->getWeight(), volta, InsertStart);

                    visitedLength ++;

                    visited[adjBase->getCurrentId()] = true;
                    cout << "PRIMEIRO NO: " << adjBase->getCurrentId() << endl;
                    for(int i = 0; i < grafo->getVerticeCount(); i ++)
                        cout << i << ": visited = " << visited[i] << endl;

                    break;
                }
                adjBase->next();
            }

            //TRABALHA EM CIMA DA SOLUÇÃO ADICIONANDO VÉRTICES ATÉ
            while(truck->getCapacity() > 0){
                //AS DUAS UÚLTIMAS ARESTAS ADICIONADAS (a1, a2)
                caminho->start();
                Adjacencia* a2 = caminho->getCurrentInfo();
                caminho->next();
                Adjacencia* a1 = caminho->getCurrentInfo();

                //SOLUÇÃO A SER INSERIDA
                InsertCalculation* solution;
                //ARESTAS DA SOLUÇÃO (s1, s2)
                Adjacencia* s1;
                Adjacencia* s2;
                //ARESTA A SER REMOVIDA DA SOLUÇÃO
                Adjacencia* removed;

                //CÁLCULO DE a1
                OrderedList<Adjacencia>* adj1 = grafo->getAdjacenciaList(a1->getIdVertice1());
                OrderedList<Adjacencia>* adj2 = grafo->getAdjacenciaList(a2->getIdVertice1());
                printf("a1: %d -> %d\n",a1->getIdVertice1(),a1->getIdVertice2());
                adj1->start();
                while(adj1->getCurrentId() != -1){
                    int id = adj1->getCurrentInfo()->getIdVertice2();
                    cout << " --- ID " << id << " --- " << endl;
                    if(!grafo->existsAdjacencia(id,a1->getIdVertice2()))
                        cout << id << " -> " << a1->getIdVertice2() << "/E" << endl;
                    if(!(truck->getCapacity() - grafo->getVerticeWeight(id)) > 0)
                        cout << "CAPACITY OVERFLOW" << endl;
                    if(visited[id])
                        cout << "VISITED" << endl;
                    if(grafo->existsAdjacencia(id,a1->getIdVertice2()) && (truck->getCapacity() - grafo->getVerticeWeight(id)) > 0 && !visited[id]){
                        InsertCalculation* ic = new InsertCalculation();
                        ic->adj = a1;
                        ic->nodeId = id;
                        ic->difPath = (adj1->getCurrentInfo()->getWeight() + grafo->getAdjacencia(id,a1->getIdVertice2())->getWeight()) - a1->getWeight();
                        calculo->insert(ic->difPath,ic, InsertOrdered);
                        cout << "ADDED" << endl;
                    }
                    adj1->next();
                }

                //CÁLCULO DE a2
                printf("a2: %d -> %d\n",a2->getIdVertice1(),a2->getIdVertice2());
                adj2->start();
                while(adj2->getCurrentId() != -1){
                    int id = adj2->getCurrentInfo()->getIdVertice2();
                    cout << " --- ID " << id << " --- " << endl;
                    if(!grafo->existsAdjacencia(id,a1->getIdVertice2()))
                        cout << id << " -> " << a1->getIdVertice2() << "/E" << endl;
                    if(!(truck->getCapacity() - grafo->getVerticeWeight(id)) > 0)
                        cout << "CAPACITY OVERFLOW" << endl;
                    if(visited[id])
                        cout << "VISITED" << endl;
                    if(grafo->existsAdjacencia(id,a2->getIdVertice2()) && (truck->getCapacity() - grafo->getVerticeWeight(id)) > 0 && !visited[id]){
                        InsertCalculation* ic = new InsertCalculation();
                        ic->adj = a2;
                        ic->nodeId = id;
                        ic->difPath = (adj2->getCurrentInfo()->getWeight() + grafo->getAdjacencia(id,a2->getIdVertice2())->getWeight()) - a2->getWeight();
                        calculo->insert(ic->difPath,ic, InsertOrdered);
                        cout << "ADDED" << endl << endl;
                    }
                    adj2->next();
                }

                cout << " -- CALCULOS -- " << endl;
                calculo->start();
                while(calculo->getCurrentId() != -1){
                    InsertCalculation* ic = calculo->getNodeInfo(calculo->getCurrentId());
                    cout << ic->adj->getIdVertice1() << " -> " << ic->adj->getIdVertice2() << ": node= " << ic->nodeId << " deltaPath= " << ic->difPath << " visited[i] " << visited[ic->nodeId] << endl;
                    calculo->next();

                }

                //SE A LISTA DE CÁLCULOS ESTIVER VAZIA NÃO HÁ MAIS NÓS QUE SEJA POSSÍVEL INSERIR NO CAMINHO
                if(calculo->isEmpty()){
                    caminho->start();
                    while(caminho->getCurrentId() != -1){
                        path += caminho->getCurrentInfo()->getWeight();
                        caminho->next();
                    }
                    break;
                }


                //INSERE A MELHOR SOLUÇÃO (GULOSA)
                calculo->start();
                solution = calculo->getCurrentInfo();
                cout << "ADD NO: " << solution->nodeId << endl;
                removed = solution->adj;
                cout << "REMOVE PATH: " << removed->getIdVertice1() << " -> " << removed->getIdVertice2() << endl;
                s1 = grafo->getAdjacencia(removed->getIdVertice1(),solution->nodeId);
                s2 = grafo->getAdjacencia(solution->nodeId,removed->getIdVertice2());
                caminho->insert(s1->getWeight(), s1,InsertStart);
                caminho->insert(s2->getWeight(), s2, InsertStart);
                truck->removeCapacity(grafo->getVerticeWeight(solution->nodeId));
                visitedLength ++;
                visited[solution->nodeId] = true;
                for(int i = 0; i < grafo->getVerticeCount(); i ++)
                    cout << i << ": visited = " << visited[i] << endl;

                //ATUALIZA OS CÁLCULOS
                calculo->start();
                while(calculo->getCurrentId() != -1){
                    InsertCalculation* ic = calculo->getNodeInfo(calculo->getCurrentId());
                    if(ic->adj == removed || (truck->getCapacity() - grafo->getVertice(ic->nodeId).getWeight() < 0) || visited[ic->nodeId]){
                        cout << "TIREI " << ic->adj->getIdVertice1() << " -> " << ic->adj->getIdVertice2() << ": node= " << ic->nodeId << " deltaPath= " << ic->difPath << " visited[i] " << visited[ic->nodeId] << endl;
                        calculo->remove(calculo->getCurrentId());
                    }
                    calculo->next();
                }
            }
        }
        iteration ++;
    }

    return path;
}

HeuristicIMP::~HeuristicIMP()
{
}
