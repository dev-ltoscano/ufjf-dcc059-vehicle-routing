#include "../header/FileHelper.h"

CVRPInstance* FileHelper::readInstance(string fileName)
{
    ifstream streamFile;
    streamFile.open(fileName.c_str());

    // Verifica se o arquivo foi aberto
    if (!streamFile.is_open())
    {
        cout << endl << "[ Erro ]: N�o foi poss�vel abrir o arquivo da inst�ncia" << endl;
    }
    else
    {
        // Conta as se��es que foram lidas
        int sectionRead = 0;

        cout << "===== Lendo inst�ncia do CVRP =====" << endl << endl;

        CVRPInstance* instance = new CVRPInstance();

        string txtLine;

        // L� linha por linha do arquivo
        while (getline(streamFile, txtLine))
        {
            // Verifica se a linha lida � igual a se��o correspondente
            if(strcmp(txtLine.c_str(), string(NODE_COUNT_SECTION).c_str()) == 0)
            {
                cout << "Section: " << txtLine << endl;
                int nodeCount;
                streamFile >> nodeCount;
                instance->setVerticeCount(nodeCount);
                cout << "Quantidade de v�rtices: " << nodeCount << endl << endl;

                sectionRead++;
            }
            else if(strcmp(txtLine.c_str(), string(VEHICLE_CAP_SECTION).c_str()) == 0)
            {
                cout << "Section: " << txtLine << endl;
                float vehicleCapacity;
                streamFile >> vehicleCapacity;
                instance->setVehicleCapacity(vehicleCapacity);

                cout << "Capacidade do ve�culo: " << vehicleCapacity << endl << endl;

                sectionRead++;
            }
            else if(strcmp(txtLine.c_str(), string(NODE_COORD_SECTION).c_str()) == 0)
            {
                cout << "Section: " << txtLine << endl << endl;

                int nodeId;
                float nodeCoordX;
                float nodeCoordY;

                // L� as pr�ximas linhas at� o fim da sess�o
                while(getline(streamFile, txtLine) && (strcmp(txtLine.c_str(), string(END_SECTION).c_str())) != 0)
                {
                    stringstream streamLine(txtLine);

                    // L� as informa��es (id X Y) da linha
                    while(streamLine >> nodeId >> nodeCoordX >> nodeCoordY)
                    {
                        cout << "Id: " << nodeId << " -- X: " << nodeCoordX << " -- Y: " << nodeCoordY << endl;
                        instance->addVerticePoint(nodeId, new Point(nodeCoordX, nodeCoordY));
                    }
                }

                cout << endl;

                sectionRead++;
            }
            else if(strcmp(txtLine.c_str(), string(NODE_DEMAND_SECTION).c_str()) == 0)
            {
                cout << "Section: " << txtLine << endl << endl;

                int nodeId;
                float nodeWeight;

                // L� as pr�ximas linhas at� o fim da sess�o
                while(getline(streamFile, txtLine) && (strcmp(txtLine.c_str(), string(END_SECTION).c_str())) != 0)
                {
                    stringstream streamLine(txtLine);

                    // L� as informa��es da linha (id demanda)
                    while(streamLine >> nodeId >> nodeWeight)
                    {
                        cout << "Id: " << nodeId << " -- Demanda: " << nodeWeight << endl;
                        instance->addVerticeDemand(nodeId, nodeWeight);
                    }
                }

                cout << endl;

                sectionRead++;
            }
            else if(strcmp(txtLine.c_str(), string(NODE_BASE_SECTION).c_str()) == 0)
            {
                cout << "Section: " << txtLine << endl;
                int base;
                streamFile >> base;
                instance->setVerticeBase(base);
                cout << "Base: " << base << endl << endl;

                sectionRead++;
            }
        }

        // Verifica se todas as se��es foram lidas
        if(sectionRead < 5)
        {
            instance = NULL;
            cout << "[ Erro ]: N�o foi poss�vel ler todas as se��es da inst�ncia!" << endl << endl;
        }

        cout << "===== END FILE =====" << endl << endl;

        streamFile.close();

        return instance;
    }

    return NULL;
}
