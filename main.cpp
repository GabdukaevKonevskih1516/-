#include "barge_simulator.h"

int main() {
    setlocale(LC_ALL, "Russian");  // Установка русской локали

    try {
        BargeSimulator sim;  // Создание экземпляра симулятора
        sim.run();           // Запуск симуляции
    }
    catch (const exception& e) {
        cerr << "Критическая ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}
