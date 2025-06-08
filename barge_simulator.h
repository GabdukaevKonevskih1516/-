#ifndef BARGE_SIMULATOR_H
#define BARGE_SIMULATOR_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits>
#include <string>

using namespace std;

class BargeSimulator {
public:
    void run();

private:
    void clearInput();
    bool isValidInit(int N, int K, int P);
    bool isValidOp(char op, int A, int B, int K);
    void load(int A, int B);
    void unload(int A, int B);
    void showError(const string& msg);
    void showState();
    int countBarrels();

    int N;
    int K;
    int P;
    int max_b;
    bool has_error;
    unordered_map<int, vector<int>> comps;
};

#endif
