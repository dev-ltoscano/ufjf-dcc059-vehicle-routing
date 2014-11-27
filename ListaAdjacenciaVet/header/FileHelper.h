#ifndef FILEHELPER_H_INCLUDED
#define FILEHELPER_H_INCLUDED

#include "Helper.h"
#include "grafo/ListaAdjacenciaVet.h"

#include <fstream>

using namespace std;

class FileHelper : public Helper
{
    private:

    public:
        static void writeGraphInfoFile(ListaAdjacenciaVet *grafo, FloydWarshall floyd);
};

#endif // FILEHELPER_H_INCLUDED
