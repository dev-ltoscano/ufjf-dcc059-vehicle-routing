#ifndef FILEHELPER_H_INCLUDED
#define FILEHELPER_H_INCLUDED

#include "heuristic/CVRPInstance.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

// Constantes para a leitura das seções do arquivo da instância. Windows e Linux
#ifdef _WIN32

#define NODE_COUNT_SECTION          "NODE_COUNT_SECTION"
#define VEHICLE_CAP_SECTION         "VEHICLE_CAP_SECTION"
#define NODE_COORD_SECTION          "NODE_COORD_SECTION"
#define NODE_DEMAND_SECTION         "NODE_DEMAND_SECTION"
#define NODE_BASE_SECTION           "NODE_BASE_SECTION"
#define END_SECTION                 "END_SECTION"
#define END_FILE                    "END_FILE"

#else

#define NODE_COUNT_SECTION          "NODE_COUNT_SECTION\r"
#define VEHICLE_CAP_SECTION         "VEHICLE_CAP_SECTION\r"
#define NODE_COORD_SECTION          "NODE_COORD_SECTION\r"
#define NODE_DEMAND_SECTION         "NODE_DEMAND_SECTION\r"
#define NODE_BASE_SECTION           "NODE_BASE_SECTION\r"
#define END_SECTION                 "END_SECTION\r"
#define END_FILE                    "END_FILE\r"

#endif

using namespace std;

/**
*   Classe para a leitura de arquivos
**/
class FileHelper
{
    public:
        // Faz a leitura do arquivo de uma instância do problema CVRP
        static shared_ptr<CVRPInstance> readInstance(string fileName);
};

#endif // FILEHELPER_H_INCLUDED
