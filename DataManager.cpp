#include "DataManager.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <unordered_set>
#include "Node.h"

using namespace std;

// Parse of data from csv files

DataManager::DataManager() {
    string dataset, csv, selectedGraph;
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
        cout << "Not implemented yet" << endl;
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
    dataset_ = dataset;
    csv_ = csv;
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
    cout << "Dataset read successfully" << endl;
}

void DataManager::readRealWorld(const string& dataset, const string& selectedGraph) {
    string path = "../data/" + dataset + "/" + selectedGraph + "/nodes.csv";
    ifstream file(path);
    string line;
    dataset_ = dataset;
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
            graph.addEdge(stoi(source), stoi(dest), stod(weight));
            graph.addEdge(stoi(dest), stoi(source), stod(weight));
        }
    }
    completeGraph();
    cout << "Dataset read successfully" << endl;
}

double haversineDistance(double lat1, double lon1, double lat2, double lon2);

void DataManager::completeGraph() {
    bool found = false;
    for (auto node1: graph.getVertexSet()) {
        for (auto node2: graph.getVertexSet()) {
            if (node1->getInfo() != node2->getInfo()) {
                for (auto adjEdgeNode1: node1->getAdj()) {
                    if (adjEdgeNode1->getDest()->getInfo() == node2->getInfo()) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    double latitude1 = nodes.find(node1->getInfo())->second.getLatitude();
                    double longitude1 = nodes.find(node1->getInfo())->second.getLongitude();
                    double latitude2 = nodes.find(node2->getInfo())->second.getLatitude();
                    double longitude2 = nodes.find(node2->getInfo())->second.getLongitude();
                    double distance = haversineDistance(latitude1, longitude1, latitude2, longitude2);
                    graph.addEdge(node1->getInfo(), node2->getInfo(), distance);
                }
                found = false;
            }

        }
    }
}

// Useful functions for algorithms

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

// Triangular Approximation Heuristic

void DataManager::toyGraphTAH() {
    auto mst = graph.primMST();

    vector<int> tour;
    unordered_set<int> visited;
    int startVertex = 0;
    dfsMST(startVertex, mst, visited, tour);
    tour.push_back(startVertex);
    printTourCost(tour);
}

void DataManager::realWorldGraphTAH() {
    // TODO
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

void DataManager::printTourCost(const vector<int>& tour) {
    cout << "Tour: ";
    for (int i = 0; i < tour.size(); i++) {
        cout << tour[i];
        if (i != tour.size() - 1)
            cout << " -> ";
    }
    cout << endl;

    double cost = 0;
    for (int i = 0; i < tour.size() - 2; i++) {
        auto vertex1 = graph.findVertex(tour[i]);
        auto vertex2 = graph.findVertex(tour[i + 1]);
        for (auto edge : vertex1->getAdj()) {
            if (edge->getDest()->getInfo() == vertex2->getInfo()) {
                cout << "Edge: " << vertex1->getInfo() << " -> " << vertex2->getInfo() << " Weight: " << edge->getWeight() << endl;
                cost += edge->getWeight();
                break;
            }
        }
    }
    auto first = graph.findVertex(tour[0]);
    auto last = graph.findVertex(tour[tour.size() - 2]);
    for (auto edge : last->getAdj()) {
        if (edge->getDest()->getInfo() == first->getInfo()) {
            cout << "Edge: " << last->getInfo() << " -> " << first->getInfo() << " Weight: " << edge->getWeight()
                 << endl;
            cost += edge->getWeight();
            break;
        }
    }
    cout << "Tour minimum cost: " << cost << endl;
}
