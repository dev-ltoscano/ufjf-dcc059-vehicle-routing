#include <iostream>
#include <string>
#include <cstdlib>
#include <locale>
#include <chrono>

#include "header/FileHelper.h"
#include "header/heuristic/HeuristicIMP.h"

using namespace std;
using namespace std::chrono;

/**
*   Converte o padrão de arquivos das instâncias (*.vrp) para um padrão próprio em (*.txt)
*
*   @param inputFile - Arquivo de entrada *.vrp
*   @param outputFile - Arquivo de saída *.txt
**/
void parseVrpToCustomFile(string inputFile, string outputFile)
{
    ifstream streamFile;
    streamFile.open(inputFile.c_str());

    // Verifica se o arquivo de entrada foi aberto
    if (!streamFile.is_open())
    {
        cout << endl << "[ Erro ]: Não foi possível abrir o arquivo" << endl;
    }
    else
    {
        ofstream instance;
        instance.open(outputFile.c_str());

        // Verifica se o arquivo de saída foi criado
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

            // Lê linha a linha o arquivo de entrada
            while (getline(streamFile, txtLine))
            {
                // Escreve no arquivo de saída as seções correspondentes
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

        instance.flush();
        instance.close();
    }

    streamFile.close();
}

int main(int argc, char *argv[])
{
    // Tempo inicial da execução
    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    // Corrige acentuação do console
    setlocale(LC_ALL, "Portuguese");

    // Semeia o gerador rand()
    srand(time(NULL));

    // Verifica os parâmetros de entrada do console
    switch(argc)
    {
        // Gerar solução gulosa
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
        // Fazer parser de um arquivo *.vrp para padrão próprio
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
        // Gerar solução randomizada ou reativa
        case 5:
        {
            // Solução randomizada
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
            //Solução reativa
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
            cout << "[ Erro ]: Nenhum comando válido!" << endl;
        }
    }

    // Tempo final da execução
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    cout << "Tempo de execução (Segundos): " << ((float)chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() / SCALERATIO) << endl;

    return 0;
}
