#ifndef HEDER_H
#define HEDER_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

class BargeSimulator {
public:
    void run();
    
private:
    void showState();
    void load(int compartment, int barrel);
    void unload(int compartment, int barrel);
    void clearInput();
    bool isValidCommand(char op, int A, int B);
    
    int totalDocks;
    int totalCompartments;
    int maxBarrels;
    int currentBarrels;
    unordered_map<int, vector<int>> compartments;
};

#endif // HEDER_H
