#include <iostream>
#include <string>
#include <cstdlib>
#include <locale>
#include <chrono>

//#include "header/grafo/ListaAdjacenciaVet.h"
//#include "header/structure/list/OrderedList.h"
//#include "header/Helper.h"
#include "header/FileHelper.h"
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

void parseVrpToCustomFile(string inputFile, string outputFile)
{
    ifstream streamFile;
    streamFile.open(inputFile.c_str());

    if (!streamFile.is_open())
    {
        cout << endl << "[ Erro ]: Não foi possível abrir o arquivo" << endl;
    }
    else
    {
        ofstream instance;
        instance.open(outputFile.c_str());

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

int main(int argc, char *argv[])
{
    // Tempo inicial da execução
    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    // Corrige acentuação do console
    setlocale(LC_ALL, "Portuguese");

    // Semeia o gerador rand()
    srand(time(NULL));

    switch(argc)
    {
        case 3:
        {
            cout << (argv[1] == string("gulosa")) << endl;
            if((argv[1] != NULL) && (argv[1] == string("gulosa")) && (argv[2] != NULL))
            {
                shared_ptr<HeuristicIMP> h = make_shared<HeuristicIMP>(string(argv[2]));
                cout << "Custo mínimo: " << h->runGulosa() << endl;
            }
            else
            {
                cout << "[ Erro ] Parâmetros inválidos!" << endl;
            }

            break;
        }
        case 4:
        {
            if((argv[1] != NULL) && (argv[1] == string("parser")) && (argv[2] != NULL) && (argv[3] != NULL))
            {
                parseVrpToCustomFile(string(argv[2]), string(argv[3]));
            }
            else
            {
                cout << "[ Erro ] Parâmetros inválidos!" << endl;
            }

            break;
        }
        case 5:
        {
            if((argv[1] != NULL) && (argv[1] == string("rand")))
            {
                if((argv[2] != NULL) && (argv[3] != NULL) && (argv[4] != NULL))
                {
                    shared_ptr<HeuristicIMP> h = make_shared<HeuristicIMP>(string(argv[2]));

                    float alfa = atof(argv[3]);
                    int maxIteration = atoi(argv[4]);
                    cout << "Custo mínimo: " << h->runRandom(alfa, maxIteration) << endl;
                }
                else
                {
                    cout << "[ Erro ] Parâmetros inválidos!" << endl;
                }
            }
            else if((argv[1] != NULL) && (argv[1] == string("reat")))
            {
                if((argv[2] != NULL) && (argv[3] != NULL) && (argv[4] != NULL))
                {
                    shared_ptr<HeuristicIMP> h = make_shared<HeuristicIMP>(string(argv[2]));

                    float alfa = atol(argv[3]);
                    int maxIteration = atol(argv[4]);

                    cout << "Custo mínimo: " << h->runReativa(alfa, maxIteration) << endl;
                }
                else
                {
                    cout << "[ Erro ] Parâmetros inválidos!" << endl;
                }
            }

            break;
        }
        default:
        {
                shared_ptr<HeuristicIMP> h = make_shared<HeuristicIMP>("Instance/instance101.txt");
                cout << "Custo: " << h->runReativa(50, 2500) << endl;
        }
    }

    // Tempo final da execução
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    cout << "Tempo de execução (Segundos): " << ((float)chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() / SCALERATIO) << endl;

    return 0;
}
