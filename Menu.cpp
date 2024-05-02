//
// Created by guire on 01/05/2024.
//

#include "Menu.h"

Menu::Menu() {
    init();
}

void Menu::init() {
    mainMenu();
}


void Menu::mainMenu() {
    if(dataManager.getcsv() == "shipping.csv") {
        int choice;
        cout << "===== Main Menu =====" << endl;
        cout << "1. Backtracking Algorithm" << endl;
        cout << "2. TSP in the Real World" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                break;
            case 2:
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

    if(dataManager.getcsv() == "stadiums.csv" || dataManager.getcsv() =="tourism.csv") {
        int choice;
        cout << "===== Main Menu =====" << endl;
        cout << "1. Backtracking Algorithm" << endl;
        cout << "2. Triangular Approximation Heuristic" << endl;
        cout << "3. Other Heuristics" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                break;
            case 2:
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
}
