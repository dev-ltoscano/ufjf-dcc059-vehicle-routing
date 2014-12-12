#include <iostream>
#include <string>
#include <stdlib.h> // rand();
#include <locale> // setlocale();
#include <chrono>

#include "header/grafo/ListaAdjacenciaVet.h"
#include "header/structure/list/OrderedList.h"
#include "header/Helper.h"
#include "header/FileHelper.h"
#include "header/heuristic/HeuristicCVRP.h"
#include "header/heuristic/HeuristicIMP.h"

using namespace std;
using namespace std::chrono;

ListaAdjacenciaVet* createGrafo(int maxNodes, OperationType type)
{
    ListaAdjacenciaVet *grafo = new ListaAdjacenciaVet(maxNodes, true, type);

    for(int i = 0; i < maxNodes; i++)
    {
        for(int j = 0; j < maxNodes; j++)
        {
            if(i != j)
            {
                grafo->addAdjacencia(i, j, rand() % 100);
            }
        }
    }

    for(int i = 1; i < maxNodes; i++)
    {
        grafo->setVerticeWeight(i, rand() % 100);
    }

    grafo->setVerticeWeight(0, 0);

    return grafo;
}

void parseVrpToCustomFile(string fileName, string instanceName)
{
    ifstream streamFile;
    streamFile.open(fileName.c_str());

    if (!streamFile.is_open())
    {
        cout << endl << "[ Erro ]: Não foi possível abrir o arquivo" << endl;
    }
    else
    {
        ofstream instance;
        string filePath = "Instance/" + instanceName;
        instance.open(filePath.c_str());

        if(!instance.is_open())
            cout << endl << "[ Erro ]: Não foi possível criar o arquivo da instância" << endl;
        else
        {
            cout << "===== Fazendo parsing do arquivo CVRP =====" << endl << endl;

            instance << "NODE_COUNT_SECTION" << endl << endl;
            instance << "END_SECTION" << endl;
            instance << "VEHICLE_CAP_SECTION" << endl << endl;
            instance << "END_SECTION" << endl;

            string txtLine;
            while (getline(streamFile, txtLine))
            {
                if(txtLine == "NODE_COORD_SECTION")
                {
                    instance << "NODE_COORD_SECTION" << endl;

                    int nodeId;
                    int nodeCoordX;
                    int nodeCoordY;

                    while(getline(streamFile, txtLine) && (txtLine != "END_SECTION"))
                    {
                        istringstream streamLine(txtLine);

                        while(streamLine >> nodeId >> nodeCoordX >> nodeCoordY)
                        {
                            cout << "Id: " << nodeId << " -- X: " << nodeCoordX << " -- Y: " << nodeCoordY << endl;
                            instance << (nodeId -1) << " " << nodeCoordX << " " << nodeCoordY << endl;
                        }
                    }

                    instance << "END_SECTION" << endl;
                    cout << endl;
                }
                else if(txtLine == "DEMAND_SECTION")
                {
                    instance << "NODE_DEMAND_SECTION" << endl;

                    int nodeId;
                    int nodeDemand;

                    while(getline(streamFile, txtLine) && (txtLine != "END_SECTION"))
                    {
                        istringstream streamLine(txtLine);

                        while(streamLine >> nodeId >> nodeDemand)
                        {
                            cout << "Id: " << nodeId << " -- Demand: " << nodeDemand << endl;
                            instance << (nodeId -1) << " " << nodeDemand << endl;
                        }
                    }

                    instance << "END_SECTION" << endl;
                    cout << endl;
                }
                else if(txtLine == "DEPOT_SECTION")
                {
                    instance << "NODE_BASE_SECTION" << endl;

                    int nodeBase;

                    while(getline(streamFile, txtLine) && (txtLine != "END_SECTION"))
                    {
                        istringstream streamLine(txtLine);

                        while(streamLine >> nodeBase)
                        {
                            cout << "Base: " << nodeBase << endl;
                            instance << (nodeBase -1) << endl;
                        }
                    }

                    instance << "END_SECTION" << endl;
                    cout << endl;
                }
            }

            instance << "END_FILE" << endl;
            cout << "===== END PARSING =====" << endl << endl;
        }
    }
}

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL)); // Seed the time

    if((argv[1] != NULL) && (string(argv[1]) == "parse") && (argv[2] != NULL) && (argv[3] != NULL))
    {
        parseVrpToCustomFile("Parse/" + string(argv[2]), string(argv[3]));
    }
    else if((argv[1] != NULL) && (string(argv[1]) == "gulosa") && (argv[2] != NULL))
    {
        CVRPInstance *instance = FileHelper::readInstance("Instance/" + string(argv[2]));
        HeuristicIMP *h = new HeuristicIMP(Gulosa, 0);
        cout << "Custo: " << h->run(instance) << endl;
    }
    else if((argv[1] != NULL) && (string(argv[1]) == "rand") && (argv[2] != NULL) && (argv[3] != NULL) && (argv[4] != NULL))
    {
        CVRPInstance *instance = FileHelper::readInstance("Instance/" + string(argv[2]));
        ListaAdjacenciaVet *grafo = instance->createInstance();

        float alfa = atof(argv[3]);
        HeuristicIMP *h = new HeuristicIMP(Randomizada, alfa);

        int minPath = INFINITE;
        int media = 0;

        int iteration = atof(argv[4]);

        for(int j = 0; j < iteration; j++)
        {
            int path = h->run(instance);

            if(path < minPath)
            {
                minPath = path;
            }

            media += path;
            cout << "Custo (" << alfa << "): " << path << endl << endl;
        }

        cout << "Custo mínimo (" << alfa << "): " << minPath << endl;
        cout << "Custo médio (" << alfa << "): " << (media/iteration) << endl;
    }
    else
    {
//        CVRPInstance *instance = FileHelper::readInstance("Instance/instance20.txt");
//        ListaAdjacenciaVet *grafo = instance->createInstance();
//
//        HeuristicIMP *h = new HeuristicIMP(Randomizada, 0);
//        cout << "Custo: " << h->run(grafo, instance->getVerticeBase(), instance->getVehicleCapacity()) << endl;


        CVRPInstance *instance = FileHelper::readInstance("Instance/instance20.txt");
        ListaAdjacenciaVet *grafo = instance->createInstance();

        HeuristicIMP *h = new HeuristicIMP(Randomizada, 0);

        cout << "Custo: " << h->run(instance) << endl;
        h->setAlfa(0.1);
        cout << "Custo: " <<  h->run(instance) << endl;
        h->setAlfa(0.2);
        cout << "Custo: " << h->run(instance) << endl;
        h->setAlfa(0.3);
        cout << "Custo: " <<h->run(instance) << endl;
        h->setAlfa(0.4);
        cout << "Custo: " << h->run(instance) << endl;
        h->setAlfa(0.5);
        cout << "Custo: " << h->run(instance) << endl;
        h->setAlfa(0.6);
        cout << "Custo: " << h->run(instance) << endl;

//        int minPath = INFINITE;
//        int media = 0;
//
//        int iteration = 10;
//
//        for(int j = 0; j < iteration; j++)
//        {
//            int path = h->run(instance);
//
//            if(path < minPath)
//            {
//                minPath = path;
//            }
//
//            media += path;
//            cout << "Custo (" << alfa << "): " << path << endl << endl;
//        }
//
//        cout << "Custo mínimo (" << alfa << "): " << minPath << endl;
//        cout << "Custo médio (" << alfa << "): " << (media/iteration) << endl;
    }

//    ListaAdjacenciaVet *grafo = createGrafo(15, 15, true, InsertEnd);
//    high_resolution_clock::time_point t1 = high_resolution_clock::now();
//    ListaAdjacenciaVet *grafo = createGrafo(300, ListOrdered);
//    HeuristicIMP *heuristic = new HeuristicIMP(Gulosa, 1, 0);
//    cout << "Custo: " << heuristic->run(grafo, 0, 100) << endl;

//    ListaAdjacenciaVet *grafo = new ListaAdjacenciaVet(5, true, InsertOrdered);
//
//    grafo->addAdjacencia(0,1,1);
//    grafo->addAdjacencia(0,2,1);
//    grafo->addAdjacencia(0,3,1);
//    grafo->addAdjacencia(0,4,1);
//
//    grafo->addAdjacencia(1,0,1);
//    grafo->addAdjacencia(1,2,1);
//    grafo->addAdjacencia(1,3,1);
//    grafo->addAdjacencia(1,4,1);
//
//    grafo->addAdjacencia(2,0,1);
//    grafo->addAdjacencia(2,1,1);
//    grafo->addAdjacencia(2,3,1);
//    grafo->addAdjacencia(2,4,1);
//
//    grafo->addAdjacencia(3,0,1);
//    grafo->addAdjacencia(3,1,1);
//    grafo->addAdjacencia(3,2,1);
//    grafo->addAdjacencia(3,4,1);
//
//    grafo->addAdjacencia(4,0,1);
//    grafo->addAdjacencia(4,1,1);
//    grafo->addAdjacencia(4,2,1);
//    grafo->addAdjacencia(4,3,1);
//
//    grafo->setVerticeWeight(0,0);
//    grafo->setVerticeWeight(1,50);
//    grafo->setVerticeWeight(2,40);
//    grafo->setVerticeWeight(3,20);
//    grafo->setVerticeWeight(4,90);

//
//    high_resolution_clock::time_point t2 = high_resolution_clock::now();
//    int duration = chrono::duration_cast<chrono::seconds>(t2 - t1).count();
//    cout << duration;

    system("PAUSE");

//    delete grafo;
    return 0;
}
