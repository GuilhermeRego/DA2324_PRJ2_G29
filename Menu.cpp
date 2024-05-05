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
        if (dataManager.getCsv() == "shipping.csv")
            cout << "\nCurrent dataset: " << dataManager.getDataset() << " -> " << dataManager.getCsv() << " (not fully connected)" << endl;
        else if (dataManager.getCsv() == "stadiums.csv" || dataManager.getCsv() == "tourism.csv")
            cout << "\nCurrent dataset: " << dataManager.getDataset() << " -> " << dataManager.getCsv() << " (fully connected)" << endl;
        else
            cout << "\nCurrent dataset: " << dataManager.getDataset() << " -> " << dataManager.getCsv() << endl;
        cout << "\n===== Main Menu =====" << endl;
        cout << "1 - Backtracking Algorithm" << endl;
        cout << "2 - Triangular Approximation Heuristic (fully connected)" << endl;
        cout << "3 - Other Heuristics (fully connected)" << endl;
        cout << "4 - TSP (not fully connected)" << endl;
        cout << "5 - Exit" << endl;
        cin >> choice;

        switch (choice) {
            case 1:
                dataManager.runBacktrackingAlgorithm(dataManager.getGraph());
                break;
            case 2:
                if (dataManager.getCsv() == "shipping.csv") {
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
                dataManager.TAH(dataManager.getGraph());
                break;
            case 3:
                if (dataManager.getCsv() == "shipping.csv") {
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
                dataManager.runNearestNeighborHeuristic(dataManager.getGraph());
                break;
            case 4:
                cout << "TSP not implemented yet\n";
                break;
            case 5:
                cout << "\nGoodbye!\n";
                exit(0);
            default:
                cout << "Invalid input, try again\n";
                mainMenu();
                break;
        }
    }
    else if (dataManager.getDataset() == "Real-world Graphs") {
        int choice;
        cout << "\n===== Main Menu =====" << endl;
        cout << "1 - Backtracking Algorithm" << endl;
        cout << "2 - Triangular Approximation Heuristic (fully connected)" << endl;
        cout << "3 - Other Heuristics (fully connected)" << endl;
        cout << "4 - TSP (not fully connected)" << endl;
        cout << "5 - Exit" << endl;
        cin >> choice;

        switch (choice) {
            case 1: {
                Graph<int> fullyConnectedGraph = dataManager.getGraph().deepCopy();
                dataManager.completeGraph(fullyConnectedGraph);
                dataManager.runBacktrackingAlgorithm(fullyConnectedGraph);
                break;
            }
            case 2: {
                Graph<int> fullyConnectedGraph = dataManager.getGraph().deepCopy();
                dataManager.completeGraph(fullyConnectedGraph);
                dataManager.TAH(fullyConnectedGraph);
                break;
            }
            case 3: {
                Graph<int> fullyConnectedGraph = dataManager.getGraph().deepCopy();
                dataManager.completeGraph(fullyConnectedGraph);
                dataManager.runNearestNeighborHeuristic(fullyConnectedGraph);
                break;
            }
            case 4: {
                int startVertex = -1;
                while (startVertex < 0 || startVertex >= dataManager.getNodes().size()) {
                    cout << "Enter the start vertex: " << endl;
                    cin >> startVertex;
                }
                cout << "Processing..." << endl;
                dataManager.runEfficientTSP(dataManager.getGraph(), startVertex);
                break;
            }
            case 5:
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