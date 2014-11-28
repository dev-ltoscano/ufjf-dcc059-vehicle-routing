#ifndef FILEHELPER_H_INCLUDED
#define FILEHELPER_H_INCLUDED

#include "heuristic/FloydWarshall.h"
#include "grafo/ListaAdjacenciaVet.h"

#include <fstream>

using namespace std;

class FileHelper : public Helper
{
    private:

    public:
        static void writeGraphInfoFile(ListaAdjacenciaVet *grafo, Floyd floyd);
};

#endif // FILEHELPER_H_INCLUDED
