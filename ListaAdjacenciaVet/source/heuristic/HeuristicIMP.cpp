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
    OrderedList<Adjacencia> *adjBase = grafo->getAdjacenciaList(nodeBase);

    for(int i = 0; i < grafo->getVerticeCount(); i ++){
        visited[i] = false;
    }
    visited[nodeBase] = true;

    while(iteration < itCount){
        while(visitedLength < grafo->getVerticeCount()){
            Vehicle *truck = new Vehicle(1, vehicleCapacity, nodeBase);
            OrderedList<Adjacencia>* caminho = new OrderedList<Adjacencia>();
            OrderedList<InsertCalculation>* calculo = new OrderedList<InsertCalculation>();
            bool found = false;

            //ADICIONA AS DUAS PRIMEIRAS ARESTAS A SOLU��O
            adjBase->start();
            while(adjBase->getCurrentId() != -1 && !found){
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

                    found = true;
                }
                adjBase->next();
            }

            //TRABALHA EM CIMA DA SOLU��O ADICIONANDO V�RTICES AT�
            while(truck->getCapacity() > 0){
                //AS DUAS U�LTIMAS ARESTAS ADICIONADAS (a1, a2)
                caminho->start();
                Adjacencia* a2 = caminho->getCurrentInfo();
                caminho->next();
                Adjacencia* a1 = caminho->getCurrentInfo();

                //SOLU��O A SER INSERIDA
                InsertCalculation* solution;
                //ARESTAS DA SOLU��O (s1, s2)
                Adjacencia* s1;
                Adjacencia* s2;
                //ARESTA A SER REMOVIDA DA SOLU��O
                Adjacencia* removed;

                //C�LCULO DE a1
                OrderedList<Adjacencia>* adj1 = grafo->getAdjacenciaList(a1->getIdVertice1());
                OrderedList<Adjacencia>* adj2 = grafo->getAdjacenciaList(a2->getIdVertice1());
                printf("a1: %d -> %d\n",a1->getIdVertice1(),a1->getIdVertice2());
                adj1->start();
                while(adj1->getCurrentId() != -1){
                    int id = adj1->getCurrentInfo()->getIdVertice2();
                    if(grafo->existsAdjacencia(id,a1->getIdVertice2()) && (truck->getCapacity() - grafo->getVerticeWeight(id)) > 0 && !visited[id]){
                        InsertCalculation* ic = new InsertCalculation();
                        ic->idVertice1 = a1->getIdVertice1();
                        ic->idVertice2 = a1->getIdVertice2();
                        ic->nodeId = id;
                        ic->difPath = (adj1->getCurrentInfo()->getWeight() + grafo->getAdjacencia(id,a1->getIdVertice2())->getWeight()) - a1->getWeight();
                        calculo->insert(ic->difPath,ic, InsertOrdered);
                    }
                    adj1->next();
                }

                //C�LCULO DE a2
                printf("a2: %d -> %d\n",a2->getIdVertice1(),a2->getIdVertice2());
                adj2->start();
                while(adj2->getCurrentId() != -1){
                    int id = adj2->getCurrentInfo()->getIdVertice2();
                    if(grafo->existsAdjacencia(id,a2->getIdVertice2()) && (truck->getCapacity() - grafo->getVerticeWeight(id)) > 0 && !visited[id]){
                        InsertCalculation* ic = new InsertCalculation();
                        ic->idVertice1 = a2->getIdVertice1();
                        ic->idVertice2 = a2->getIdVertice2();
                        ic->nodeId = id;
                        ic->difPath = (adj2->getCurrentInfo()->getWeight() + grafo->getAdjacencia(id,a2->getIdVertice2())->getWeight()) - a2->getWeight();
                        calculo->insert(ic->difPath,ic, InsertOrdered);
                    }
                    adj2->next();
                }

                cout << " -- CALCULOS -- " << endl;
                calculo->start();
                while(calculo->getCurrentId() != -1){
                    InsertCalculation* ic = calculo->getNodeInfo(calculo->getCurrentId());
                    cout << ic->idVertice1 << " -> " << ic->idVertice2 << ": node= " << ic->nodeId << " deltaPath= " << ic->difPath << " visited[i] " << visited[ic->nodeId] << endl;
                    calculo->next();

                }
                cout << endl << endl;

                //SE A LISTA DE C�LCULOS ESTIVER VAZIA N�O H� MAIS N�S QUE SEJA POSS�VEL INSERIR NO CAMINHO
                if(calculo->isEmpty()){
                    caminho->start();
                    cout << " --- CAMINHO FINAL --- " << endl;
                    while(caminho->getCurrentId() != -1){
                        path += caminho->getCurrentInfo()->getWeight();
                        cout << caminho->getCurrentInfo()->getIdVertice1() << " -> " << caminho->getCurrentInfo()->getIdVertice2() << endl;
                        caminho->next();
                    }
                    cout << endl << endl;
                    break;
                }


                //INSERE A MELHOR SOLU��O (GULOSA)
                calculo->start();
                solution = calculo->getCurrentInfo();
                cout << "ADD NO: " << solution->nodeId << endl;
                removed = grafo->getAdjacencia(solution->idVertice1, solution->idVertice2);
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

                //ATUALIZA OS C�LCULOS
                calculo->start();
                cout << "CALC TAM -> " << calculo->getLength() << endl;
                while(!calculo->isEnd() && !calculo->isEmpty()){
                    InsertCalculation* ic = calculo->getCurrentInfo();
                    cout << "REMOVED (" << removed->getIdVertice1() << " -> " << removed->getIdVertice2();
                    cout << ") == (" << ic->idVertice1 << " -> " << ic->idVertice2 << ")" << endl;
                    if(removed->equals(ic->idVertice1, ic->idVertice2)|| (truck->getCapacity() - grafo->getVerticeWeight(ic->nodeId) < 0) || visited[ic->nodeId]){
                        cout << "TIREI " << ic->idVertice1 << " -> " << ic->idVertice2 << ": node= " << ic->nodeId << " deltaPath= " << ic->difPath << " visited[i] " << visited[ic->nodeId] << endl;
                        calculo->remove(calculo->getCurrentId());
                    } else {
                        calculo->next();
                    }
                }

                //REMOVE DO CAMINHO A ARESTA QUE FOI SUBSTITU�DA
                caminho->start();
                while(!caminho->isEnd() && !caminho->isEmpty()){
                    cout << " --- REMOVE ARESTA --- " << endl;
                    cout << caminho->getCurrentInfo()->getIdVertice1() << " - > " << caminho->getCurrentInfo()->getIdVertice2();
                    cout << " == " <<removed->getIdVertice1() << " -> " << removed->getIdVertice2() << endl;
                    if(removed->equals(caminho->getCurrentInfo())){
                        caminho->remove(caminho->getCurrentId());
                        break;
                    } else {
                        caminho->next();
                    }
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
