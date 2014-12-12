#include "../header/FileHelper.h"

CVRPInstance* FileHelper::readInstance(string fileName)
{
    ifstream streamFile;
    streamFile.open(fileName.c_str());

    if (!streamFile.is_open())
    {
        cout << endl << "[ Erro ]: N�o foi poss�vel abrir o arquivo da inst�ncia" << endl;
    }
    else
    {
        cout << "===== Lendo inst�ncia do CVRP =====" << endl << endl;

        CVRPInstance *instance = new CVRPInstance();

        string txtLine;
        while (getline(streamFile, txtLine))
        {
            if(txtLine == "NODE_COUNT_SECTION")
            {
                cout << "Section: " << txtLine << endl;
                int nodeCount;
                streamFile >> nodeCount;
                instance->setVerticeCount(nodeCount);
                cout << "Quantidade de v�rtices: " << nodeCount << endl << endl;
            }
            else if(txtLine == "VEHICLE_CAP_SECTION")
            {
                cout << "Section: " << txtLine << endl;
                float vehicleCapacity;
                streamFile >> vehicleCapacity;
                instance->setVehicleCapacity(vehicleCapacity);

                cout << "Capacidade do ve�culo: " << vehicleCapacity << endl << endl;
            }
            else if(txtLine == "NODE_COORD_SECTION")
            {
                cout << "Section: " << txtLine << endl << endl;

                int nodeId;
                float nodeCoordX;
                float nodeCoordY;

                while(getline(streamFile, txtLine) && (txtLine != "END_SECTION"))
                {
                    stringstream streamLine(txtLine);

                    while(streamLine >> nodeId >> nodeCoordX >> nodeCoordY)
                    {
                        cout << "Id: " << nodeId << " -- X: " << nodeCoordX << " -- Y: " << nodeCoordY << endl;
                        instance->addVerticePoint(nodeId, new Point(nodeCoordX, nodeCoordY));
                    }
                }

                cout << endl;
            }
            else if(txtLine == "NODE_DEMAND_SECTION")
            {
                cout << "Section: " << txtLine << endl << endl;

                int nodeId;
                float nodeWeight;

                while(getline(streamFile, txtLine) && (txtLine != "END_SECTION"))
                {
                    stringstream streamLine(txtLine);

                    while(streamLine >> nodeId >> nodeWeight)
                    {
                        cout << "Id: " << nodeId << " -- Demanda: " << nodeWeight << endl;
                        instance->addVerticeDemand(nodeId, nodeWeight);
                    }
                }

                cout << endl;
            }
            else if(txtLine == "NODE_BASE_SECTION")
            {
                cout << "Section: " << txtLine << endl;
                int base;
                streamFile >> base;
                instance->setVerticeBase(base);
                cout << "Base: " << base << endl << endl;
            }
        }

        cout << "===== END FILE =====" << endl << endl;

        return instance;
    }

    return NULL;
}





void FileHelper::writeGraphInfoFile(ListaAdjacenciaVet *grafo, Floyd floyd)
{
    ofstream weightFile;
    weightFile.open("weights.txt");

    if(weightFile.is_open())
    {
        weightFile << "=== Informa��es do Grafo ===" << endl;
        weightFile << "Quantidade de v�rtices: " << grafo->getVerticeCount() << endl;
        weightFile << "Quantidade de adjac�ncias: " << grafo->getAdjacenciaCount() << endl;
        weightFile << "Conexo: " << grafo->isConexo() << endl;
        weightFile << "Componentes: " << grafo->compConexaCount() << endl;
        weightFile << "============================" << endl << endl;

        for(int i = 0; i < grafo->getVerticeCount(); i++)
        {
            for(int j = 0; j < grafo->getVerticeCount(); j++)
            {
                weightFile << "============================" << endl;
                weightFile << "i: " << i << " | Grau: " << grafo->getVerticeGrau(i) << endl;
                weightFile << "j: " << j << " | Grau: " << grafo->getVerticeGrau(j) << endl;
                weightFile << FloydWarshall::getShortestStringPath(floyd, i, j);
                weightFile << "Custo do caminho: " << floyd.dij[i][j] << endl;
                weightFile << "============================" << endl << endl;
            }
        }

        weightFile.close();
        cout << "Arquivo com a matriz de custos do grafo foi salvo!" << endl;
    }
    else
    {
        cout << "[ ERRO ]: N�o foi poss�vel criar o arquivo da matriz de custos do grafo" << endl;
    }
}
