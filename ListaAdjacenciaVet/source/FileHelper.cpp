#include "../header/FileHelper.h"

CVRPInstance* FileHelper::readInstance(string fileName)
{
    ifstream streamFile;
    streamFile.open(fileName.c_str());

    // Verifica se o arquivo foi aberto
    if (!streamFile.is_open())
    {
        cout << endl << "[ Erro ]: Não foi possível abrir o arquivo da instância" << endl;
    }
    else
    {
        // Conta as seções que foram lidas
        int sectionRead = 0;

        cout << "===== Lendo instância do CVRP =====" << endl << endl;

        CVRPInstance* instance = new CVRPInstance();

        string txtLine;

        // Lê linha por linha do arquivo
        while (getline(streamFile, txtLine))
        {
            // Verifica se a linha lida é igual a seção correspondente
            if(strcmp(txtLine.c_str(), string(NODE_COUNT_SECTION).c_str()) == 0)
            {
                cout << "Section: " << txtLine << endl;
                int nodeCount;
                streamFile >> nodeCount;
                instance->setVerticeCount(nodeCount);
                cout << "Quantidade de vértices: " << nodeCount << endl << endl;

                sectionRead++;
            }
            else if(strcmp(txtLine.c_str(), string(VEHICLE_CAP_SECTION).c_str()) == 0)
            {
                cout << "Section: " << txtLine << endl;
                float vehicleCapacity;
                streamFile >> vehicleCapacity;
                instance->setVehicleCapacity(vehicleCapacity);

                cout << "Capacidade do veículo: " << vehicleCapacity << endl << endl;

                sectionRead++;
            }
            else if(strcmp(txtLine.c_str(), string(NODE_COORD_SECTION).c_str()) == 0)
            {
                cout << "Section: " << txtLine << endl << endl;

                int nodeId;
                float nodeCoordX;
                float nodeCoordY;

                // Lê as próximas linhas até o fim da sessão
                while(getline(streamFile, txtLine) && (strcmp(txtLine.c_str(), string(END_SECTION).c_str())) != 0)
                {
                    stringstream streamLine(txtLine);

                    // Lê as informações (id X Y) da linha
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

                // Lê as próximas linhas até o fim da sessão
                while(getline(streamFile, txtLine) && (strcmp(txtLine.c_str(), string(END_SECTION).c_str())) != 0)
                {
                    stringstream streamLine(txtLine);

                    // Lê as informações da linha (id demanda)
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

        // Verifica se todas as seções foram lidas
        if(sectionRead < 5)
        {
            instance = NULL;
            cout << "[ Erro ]: Não foi possível ler todas as seções da instância!" << endl << endl;
        }

        cout << "===== END FILE =====" << endl << endl;

        streamFile.close();

        return instance;
    }

    return NULL;
}
