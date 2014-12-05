//#ifndef HEURISTICCVRP_H_INCLUDED
//#define HEURISTICCVRP_H_INCLUDED
//
//#include "../grafo/ListaAdjacenciaVet.h"
//#include "FloydWarshall.h"
//#include "Vehicle.h"
//#include "../structure/list/OrderedList.h"
//
//#include <cmath>
//
//enum HeuristicType
//{
//    Gulosa, Randomizada, Reativa
//};
//
//class HeuristicCVRP
//{
//    private:
//        ListaAdjacenciaVet *grafo;
//        HeuristicType heuristic;
//        int itCount;
//
//        OrderedList<Adjacencia> *nodeRateList;
//
//        void calculateNodeRates(Floyd floyd);
//    public:
//        HeuristicCVRP(ListaAdjacenciaVet *grafo, HeuristicType heuristic, int itCount);
//        ~HeuristicCVRP();
//
//        void printNodeRateList();
//        int run(int nodeBase, float vehicleCapacity);
//};
//
//#endif // HEURISTICCVRP_H_INCLUDED
