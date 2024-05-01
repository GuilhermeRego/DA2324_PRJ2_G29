#ifndef DA2324_PRJ2_G29_DATAMANAGER_H
#define DA2324_PRJ2_G29_DATAMANAGER_H

#include "Graph.h"

using namespace std;


class DataManager {
    public:
        DataManager();
        void readToy(string dataset, string csv);
    private:
        Graph<int> graph;
};

#endif
