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
        cout << "3 - Exit" << endl;
        cin >> choice;

        switch (choice) {
            case 1:
                runBacktrackingAlgorithm();
                break;
            case 2:
                dataManager.realWorldGraphTAH();
                break;
            case 3:
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
    return INT_MAX; // Return a large value if edge not found (assuming no negative weights)
}


void backtrack(const Graph<int>& graph, vector<int>& tour, vector<bool>& visited, double currentCost, double& minCost, vector<int>& bestTour) {
    // Base case: If all nodes have been visited, update minCost if currentCost is less
    if (tour.size() == graph.getVertexSet().size()) {
        minCost = min(minCost, currentCost);
        if (minCost == currentCost) {
            bestTour = tour; // Update the best tour
        }
        return;
    }

    // Try visiting each unvisited node and recursively find the minimum cost tour
    for (int i = 0; i < graph.getVertexSet().size(); ++i) {
        if (!visited[i]) {
            int lastNode = tour.back();
            if (hasEdge(graph.findVertex(lastNode), graph.findVertex(i))) {
                tour.push_back(i);
                visited[i] = true;
                backtrack(graph, tour, visited, currentCost + getEdgeWeight(graph, lastNode, i), minCost, bestTour); // Assuming weight = 1 for each edge
                // Backtrack
                tour.pop_back();
                visited[i] = false;
            }
        }
    }
}

// Function to calculate the TSP using backtracking algorithm
double Menu::calculateTSPBacktracking(const Graph<int>& graph, vector<int>& bestTour) {
    // Initialize variables
    double minCost = INT_MAX;
    int startNode = 0; // Assuming starting and ending node is 0
    vector<int> tour = {startNode}; // Initialize tour with starting node
    vector<bool> visited(graph.getVertexSet().size(), false); // Mark all nodes as unvisited
    visited[startNode] = true; // Mark the starting node as visited

    // Call the backtracking function
    backtrack(graph, tour, visited, 0.0, minCost, bestTour);

    return minCost;
}

void Menu::runBacktrackingAlgorithm() {
    Graph<int> graph = dataManager.getGraph();

    if (graph.getVertexSet().size() != 0) {
        vector<int> bestTour; // To store the best tour
        double minCost = calculateTSPBacktracking(graph, bestTour);

        // Calculate the weight of the last edge (from the last vertex to 0)
        double lastEdgeWeight = getEdgeWeight(graph, bestTour.back(), 0);

        // Add the weight of the last edge to the tour cost
        minCost += lastEdgeWeight;

        cout << "Minimum cost tour using backtracking algorithm: " << minCost << endl;
        cout << "Tour path: ";
        for (size_t i = 0; i < bestTour.size() - 1; ++i) {
            cout << bestTour[i] << " -> ";
        }
        cout << bestTour.back() << " -> 0"; // Print the last vertex and back to 0
        cout << endl;
    } else {
        cout << "Graph data is empty. Please parse the CSV file first.\n";
    }
}

