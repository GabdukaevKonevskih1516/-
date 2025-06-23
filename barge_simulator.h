#ifndef BARGE_SIMULATOR_H
#define BARGE_SIMULATOR_H

#include <iostream>
#include <limits>
#include <string>

using namespace std;

// Класс для обработки исключений симулятора
class BargeException {
public:
    explicit BargeException(const string& msg) : message(msg) {}
    string what() const { return message; }
private:
    string message;
};

// Узел двусвязного списка для хранения бочек
struct BarrelNode {
    int value;         // Номер бочки
    BarrelNode* prev;  // Указатель на предыдущую бочку
    BarrelNode* next;  // Указатель на следующую бочку

    explicit BarrelNode(int val) : value(val), prev(nullptr), next(nullptr) {}
};

// Двусвязный список для хранения бочек в отсеке
class BarrelList {
public:
    BarrelList() : head(nullptr), tail(nullptr), size(0) {}
    ~BarrelList() { clear(); }

    // Основные методы работы со списком бочек
    void push_back(int value);  // Добавить бочку в конец
    void pop_back();            // Удалить бочку с конца
    int back() const;           // Получить последнюю бочку
    bool empty() const;         // Проверить на пустоту
    int getSize() const;        // Получить количество бочек
    void clear();               // Очистить список

    // Итератор для прохода по списку (для вывода)
    BarrelNode* begin() const { return head; }
    BarrelNode* end() const { return nullptr; }

private:
    BarrelNode* head;  // Указатель на первую бочку
    BarrelNode* tail;  // Указатель на последнюю бочку
    int size;          // Количество бочек в отсеке
};

// Узел списка отсеков баржи
struct CompartmentNode {
    int id;               // Номер отсека
    BarrelList barrels;   // Список бочек в отсеке
    CompartmentNode* next; // Указатель на следующий отсек

    explicit CompartmentNode(int id) : id(id), next(nullptr) {}
};

// Односвязный список отсеков баржи
class CompartmentList {
public:
    CompartmentList() : head(nullptr) {}
    ~CompartmentList() { clear(); }

    // Получение списка бочек по номеру отсека
    BarrelList& getBarrelList(int id);

    // Очистка списка отсеков
    void clear();

    // Итератор для прохода по отсекам
    CompartmentNode* begin() const { return head; }
    CompartmentNode* end() const { return nullptr; }

private:
    CompartmentNode* head;  // Указатель на первый отсек
};

// Основной класс симулятора баржи
class BargeSimulator {
public:
    void run();  // Главный метод запуска симуляции

private:
    // Вспомогательные методы
    void clearInput();                      // Очистка буфера ввода
    bool isValidInit(int N, int K, int P);  // Проверка параметров инициализации
    bool isValidOp(char op, int A, int B, int K); // Проверка операции
    void load(int A, int B);                // Загрузка бочки
    void unload(int A, int B);              // Выгрузка бочки
    void showError(const string& msg);      // Вывод ошибки
    void showState();                       // Отображение состояния
    int countBarrels();                     // Подсчет общего числа бочек

    // Параметры симуляции
    int N;                 // Общее количество операций
    int K;                 // Количество отсеков
    int P;                 // Максимальное количество бочек
    int max_b;             // Максимальное количество бочек за все время
    bool has_error;        // Флаг ошибки
    CompartmentList compartments;  // Структура данных баржи
};

#endif
