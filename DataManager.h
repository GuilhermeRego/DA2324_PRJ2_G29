#ifndef DA2324_PRJ2_G29_DATAMANAGER_H
#define DA2324_PRJ2_G29_DATAMANAGER_H

#include "Graph.h"

using namespace std;


class DataManager {
    public:
        DataManager();
        void readToy(string dataset, string csv);
        string getcsv(){
            return csv_;
        }
    private:
        Graph<int> graph;
        string csv_;
};

#endif
