#include "Menu.h"
#include <chrono>
#include <stack>

bool isFullyConnected(const Graph<int>& graph);

Menu::Menu() {
    init();
}

void Menu::init() {
    mainMenu();
}

void Menu::mainMenu() {
    string choice;
    cout << "\nCurrent dataset: " << dataManager.getDataset() << " -> " << dataManager.getCsv();
    if (isFullyConnected(dataManager.getGraph())) cout << " (fully connected)" << endl;
    else cout << " (not fully connected)" << endl;
    cout << "\n===== Main Menu =====" << endl;
    cout << "1 - Backtracking Algorithm" << endl;
    cout << "2 - Triangular Approximation Heuristic (fully connected)" << endl;
    cout << "3 - Other Heuristics (fully connected)" << endl;
    cout << "4 - TSP Solver" << endl;
    cout << "5 - Graph's number of vertices and edges" << endl;
    cout << "6 - Complete the graph" << endl;
    cout << "7 - Change dataset" << endl;
    cout << "8 - Exit" << endl;
    cin >> choice;
    if (dataManager.getDataset() == "Toy-Graphs" || dataManager.getDataset() == "Extra_Fully_Connected_Graphs") {
        switch (choice[0]) {
            case '1': {
                auto start = chrono::high_resolution_clock::now();
                dataManager.runBacktrackingAlgorithm(dataManager.getGraph());
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
                printTime(duration);
                break;
            }
            case '2': {
                if (!isFullyConnected(dataManager.getGraph())) {
                    cout << "WARNING: The chosen csv file (" << dataManager.getCsv()
                         << ") is not fully connected and therefore the Triangular Approximation Heuristic may not work as expected\n";
                    char c = 0;
                    while (tolower(c) != 'y' && tolower(c) != 'n') {
                        cout << "Would you like to continue? (y/n)\n";
                        cin >> c;
                        c = tolower(c);
                        if (c == 'n') {
                            mainMenu();
                        }
                    }
                }
                auto start = chrono::high_resolution_clock::now();
                dataManager.TAH(dataManager.getGraph());
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
                printTime(duration);
                break;
            }
            case '3': {
                if (!isFullyConnected(dataManager.getGraph())) {
                    cout << "WARNING: The chosen csv file (" << dataManager.getCsv()
                         << ") is not fully connected and therefore the Nearest Neighbor Heuristic may not work as expected\n";
                    char c = 0;
                    while (tolower(c) != 'y' && tolower(c) != 'n') {
                        cout << "Would you like to continue? (y/n)\n";
                        cin >> c;
                        c = tolower(c);
                        if (c == 'n') {
                            mainMenu();
                        }
                    }
                }
                auto start = chrono::high_resolution_clock::now();
                dataManager.runNearestNeighborHeuristic(dataManager.getGraph());
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
                printTime(duration);
                break;
            }
            case '4': {
                int startVertex;
                cout << "Enter the start vertex: " << endl;
                cin >> startVertex;
                if (startVertex < 0 || startVertex >= dataManager.getGraph().getNumVertex()) {
                    cout << "Invalid start vertex, try again (choose a number between 0 and " << dataManager.getGraph().getNumVertex() - 1 << ")" << endl;
                    mainMenu();
                }
                cout << "Processing..." << endl;
                auto start = chrono::high_resolution_clock::now();
                dataManager.runModifiedDFS(dataManager.getGraph(), startVertex);
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
                printTime(duration);
                break;
            }
            case '5' : {
                cout << "The graph has " << dataManager.getGraph().getNumVertex() << " vertices and ";
                int numEdges = 0;
                for (auto vertex : dataManager.getGraph().getVertexSet()) {
                    numEdges += vertex->getAdj().size();
                }
                cout << numEdges << " edges" << endl;
                break;
            }
            case '6': {
                if (isFullyConnected(dataManager.getGraph())) {
                    cout << "Graph is already fully connected" << endl;
                    break;
                }
                else if (dataManager.getDataset() == "Toy-Graphs") {
                    cout << "Graph cannot be completed" << endl;
                    break;
                }
                else {
                    Graph<int>& fullyConnectedGraph = dataManager.getGraph();
                    for (auto vertex : fullyConnectedGraph.getVertexSet()) {
                        cout << vertex->getAdj().size() << " ";
                    }
                    cout << endl;
                    dataManager.completeGraph(fullyConnectedGraph);
                    dataManager.setGraph(fullyConnectedGraph);
                    for (auto vertex : fullyConnectedGraph.getVertexSet()) {
                        cout << vertex->getAdj().size() << " ";
                    }
                    if (isFullyConnected(fullyConnectedGraph)) cout << "Graph is now fully connected" << endl;
                    else cout << "Error completing the graph" << endl;
                    break;
                }
            }
            case '7':
                dataManager.clean();
                dataManager.start();
                break;
            case '8':
                cout << "\nGoodbye!\n";
                exit(0);
            default:
                cout << "Invalid input, try again\n";
                mainMenu();
                break;
        }
    }
    else if (dataManager.getDataset() == "Real-world Graphs") {
        switch (choice[0]) {
            case '1': {

                if(!isFullyConnected(dataManager.getGraph())){
                auto start = chrono::high_resolution_clock::now();
                Graph<int> fullyConnectedGraph = dataManager.getGraph().deepCopy();
                dataManager.completeGraph(fullyConnectedGraph);
                if (isFullyConnected(fullyConnectedGraph)) cout << "Graph is now fully connected" << endl;
                else {
                    cout << "Error completing the graph" << endl;
                    break;
                }
                dataManager.runBacktrackingAlgorithm(fullyConnectedGraph);
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
                printTime(duration);}
                else{
                    auto start = chrono::high_resolution_clock::now();
                    dataManager.runBacktrackingAlgorithm(dataManager.getGraph());
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
                    printTime(duration);
                }
                break;
            }
            case '2': {

                if(!isFullyConnected(dataManager.getGraph())){
                auto start = chrono::high_resolution_clock::now();
                Graph<int> fullyConnectedGraph = dataManager.getGraph().deepCopy();
                dataManager.completeGraph(fullyConnectedGraph);
                if (isFullyConnected(fullyConnectedGraph)) cout << "Graph is now fully connected" << endl;
                else {
                    cout << "Error completing the graph" << endl;
                    break;
                }
                dataManager.TAH(fullyConnectedGraph);
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
                printTime(duration);}
                else{
                    auto start = chrono::high_resolution_clock::now();
                    dataManager.TAH(dataManager.getGraph());
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
                    printTime(duration);
                }
                break;
            }
            case '3': {
                if(!isFullyConnected(dataManager.getGraph())){
                auto start = chrono::high_resolution_clock::now();
                Graph<int> fullyConnectedGraph = dataManager.getGraph().deepCopy();
                dataManager.completeGraph(fullyConnectedGraph);
                if (isFullyConnected(fullyConnectedGraph)) cout << "Graph is now fully connected" << endl;
                else {
                    cout << "Error completing the graph" << endl;
                    break;
                }
                dataManager.runNearestNeighborHeuristic(fullyConnectedGraph);
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
                printTime(duration);}
                else{
                    auto start = chrono::high_resolution_clock::now();
                    dataManager.runNearestNeighborHeuristic(dataManager.getGraph());
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
                    printTime(duration);
                }
                break;
            }
            case '4': {
                auto start = chrono::high_resolution_clock::now();
                int startVertex = -1;
                while (startVertex < 0 || startVertex >= dataManager.getNodes().size()) {
                    cout << "Enter the start vertex: " << endl;
                    cin >> startVertex;
                }
                cout << "Processing..." << endl;
                dataManager.runModifiedDFS(dataManager.getGraph(), startVertex);
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
                printTime(duration);
                break;
            }
            case '5' : {
                cout << "The graph has " << dataManager.getGraph().getNumVertex() << " vertices and ";
                int numEdges = 0;
                for (auto vertex : dataManager.getGraph().getVertexSet()) {
                    numEdges += vertex->getAdj().size();
                }
                cout << numEdges << " edges" << endl;
                break;
            }
            case '6': {
                if (isFullyConnected(dataManager.getGraph())) {
                    cout << "Graph is already fully connected" << endl;
                    break;
                }
                else {
                    Graph<int>& fullyConnectedGraph = dataManager.getGraph();
                    dataManager.completeGraph(fullyConnectedGraph);
                    dataManager.setGraph(fullyConnectedGraph);
                    if (isFullyConnected(fullyConnectedGraph)) cout << "Graph is now fully connected" << endl;
                    else cout << "Error completing the graph" << endl;
                    break;
                }
            }
            case '7':
                dataManager.clean();
                dataManager.start();
                break;
            case '8':
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

void Menu::printTime(chrono::milliseconds time) {
    long long total_seconds = time.count() / 1000;
    int minutes, seconds;
    cout << "Time taken: ";
    if (total_seconds >= 60) {
        minutes = (int) total_seconds / 60;
        seconds = (int) total_seconds % 60;
        cout << minutes << "m" << seconds << "s" << endl;
    }
    else {
        cout << total_seconds << "s" << endl;
    }
}

bool isFullyConnected(const Graph<int>& graph) {
    for (auto vertex : graph.getVertexSet()) {
        if (vertex->getAdj().size() != graph.getNumVertex() - 1) return false;
    }
    return true;
}