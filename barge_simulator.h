#ifndef BARGE_SIMULATOR_H
#define BARGE_SIMULATOR_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits>
#include <string>

using namespace std;

class BargeSimulator { // Класс симулятора баржи
public:
    void run();  // Основной метод запуска симуляции

private:

    void clearInput();     // Очистка буфера ввода
    bool isValidInit(int N, int K, int P); // Проверка начальных параметров
    bool isValidOp(char op, int A, int B, int K); // Проверка операции
    void load(int A, int B);  // Загрузка бочки
    void unload(int A, int B); // Выгрузка бочки
    void showError(const string& msg); // Вывод ошибки
    void showState();      // Отображение текущего состояния
    int countBarrels();    // Подсчет общего количества бочек

    int N;                // Количество операций
    int K;                // Количество отсеков
    int P;                // Максимальное количество бочек
    int max_b;            // Максимальное число бочек за время симуляции
    bool has_error;       // Флаг ошибки
    unordered_map<int, vector<int>> comps; // Контейнер: отсек → вектор бочек
};

#endif
