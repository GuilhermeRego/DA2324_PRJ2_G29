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
        void readExtra(const string &edges);
        void readRealWorld(const string& basicString, const string& basicString1);

        string getCsv() { return subDirectory; }
        string getDataset() { return directory; }
        unordered_map<int, Node> getNodes() { return nodes; }
        Graph<int> getGraph() {return graph;}

        static void calculateTSPBacktracking(const Graph<int>& graph, vector<int> &bestTour);
        void runBacktrackingAlgorithm(Graph<int> graph);
        void runNearestNeighborHeuristic(Graph<int> graph);

        void TAH(Graph<int> graph);
        void completeGraph(Graph<int> graph);
        void dfsMST(int vertex, Graph<int> &mst, unordered_set<int> &visited, vector<int> &tour);


        void printTourCost(vector<int> &tour);

        void start();
        void clean();

        void runModifiedDFS(Graph<int> graph, int startVertex);

    private:
            Graph<int> graph;
            string directory;
            string subDirectory;
            unordered_map<int, Node> nodes;


    void printTourCostModified(vector<int> &tour);
};

#endif