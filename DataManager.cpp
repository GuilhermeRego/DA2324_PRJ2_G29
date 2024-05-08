#include "DataManager.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <unordered_set>
#include <list>
#include "Node.h"

using namespace std;

// Parse of data from csv files

DataManager::DataManager() {
    start();
}

void DataManager::start() {
    string dataset, csv, selectedGraph, edges;
    cout << "Choose the dataset: " << endl;
    cout << "1 - Toy-Graphs" << endl;
    cout << "2 - Extra_Fully_Connected_Graphs" << endl;
    cout << "3 - Real-world Graphs" << endl;
    cin >> dataset;
    if (dataset == "1") {
        dataset = "Toy-Graphs";
        cout << "Enter the csv file: " << endl;
        cout << "1 - shipping.csv" << endl;
        cout << "2 - stadiums.csv" << endl;
        cout << "3 - tourism.csv" << endl;
        cin >> csv;
        if (csv == "1") {
            csv = "shipping.csv";
        }
        else if (csv == "2") {
            csv = "stadiums.csv";
        }
        else if (csv == "3") {
            csv = "tourism.csv";
        }
        else {
            cout << "Invalid csv file" << endl;
        }
        readToy(dataset, csv);
    }
    else if (dataset == "2") {
        cout << "Choose the graph's number of edges between the following options:" << endl;
        int options[12] = {25, 50, 75, 100, 200, 300, 400, 500, 600, 700, 800, 900};
        for (int i = 0; i < 12; i++) {
            cout << i + 1 << " - " << options[i] << " edges" << endl;
        }
        while (cin >> edges) {
            try {
                if (stoi(edges) < 1 || stoi(edges) > 12) {
                    cout << "Invalid number of edges" << endl;
                }
                else {
                    edges = to_string(options[stoi(edges) - 1]);
                    break;
                }
            }
            catch (invalid_argument& e) {
                cout << "Invalid input" << endl;
            }
        }
        readExtra(edges);
    }
    else if (dataset == "3") {
        dataset = "Real-world Graphs";
        cout << "Enter the graph:" << endl;
        cout << "1 - graph1" << endl;
        cout << "2 - graph2" << endl;
        cout << "3 - graph3" << endl;
        cin >> selectedGraph;
        if (selectedGraph == "1") {
            selectedGraph = "graph1";
        }
        else if (selectedGraph == "2") {
            selectedGraph = "graph2";
        }
        else if (selectedGraph == "3") {
            selectedGraph = "graph3";
        }
        else {
            cout << "Invalid graph" << endl;
        }
        readRealWorld(dataset, selectedGraph);
    }
    else {
        cout << "Invalid dataset" << endl;
    }
}

void DataManager::readToy(const string& dataset, const string& csv) {
    string path = "../data/" + dataset + "/" + csv;
    ifstream file(path);
    string line;
    directory = dataset;
    subDirectory = csv;
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
    }
    else {
        getline(file, line);
        while (getline(file, line)) {
            string source, dest, weight;
            istringstream iss(line);
            getline(iss, source, ',');
            getline(iss, dest, ',');
            getline(iss, weight, ',');
            string temp;
            getline(iss, temp, ',');
            getline(iss, temp, ',');
            graph.addVertex(stoi(source));
            graph.addVertex(stoi(dest));
            graph.addEdge(stoi(source), stoi(dest), stod(weight));
            graph.addEdge(stoi(dest), stoi(source), stod(weight));
        }
    }
    if (graph.getVertexSet().empty()) cout << "Error reading dataset" << endl;
    else cout << "Dataset read successfully" << endl;
}

void DataManager::readExtra(const string& edges) {
    directory = "Extra_Fully_Connected_Graphs";
    subDirectory = "edges_" + edges + ".csv";
    string nodesPath = "../data/Extra_Fully_Connected_Graphs/nodes.csv";
    ifstream file(nodesPath);
    string line;
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
    }
    else {
        getline(file, line);
        while (getline(file, line)) {
            string id, longitude, latitude;
            istringstream iss(line);
            getline(iss, id, ',');
            getline(iss, longitude, ',');
            getline(iss, latitude, ',');
            nodes.insert(make_pair(stoi(id), Node(stoi(id), stod(longitude), stod(latitude))));
        }
    }

    string edgesPath = "../data/Extra_Fully_Connected_Graphs/edges_" + edges + ".csv";
    ifstream file2(edgesPath);
    if (!file2.is_open()) {
        cout << "Error opening file" << endl;
    }
    else {
        while (getline(file2, line)) {
            string source, dest, weight;
            istringstream iss(line);
            getline(iss, source, ',');
            getline(iss, dest, ',');
            getline(iss, weight, ',');
            graph.addVertex(stoi(source));
            graph.addVertex(stoi(dest));
            graph.addEdge(stoi(source), stoi(dest), stod(weight));
            graph.addEdge(stoi(dest), stoi(source), stod(weight));
        }
    }
    if (graph.getVertexSet().empty()) cout << "Error reading dataset" << endl;
    else cout << "Dataset read successfully" << endl;
}

void DataManager::readRealWorld(const string& dataset, const string& selectedGraph) {
    string path = "../data/" + dataset + "/" + selectedGraph + "/nodes.csv";
    ifstream file(path);
    string line;
    directory = dataset;
    subDirectory = selectedGraph;
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
    }
    else {
        getline(file, line);
        while (getline(file, line)) {
            string id, longitude, latitude;
            istringstream iss(line);
            getline(iss, id, ',');
            getline(iss, longitude, ',');
            getline(iss, latitude, ',');
            nodes.insert(make_pair(stoi(id), Node(stoi(id), stod(longitude), stod(latitude))));
        }
    }
    path = "../data/" + dataset + "/" + selectedGraph + "/edges.csv";
    ifstream file2(path);
    if (!file2.is_open()) {
        cout << "Error opening file" << endl;
    }
    else {
        getline(file2, line);
        while (getline(file2, line)) {
            string source, dest, weight;
            istringstream iss(line);
            getline(iss, source, ',');
            getline(iss, dest, ',');
            getline(iss, weight, ',');
            graph.addVertex(stoi(source));
            graph.addVertex(stoi(dest));
            graph.addEdge(stoi(source), stoi(dest), stod(weight));
            graph.addEdge(stoi(dest), stoi(source), stod(weight));
        }
    }
    if (graph.getVertexSet().empty()) cout << "Error reading dataset" << endl;
    else cout << "Dataset read successfully" << endl;
}

double haversineDistance(double lat1, double lon1, double lat2, double lon2);
bool hasEdge(const Vertex<int>* source, const Vertex<int>* dest);

void DataManager::completeGraph(Graph<int>& graph) {
    for (auto node1 : graph.getVertexSet()) {
        for (auto edge : node1->getAdj()) {
            auto node2 = edge->getDest();
            if (!hasEdge(node2, node1) || !hasEdge(node1, node2)) {
                double weight = haversineDistance(nodes.at(node1->getInfo()).getLatitude(), nodes.at(node1->getInfo()).getLongitude(),
                                                  nodes.at(node2->getInfo()).getLatitude(), nodes.at(node2->getInfo()).getLongitude());
                graph.addEdge(node2->getInfo(), node1->getInfo(), weight);
            }

        }
    }
    cout << "Graph completed successfully" << endl;
}

void DataManager::clean() {
    for (auto vertex : graph.getVertexSet()) {
        graph.removeVertex(vertex->getInfo());
    }
    if (!graph.getVertexSet().empty() || graph.getNumVertex() != 0) {
        cout << "Error cleaning graph" << endl;
        exit(1);
    }
    nodes.clear();
    directory = "";
    subDirectory = "";
}






// Useful functions for algorithms

void DataManager::printTourCost(vector<int>& tour) {
    tour.push_back(tour[0]);
    cout << "Tour: ";
    for (int i = 0; i < tour.size(); i++) {
        cout << tour[i];
        if (i != tour.size() - 1)
            cout << " -> ";
    }
    cout << endl;

    double cost = 0;
    bool found;
    for (int i = 0; i < tour.size() - 2; i++) {
        found = false;
        auto vertex1 = graph.findVertex(tour[i]);
        auto vertex2 = graph.findVertex(tour[i + 1]);
        for (auto edge : vertex1->getAdj()) {
            if (edge->getDest()->getInfo() == vertex2->getInfo()) {
                cout << "Edge: " << vertex1->getInfo() << " -> " << vertex2->getInfo() << " Weight: " << edge->getWeight() << endl;
                cost += edge->getWeight();
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Edge not found" << endl;
        }
    }
    found = false;
    auto first = graph.findVertex(tour[0]);
    auto last = graph.findVertex(tour[tour.size() - 2]);
    for (auto edge : last->getAdj()) {
        if (edge->getDest()->getInfo() == first->getInfo()) {
            cout << "Edge: " << last->getInfo() << " -> " << first->getInfo() << " Weight: " << edge->getWeight() << endl;
            cost += edge->getWeight();
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Edge not found" << endl;
    }
    cout << "Tour minimum cost: " << cost << endl;
}

const double EARTH_RADIUS = 6371000; // Earth's radius in meters

double toRadians(double degree) {
    return degree * M_PI / 180.0;
}

double haversineDistance(double lat1, double lon1, double lat2, double lon2) {
    double radLat1 = toRadians(lat1);
    double radLon1 = toRadians(lon1);
    double radLat2 = toRadians(lat2);
    double radLon2 = toRadians(lon2);

    double deltaLat = radLat2 - radLat1;
    double deltaLon = radLon2 - radLon1;

    double a = sin(deltaLat / 2) * sin(deltaLat / 2) +
               cos(radLat1) * cos(radLat2) *
               sin(deltaLon / 2) * sin(deltaLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return EARTH_RADIUS * c; // Distance in meters
}

bool hasEdge(const Vertex<int>* source, const Vertex<int>* dest) {
    for (const Edge<int>* edge : source->getAdj()) {
        if (edge->getDest() == dest) {
            return true;
        }
    }
    return false;
}

double getEdgeWeight(const Graph<int>& graph, int source, int dest) {
    for (const Edge<int>* edge : graph.findVertex(source)->getAdj()) {
        if (edge->getDest()->getInfo() == dest) {
            return edge->getWeight();
        }
    }
    return INT_MAX;
}

// Backtracking Algorithm

void backtrack(const Graph<int>& graph, vector<int>& tour, vector<bool>& visited, double currentCost, double& minCost, vector<int>& bestTour) {

    if (tour.size() == graph.getVertexSet().size()) {
        minCost = min(minCost, currentCost);
        if (minCost == currentCost) {
            bestTour = tour;
        }
        return;
    }

    for (int i = 0; i < graph.getVertexSet().size(); ++i) {
        if (!visited[i]) {
            int lastNode = tour.back();
            if (hasEdge(graph.findVertex(lastNode), graph.findVertex(i))) {
                tour.push_back(i);
                visited[i] = true;
                backtrack(graph, tour, visited, currentCost + getEdgeWeight(graph, lastNode, i), minCost, bestTour);

                tour.pop_back();
                visited[i] = false;
            }
        }
    }
}

void DataManager::calculateTSPBacktracking(const Graph<int>& graph, vector<int>& bestTour) {
    double minCost = INT_MAX;
    int startNode = 0;
    vector<int> tour = {startNode};
    vector<bool> visited(graph.getVertexSet().size(), false);
    visited[startNode] = true;
    backtrack(graph, tour, visited, 0.0, minCost, bestTour);
}

void DataManager::runBacktrackingAlgorithm(Graph<int> graph) {
    if (!graph.getVertexSet().empty()) {
        vector<int> bestTour;
        calculateTSPBacktracking(graph, bestTour);
        printTourCost(bestTour);
        cout << endl;
    }
    else {
        cout << "Graph data is empty. Please parse the CSV file first.\n";
    }
}






// Triangular Approximation Heuristic

void DataManager::TAH(Graph<int> graph) {
    auto mst = graph.primMST();

    vector<int> tour;
    unordered_set<int> visited;
    int startVertex = 0;
    dfsMST(startVertex, mst, visited, tour);
    printTourCost(tour);
}

void DataManager::dfsMST(int vertex, Graph<int>& mst, unordered_set<int>& visited, vector<int>& tour) {
    visited.insert(vertex);
    tour.push_back(vertex);
    for (auto adjEdge : mst.findVertex(vertex)->getAdj()) {
        auto neighbor = adjEdge->getDest()->getInfo();
        if (visited.find(neighbor) == visited.end()) {
            dfsMST(neighbor, mst, visited, tour);
        }
    }
}








// Other Heuristics

int findNearestNeighbor(const Graph<int>& graph, vector<bool>& visited, int currentVertex) {
    int nearestNeighbor = -1;
    double minDistance = numeric_limits<double>::max();
    const vector<Vertex<int>*>& vertices = graph.getVertexSet();

    for (size_t i = 0; i < vertices.size(); ++i) {
        if (!visited[i]) {
            double distance = getEdgeWeight(graph, currentVertex, (int) i);
            if (distance < minDistance) {
                minDistance = distance;
                nearestNeighbor = (int) i;
            }
        }
    }

    return nearestNeighbor;
}

vector<int> calculateTSPNearestNeighbor(const Graph<int>& graph) {
    const vector<Vertex<int>*>& vertices = graph.getVertexSet();
    int numVertices = (int) vertices.size();

    vector<bool> visited(numVertices, false);
    vector<int> tour;
    int currentVertex = 0;

    tour.push_back(currentVertex);
    visited[currentVertex] = true;

    while (tour.size() < numVertices) {

        int nearestNeighbor = findNearestNeighbor(graph, visited, currentVertex);

        if (nearestNeighbor == -1) {

            tour.pop_back();
            currentVertex = tour.back();
        } else {

            tour.push_back(nearestNeighbor);
            visited[nearestNeighbor] = true;
            currentVertex = nearestNeighbor;
        }
    }

    return tour;
}

void DataManager::runNearestNeighborHeuristic(Graph<int> graph) {

    if (!graph.getVertexSet().empty()) {
        vector<int> tour = calculateTSPNearestNeighbor(graph);
        printTourCost(tour);
    }
    else {
        cout << "Graph data is empty. Please parse the CSV file first.\n";
    }
}






// The TSP in the Real-World
void DataManager::printTourCostModified(vector<int>& tour) {
    cout << "Tour: ";
    for (int i = 0; i < tour.size(); i++) {
        cout << tour[i];
        if (i != tour.size() - 1)
            cout << " -> ";
    }
    // Add the edge from the last vertex to the start vertex
    cout << " -> " << tour[0] << endl;

    double cost = 0;
    bool found;
    for (int i = 0; i < tour.size() - 1; i++) {
        found = false;
        auto vertex1 = graph.findVertex(tour[i]);
        auto vertex2 = graph.findVertex(tour[i + 1]);
        for (auto edge : vertex1->getAdj()) {
            if (edge->getDest()->getInfo() == vertex2->getInfo()) {
                cout << "Edge: " << vertex1->getInfo() << " -> " << vertex2->getInfo() << " Weight: " << edge->getWeight() << endl;
                cost += edge->getWeight();
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Edge not found" << endl;
        }
    }
    // Check for the edge from the last vertex to the start vertex
    found = false;
    auto first = graph.findVertex(tour[0]);
    auto last = graph.findVertex(tour[tour.size() - 1]);
    for (auto edge : last->getAdj()) {
        if (edge->getDest()->getInfo() == first->getInfo()) {
            cout << "Edge: " << last->getInfo() << " -> " << first->getInfo() << " Weight: " << edge->getWeight() << endl;
            cost += edge->getWeight();
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Edge not found" << endl;
    }
    cout << "Tour cost: " << cost << endl;
}

void dfsTSP(int vertex, Graph<int>& graph, unordered_set<int>& visited, vector<int>& tour, vector<int>& bestTour, double& minCost, double currentCost) {
    visited.insert(vertex);
    tour.push_back(vertex);
    if (visited.size() == graph.getNumVertex()) {
        if (hasEdge(graph.findVertex(tour.back()), graph.findVertex(tour.front()))) {
            currentCost += getEdgeWeight(graph, tour.back(), tour.front());
            if (currentCost < minCost) {
                minCost = currentCost;
                bestTour = tour;
            }
        }
    } else {
        for (auto adjEdge : graph.findVertex(vertex)->getAdj()) {
            auto neighbor = adjEdge->getDest()->getInfo();
            if (visited.find(neighbor) == visited.end()) {
                dfsTSP(neighbor, graph, visited, tour, bestTour, minCost, currentCost + adjEdge->getWeight());
            }
        }
    }
    visited.erase(vertex);
    tour.pop_back();
}

void DataManager::runModifiedDFS(Graph<int> graph, int startVertex) {
    if (graph.getVertexSet().empty()) {
        cout << "Graph data is empty. Please parse the CSV file first.\n";
        return;
    }

    unordered_set<int> visited;
    vector<int> tour;
    vector<int> bestTour;
    double minCost = numeric_limits<double>::max();
    dfsTSP(startVertex, graph, visited, tour, bestTour, minCost, 0);

    if (!bestTour.empty() && bestTour.front() == startVertex &&
        hasEdge(graph.findVertex(bestTour.back()), graph.findVertex(bestTour.front()))) {
        printTourCostModified(bestTour);
    } else {
        cout << "No path exists that returns to the origin and visits all nodes.\n";
    }
}