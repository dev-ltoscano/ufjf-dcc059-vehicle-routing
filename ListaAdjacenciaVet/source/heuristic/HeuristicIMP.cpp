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
    bool *visited = new bool[grafo->getVerticeCount() * grafo->getVerticeCount()];
    Vehicle *truck = new Vehicle(1, vehicleCapacity, nodeBase);
    Vertice base = grafo->getVertice(nodeBase);
    OrderedList<Adjacencia> *adjBase = base.getAdjacenciaList();

    visited[nodeBase] = true;

    while(iteration < itCount){
        while(visitedLength < grafo->getAdjacenciaCount()){
            OrderedList<Adjacencia>* caminho = new OrderedList<Adjacencia>();
            OrderedList<InsertCalculation>* calculo = new OrderedList<InsertCalculation>();
            int arestas = 0;
            int calculos = 0;

            //ADICIONA AS DUAS PRIMEIRAS ARESTAS A SOLUÇÃO
            adjBase->start();
            while(adjBase->getCurrentId() != -1){
                int id = adjBase->getCurrentInfo()->getIdVertice2();
                if(!visited[id]){
                    Vertice n = grafo->getVertice(id);
                    truck->removeCapacity(n.getWeight());
                    Adjacencia* ida =  base.getAdjacencia(id);
                    Adjacencia* volta = n.getAdjacencia(nodeBase);

                    caminho->insert(arestas, ida->getWeight(), ida, InsertEnd);
                    arestas ++;
                    caminho->insert(arestas, volta->getWeight(), volta, InsertEnd);
                    arestas ++;

                    visited ++;
                    visited[adjBase->getCurrentId()] = true;

                    break;
                }
                adjBase->next();
            }

            //TRABALHA EM CIMA DA SOLUÇÃO ADICIONANDO VÉRTICES ATÉ
            while(truck->getCapacity() > 0){
                //AS DUAS UÚLTIMAS ARESTAS ADICIONADAS (a1, a2)
                Adjacencia* a1 = caminho->getNodeInfo(arestas - 2);
                Adjacencia* a2 = caminho->getNodeInfo(arestas - 1);

                //SOLUÇÃO A SER INSERIDA
                InsertCalculation* solution;
                //VERTICE DA SOLUÇÃO
                Vertice vertSolution;
                //ARESTAS DA SOLUÇÃO (s1, s2)
                Adjacencia* s1;
                Adjacencia* s2;
                //ARESTA A SER REMOVIDA DA SOLUÇÃO
                Adjacencia* removed;

                //CÁLCULO DE a1
                Vertice v1 = grafo->getVertice(a1->getIdVertice1());
                OrderedList<Adjacencia>* adj = v1.getAdjacenciaList();
                adj->start();
                while(adj->getCurrentId() != -1){
                    int id = adj->getCurrentInfo()->getIdVertice2();
                    Vertice v = grafo->getVertice(id);
                    if(v.existsAdjacencia(a1->getIdVertice2()) && (truck->getCapacity() - v.getWeight()) > 0){
                        InsertCalculation* ic = new InsertCalculation();
                        ic->adj = a1;
                        ic->nodeId = id;
                        ic->difPath = (adj->getCurrentInfo()->getWeight() + v.getAdjacencia(a1->getIdVertice2())->getWeight()) - a1->getWeight();
                        calculo->insert(calculos,ic->difPath,ic);
                        calculos ++;
                    }
                    adj->next();
                }

                //CÁLCULO DE a2
                v1 = grafo->getVertice(0);
                adj = v1.getAdjacenciaList();
                adj->start();
                while(adj->getCurrentId() != -1){
                    int id = adj->getCurrentInfo()->getIdVertice2();
                    Vertice v = grafo->getVertice(id);
                    if(v.existsAdjacencia(a2->getIdVertice2()) && (truck->getCapacity() - v.getWeight()) > 0){
                        InsertCalculation* ic = new InsertCalculation();
                        ic->adj = a2;
                        ic->nodeId = id;
                        ic->difPath = (adj->getCurrentInfo()->getWeight() + v.getAdjacencia(a2->getIdVertice2())->getWeight()) - a2->getWeight();
                        calculo->insert(calculos,ic->difPath,ic);
                        calculos ++;
                    }
                    adj->next();
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
                vertSolution = grafo->getVertice(solution->nodeId);
                removed = solution->adj;
                s1 =  grafo->getVertice(removed->getIdVertice1()).getAdjacencia(solution->nodeId);
                s2 = vertSolution.getAdjacencia(removed->getIdVertice2());
                caminho->insert(arestas, s1->getWeight(), s1,InsertEnd);
                arestas ++;
                caminho->insert(arestas, s2->getWeight(), s2, InsertEnd);
                arestas ++;
                truck->removeCapacity(vertSolution.getWeight());
                visitedLength ++;
                visited[solution->nodeId];

                //ATUALIZA OS CÁLCULOS
                calculo->remove(InsertStart);
                calculo->start();
                while(calculo->getCurrentId() != -1){
                    InsertCalculation* ic = calculo->getNodeInfo(calculo->getCurrentId());
                    if(ic->adj == removed || (truck->getCapacity() - grafo->getVertice(ic->nodeId).getWeight() < 0)){
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
    delete this->grafo;
}
