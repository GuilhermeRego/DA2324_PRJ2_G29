#ifndef DA2324_PRJ2_G29_MENU_H
#define DA2324_PRJ2_G29_MENU_H


#include <chrono>
#include "DataManager.h"

class Menu {

    public:
        Menu();
        void init();
        void mainMenu();
        static void printTime(chrono::milliseconds time);

    private:
        DataManager dataManager;
    };

#endif