#include "../header/FileHelper.h"

void FileHelper::writeGraphInfoFile(ListaAdjacenciaVet *grafo, FloydWarshall floyd)
{
    ofstream weightFile;
    weightFile.open("weights.txt");

    if(weightFile.is_open())
    {
        weightFile << "=== Informações do Grafo ===" << endl;
        weightFile << "Quantidade de vértices: " << grafo->getVerticeCount() << endl;
        weightFile << "Quantidade de adjacências: " << grafo->getAdjacenciaCount() << endl;
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
                weightFile << Helper::printShortestStringPath(floyd, i, j);
                weightFile << "Custo do caminho: " << floyd.dij[i][j] << endl;
                weightFile << "============================" << endl << endl;
            }
        }

        weightFile.close();
        cout << "Arquivo com a matriz de custos do grafo foi salvo!" << endl;
    }
    else
    {
        cout << "[ ERRO ]: Não foi possível criar o arquivo da matriz de custos do grafo" << endl;
    }
}
