#ifndef FILEHELPER_H_INCLUDED
#define FILEHELPER_H_INCLUDED

#include "heuristic/FloydWarshall.h"

#include "heuristic/CVRPInstance.h"
#include "grafo/ListaAdjacenciaVet.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class FileHelper : public Helper
{
    private:

    public:
        static CVRPInstance* readInstance(string fileName);


        static void writeGraphInfoFile(ListaAdjacenciaVet *grafo, Floyd floyd);
};

#endif // FILEHELPER_H_INCLUDED
