#include "heder.h"
#include <limits>

void BargeSimulator::clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool BargeSimulator::isValidCommand(char op, int A, int B) {
    return (op == '+' || op == '-') && 
           (A >= 1 && A <= totalCompartments) && 
           (B >= 1 && B <= 10000);
}

void BargeSimulator::showState() {
    currentBarrels = 0;
    int usedCompartments = 0;
    
    for (const auto& comp : compartments) {
        currentBarrels += comp.second.size();
        if (!comp.second.empty()) {
            usedCompartments++;
        }
    }

    cout << "\n=== Текущее состояние баржи ===" << endl;
    cout << "Всего бочек: " << currentBarrels << endl;
    cout << "Используется отсеков: " << usedCompartments << endl;

    if (currentBarrels == 0) {
        cout << "Баржа пуста" << endl;
        return;
    }

    for (const auto& comp : compartments) {
        if (!comp.second.empty()) {
            cout << "Отсек " << comp.first << ": ";
            for (int i = comp.second.size() - 1; i >= 0; --i) {
                cout << comp.second[i];
                if (i != 0) cout << " <- ";
            }
            cout << " (верхняя: " << comp.second.back() << ")" << endl;
        }
    }
    cout << "==============================" << endl;
}

void BargeSimulator::load(int compartment, int barrel) {
    if (currentBarrels >= maxBarrels) {
        cout << "ОШИБКА! Превышен лимит бочек (" << maxBarrels << ")" << endl;
        return;
    }

    compartments[compartment].push_back(barrel);
    cout << "Добавлена бочка " << barrel << " в отсек " << compartment << endl;
    showState();
}

void BargeSimulator::unload(int compartment, int barrel) {
    if (compartments[compartment].empty()) {
        cout << "ОШИБКА! Отсек " << compartment << " пуст" << endl;
        return;
    }

    if (compartments[compartment].back() != barrel) {
        cout << "ОШИБКА! В отсеке " << compartment 
             << " верхняя бочка " << compartments[compartment].back()
             << ", а ожидалась " << barrel << endl;
        return;
    }

    cout << "Извлечена бочка " << barrel << " из отсека " << compartment << endl;
    compartments[compartment].pop_back();
    showState();
}

void BargeSimulator::run() {
    cout << "=== Симулятор баржи ===" << endl;
    cout << "Введите количество операций, отсеков и лимит бочек: ";
    
    while (!(cin >> totalDocks >> totalCompartments >> maxBarrels) || 
           totalDocks < 1 || totalCompartments < 1 || maxBarrels < 1) {
        cout << "Ошибка ввода! Повторите: ";
        clearInput();
    }

    currentBarrels = 0;
    compartments.clear();

    cout << "\nВведите " << totalDocks << " операций (+ A B для загрузки, - A B для выгрузки):" << endl;
    
    for (int i = 0; i < totalDocks; ++i) {
        char op;
        int A, B;
        
        cout << "Операция " << i+1 << ": ";
        while (!(cin >> op >> A >> B) || !isValidCommand(op, A, B)) {
            cout << "Неверная команда! Повторите: ";
            clearInput();
        }

        if (op == '+') {
            load(A, B);
        } else {
            unload(A, B);
        }
    }

    cout << "\n=== Итоговое состояние ===" << endl;
    showState();
}
