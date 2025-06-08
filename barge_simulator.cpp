#include "barge_simulator.h"

void BargeSimulator::clearInput() { // Очистка буфера ввода после ошибочного ввода
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool BargeSimulator::isValidInit(int N, int K, int P) { // Проверка корректности начальных параметров (N, K, P)
    return !(N < 1 || N > 100000 || K < 1 || K > 100000 || P < 1 || P > 100000);
}

bool BargeSimulator::isValidOp(char op, int A, int B, int K) { // Проверка корректности операции (+/-) и параметров (A, B)
    return (op == '+' || op == '-') &&
           (A >= 1 && A <= K) &&
           (B >= 1 && B <= 10000);
}

int BargeSimulator::countBarrels() { // Подсчет общего количества бочек во всех отсеках
    int total = 0;
    for (const auto& c : comps) {
        total += c.second.size();
    }
    return total;
}

void BargeSimulator::showState() { // Вывод текущего состояния баржи
    int total = 0;
    int used = 0;
    
    for (const auto& c : comps) {
        total += c.second.size();
        if (!c.second.empty()) {
            used++;
        }
    }

    cout << "\n=== Текущее состояние ===" << endl;
    cout << "Всего бочек: " << total << endl;
    cout << "Используется отсеков: " << used << endl;

    if (total == 0) {
        cout << "Баржа пуста" << endl;
        return;
    }

    for (const auto& c : comps) {
        if (!c.second.empty()) {
            cout << "Отсек " << c.first << ": ";
            for (int i = c.second.size() - 1; i >= 0; --i) {
                cout << c.second[i];
                if (i != 0) cout << " <- ";
            }
            cout << " (верхняя: " << c.second.back() << ")" << endl;
        }
    }
    cout << "========================\n" << endl;
}

void BargeSimulator::load(int A, int B) { // Операция загрузки бочки в отсек
    int total = countBarrels();
    if (total >= P) {
        showError("Превышено максимальное количество бочек (" + to_string(P) + ")");
        has_error = true;
        return;
    }

    comps[A].push_back(B);
    cout << "\nДобавлена бочка " << B << " в отсек " << A << endl;
    showState();
    
    total++;
    if (total > max_b) {
        max_b = total;
    }
}

void BargeSimulator::unload(int A, int B) { // Операция выгрузки бочки из отсека
    if (comps[A].empty()) {
        showError("Отсек " + to_string(A) + " пуст");
        has_error = true;
        return;
    }

    if (comps[A].back() != B) {
        showError("Ожидалась бочка " + to_string(B) +
                 ", а в отсеке " + to_string(A) +
                 " верхняя бочка " + to_string(comps[A].back()));
        has_error = true;
        return;
    }

    cout << "\nИзвлечена бочка " << comps[A].back()
         << " из отсека " << A << endl;
    comps[A].pop_back();
    showState();
}

void BargeSimulator::showError(const string& msg) { // Вывод сообщения об ошибке
    cerr << "ОШИБКА! " << msg << endl; 
}

void BargeSimulator::run() { // Основной метод работы симулятора
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Симулятор работы баржи ===" << endl;
    cout << "Изначальное состояние: баржа пуста\n" << endl;

    // Ввод параметров
    cout << "Введите N, K и P:" << endl;
    cout << "N - кол-во операций (1-100000)" << endl;
    cout << "K - кол-во отсеков (1-100000)" << endl;
    cout << "P - макс. кол-во бочек (1-100000)" << endl;

    while (true) {
        cin >> N >> K >> P;
        if (cin.fail() || !isValidInit(N, K, P)) {
            cout << "Ошибка! Введите три числа 1-100000:" << endl;
            clearInput();
        }
        else {
            break;
        }
    }

    // Ввод операций
    cout << "\nВведите " << N << " операций:" << endl;
    cout << "+ A B - погрузить бочку B в отсек A" << endl;
    cout << "- A B - выгрузить бочку B из отсека A" << endl;
    cout << "1 <= A <= " << K << ", 1 <= B <= 10000\n" << endl;

    max_b = 0;
    has_error = false;

    for (int i = 0; i < N && !has_error; ++i) {
        char op;
        int A, B;

        while (true) {
            cout << "Операция #" << i + 1 << ": ";
            cin >> op;

            if (op != '+' && op != '-') {
                cout << "Ошибка! Операция должна быть '+' или '-'" << endl;
                clearInput();
                continue;
            }

            cin >> A >> B;
            if (cin.fail() || !isValidOp(op, A, B, K)) {
                cout << "Ошибка! Некорректные параметры" << endl;
                clearInput();
            }
            else {
                break;
            }
        }

        if (op == '+') {
            load(A, B);
        }
        else {
            unload(A, B);
        }
    }

    // Финальная проверка
    cout << "\n=== Финальное состояние ===" << endl;
    if (!has_error) {
        if (countBarrels() != 0) {
            showError("Баржа не пуста");
            has_error = true;
        }
        else {
            cout << "Все операции успешны!" << endl;
        }
    }

    // Результат
    cout << "\n=== Результат ===" << endl;
    if (has_error) {
        cout << "Error" << endl;
    }
    else {
        cout << "Максимум бочек: " << max_b << endl;
    }
}
