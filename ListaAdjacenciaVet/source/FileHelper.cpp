#include "../header/FileHelper.h"

shared_ptr<CVRPInstance> FileHelper::readInstance(string fileName)
{
    ifstream streamFile;
    streamFile.open(fileName.c_str());

    if (!streamFile.is_open())
    {
        cout << endl << "[ Erro ]: Não foi possível abrir o arquivo da instância" << endl;
    }
    else
    {
        int sectionRead = 0;

        cout << "===== Lendo instância do CVRP =====" << endl << endl;

        shared_ptr<CVRPInstance> instance = make_shared<CVRPInstance>();

        string txtLine;

        while (getline(streamFile, txtLine))
        {
//            cout << "Line: " << (txtLine.c_str() == string("NODE_COUNT_SECTION\r")) << endl;

//            cout << "Equals: " << strcmp(txtLine.c_str(), string("NODE_COORD_SECTION").c_str()) << endl;

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

                while(getline(streamFile, txtLine) && (strcmp(txtLine.c_str(), string(END_SECTION).c_str())) != 0)
                {
                    stringstream streamLine(txtLine);

                    while(streamLine >> nodeId >> nodeCoordX >> nodeCoordY)
                    {
                        cout << "Id: " << nodeId << " -- X: " << nodeCoordX << " -- Y: " << nodeCoordY << endl;
                        instance->addVerticePoint(nodeId, make_shared<Point>(nodeCoordX, nodeCoordY));
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

                while(getline(streamFile, txtLine) && (strcmp(txtLine.c_str(), string(END_SECTION).c_str())) != 0)
                {
                    stringstream streamLine(txtLine);

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

        if(sectionRead < 5)
        {
            instance = NULL;
            cout << "[ Erro ]: Não foi possível ler todas as seções da instância!" << endl << endl;
        }

        cout << "===== END FILE =====" << endl << endl;

        return instance;
    }

    return NULL;
}
