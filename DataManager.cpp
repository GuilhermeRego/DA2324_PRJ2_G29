#include "DataManager.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Graph.h"

using namespace std;

DataManager::DataManager() {
    string dataset, csv;
    cout << "Choose the dataset: " << endl;
    cout << "1 - Toy-Graphs" << endl;
    cout << "2 - Extra_Fully_Connected_Graphs" << endl;
    cout << "3 - Real-world Graphs" << endl;
    cin >> dataset;
    cout << "Enter the csv file: " << endl;
    if (dataset == "1") {
        dataset = "Toy-Graphs";
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
        cout << "Not implemented yet" << endl;
    }
    else {
        cout << "Invalid dataset" << endl;
    }
}

void DataManager::readToy(string dataset, string csv) {
    string path = "../data/" + dataset + "/" + csv;
    ifstream file(path);
    string line;
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
            cout << source << " " << dest << " " << weight << endl;
        }
    }
}