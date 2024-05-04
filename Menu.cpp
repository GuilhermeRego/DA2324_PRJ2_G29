#include "Menu.h"

Menu::Menu() {
    init();
}

void Menu::init() {
    mainMenu();
}


void Menu::mainMenu() {
    if (dataManager.getDataset() == "Toy-Graphs") {
        int choice;
        cout << "\n===== Main Menu =====" << endl;
        cout << "1 - Backtracking Algorithm" << endl;
        cout << "2 - Triangular Approximation Heuristic" << endl;
        cout << "3 - Other Heuristics" << endl;
        cout << "4 - Exit" << endl;
        cin >> choice;

        switch (choice) {
            case 1:
                runBacktrackingAlgorithm();
                break;
            case 2:
                dataManager.toyGraphTAH();
                break;
            case 3:
                runNearestNeighborHeuristic();
                break;
            case 4:
                cout << "\nGoodbye!\n";
                exit(0);
            default:
                cout << "Invalid input, try again\n";
                mainMenu();
                break;
        }
    }
    else if(dataManager.getDataset() == "Real-world Graphs") {
        int choice;
        cout << "\n===== Main Menu =====" << endl;
        cout << "1 - Backtracking Algorithm" << endl;
        cout << "2 - Triangular Approximation Heuristic" << endl;
        cout << "3 - Other Heuristics" << endl;
        cout << "4- Exit" << endl;
        cin >> choice;

        switch (choice) {
            case 1:
                runBacktrackingAlgorithm();
                break;
            case 2:
                dataManager.realWorldGraphTAH();
                break;
            case 3:
                runNearestNeighborHeuristic();
                break;
            case 4:
                cout << "\nGoodbye!\n";
                exit(0);
            default:
                cout << "Invalid input, try again\n";
                mainMenu();
                break;
        }
    }
    mainMenu();
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


double Menu::calculateTSPBacktracking(const Graph<int>& graph, vector<int>& bestTour) {

    double minCost = INT_MAX;
    int startNode = 0;
    vector<int> tour = {startNode};
    vector<bool> visited(graph.getVertexSet().size(), false);
    visited[startNode] = true;


    backtrack(graph, tour, visited, 0.0, minCost, bestTour);

    return minCost;
}

void Menu::runBacktrackingAlgorithm() {
    Graph<int> graph = dataManager.getGraph();

    if (graph.getVertexSet().size() != 0) {
        vector<int> bestTour;
        double minCost = calculateTSPBacktracking(graph, bestTour);


        double lastEdgeWeight = getEdgeWeight(graph, bestTour.back(), 0);


        minCost += lastEdgeWeight;

        cout << "Minimum cost tour using backtracking algorithm: " << minCost << endl;
        cout << "Tour path: ";
        for (size_t i = 0; i < bestTour.size() - 1; ++i) {
            cout << bestTour[i] << " -> ";
        }
        cout << bestTour.back() << " -> 0";
        cout << endl;
    } else {
        cout << "Graph data is empty. Please parse the CSV file first.\n";
    }
}



int findNearestNeighbor(const Graph<int>& graph, vector<bool>& visited, int currentVertex) {
    int nearestNeighbor = -1;
    double minDistance = numeric_limits<double>::max();
    const vector<Vertex<int>*>& vertices = graph.getVertexSet();


    for (size_t i = 0; i < vertices.size(); ++i) {
        if (!visited[i]) {
            double distance = getEdgeWeight(graph, currentVertex, i);
            if (distance < minDistance) {
                minDistance = distance;
                nearestNeighbor = i;
            }
        }
    }

    return nearestNeighbor;
}


vector<int> calculateTSPNearestNeighbor(const Graph<int>& graph) {
    const vector<Vertex<int>*>& vertices = graph.getVertexSet();
    int numVertices = vertices.size();


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

    tour.push_back(0);

    return tour;
}


double calculateTourCost(const Graph<int>& graph, const vector<int>& tour) {
    double cost = 0;
    for (size_t i = 0; i < tour.size() - 1; ++i) {
        int source = tour[i];
        int dest = tour[i + 1];
        cost += getEdgeWeight(graph,source, dest);
    }

    return cost;
}

void Menu::runNearestNeighborHeuristic() {
    Graph<int> graph = dataManager.getGraph();

    if (graph.getVertexSet().size() != 0) {
        vector<int> tour = calculateTSPNearestNeighbor(graph);
        double tourCost = calculateTourCost(graph, tour);
        cout << "TSP Tour using Nearest Neighbor Heuristic:" << endl;
        for (int vertex : tour) {
            cout << vertex << " ";
        }
        cout << endl;
        cout << "Tour Cost: " << tourCost << endl;
    } else {
        cout << "Graph data is empty. Please parse the CSV file first.\n";
    }
}


