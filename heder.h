#ifndef HEDER_H
#define HEDER_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

class BargeSimulator {
public:
    void run(); // Запуск симуляции
    
private:
    void showState(); // Вывод текущего состояния
    void load(int compartment, int barrel); // Загрузка бочки в отсек
    void unload(int compartment, int barrel); // Выгрузка бочки из отсека
    void clearInput(); // Очистка буфера ввода
    bool isValidCommand(char op, int A, int B); // Проверка команды на адекватность
    
    int totalDocks; // Общее число операций
    int totalCompartments; // Количество отсеков
    int maxBarrels; // Лимит бочек
    int currentBarrels; // Текущее число бочек
    unordered_map<int, vector<int>> compartments; // Контейнер: номер отсека → вектор бочек
};

#endif // HEDER_H
