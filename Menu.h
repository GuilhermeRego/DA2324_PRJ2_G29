#ifndef DA2324_PRJ2_G29_MENU_H
#define DA2324_PRJ2_G29_MENU_H


#include "DataManager.h"

class Menu {
    public:
        Menu();
        void init();
        void mainMenu();
    private:
        DataManager dataManager;

    double calculateTSPBacktracking(const Graph<int>& graph, vector<int>& bestTour);

    void runBacktrackingAlgorithm();
};


#endif
