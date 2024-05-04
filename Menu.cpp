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
                dataManager.runBacktrackingAlgorithm();
                break;
            case 2:
                dataManager.toyGraphTAH();
                break;
            case 3:
                dataManager.runNearestNeighborHeuristic();
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
                dataManager.runBacktrackingAlgorithm();
                break;
            case 2:
                dataManager.realWorldGraphTAH();
                break;
            case 3:
                dataManager.runNearestNeighborHeuristic();
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
