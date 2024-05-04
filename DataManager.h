#ifndef DA2324_PRJ2_G29_DATAMANAGER_H
#define DA2324_PRJ2_G29_DATAMANAGER_H

#include <unordered_map>
#include <unordered_set>
#include "Graph.h"
#include "Node.h"

using namespace std;


class DataManager {

    public:
        DataManager();
        void readToy(const string& dataset, const string& csv);
        void readRealWorld(const string& basicString, const string& basicString1);

        string getCsv() { return csv_; }
        string getDataset() { return dataset_; }
        unordered_map<int, Node> getNodes() { return nodes; }
        Graph<int> getGraph() {return graph;}

        static void calculateTSPBacktracking(const Graph<int>& graph, vector<int> &bestTour);
        void runBacktrackingAlgorithm();
        void runNearestNeighborHeuristic();

        void toyGraphTAH();
        void realWorldGraphTAH();
        void completeGraph();
        void printTourCost(vector<int>& tour);
        void dfsMST(int vertex, Graph<int> &mst, unordered_set<int> &visited, vector<int> &tour);

    private:
            Graph<int> graph;
            string dataset_;
            string csv_;
            unordered_map<int, Node> nodes;
};

#endif
