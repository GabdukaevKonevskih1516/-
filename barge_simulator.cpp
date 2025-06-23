#include "barge_simulator.h"

// РЕАЛИЗАЦИЯ МЕТОДОВ BARREL_LIST 

// Добавление бочки в конец списка
void BarrelList::push_back(int value) {
    BarrelNode* newNode = new BarrelNode(value);
    if (tail == nullptr) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;
}

// Удаление бочки с конца списка
void BarrelList::pop_back() {
    if (tail == nullptr) return;

    BarrelNode* toDelete = tail;
    tail = tail->prev;
    if (tail != nullptr) {
        tail->next = nullptr;
    }
    else {
        head = nullptr;
    }
    delete toDelete;
    size--;
}

// Получение последней бочки
int BarrelList::back() const {
    if (tail == nullptr) throw BargeException("Список бочек пуст");
    return tail->value;
}

// Проверка на пустоту
bool BarrelList::empty() const {
    return size == 0;
}

// Получение размера списка
int BarrelList::getSize() const {
    return size;
}

// Очистка списка
void BarrelList::clear() {
    while (head != nullptr) {
        BarrelNode* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    size = 0;
}

// РЕАЛИЗАЦИЯ МЕТОДОВ COMPARTMENT_LIST 

// Получение списка бочек по номеру отсека
BarrelList& CompartmentList::getBarrelList(int id) {
    CompartmentNode* current = head;
    while (current != nullptr) {
        if (current->id == id) {
            return current->barrels;
        }
        current = current->next;
    }

    // Создание нового отсека, если не найден
    CompartmentNode* newNode = new CompartmentNode(id);
    newNode->next = head;
    head = newNode;
    return newNode->barrels;
}

// Очистка списка отсеков
void CompartmentList::clear() {
    while (head != nullptr) {
        CompartmentNode* temp = head;
        head = head->next;
        delete temp;
    }
}

// РЕАЛИЗАЦИЯ МЕТОДОВ BARGE_SIMULATOR

// Очистка буфера ввода после ошибки
void BargeSimulator::clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Проверка корректности параметров инициализации
bool BargeSimulator::isValidInit(int N, int K, int P) {
    return !(N < 1 || N > 100000 || K < 1 || K > 100000 || P < 1 || P > 100000);
}

// Проверка корректности операции
bool BargeSimulator::isValidOp(char op, int A, int B, int K) {
    return (op == '+' || op == '-') &&
        (A >= 1 && A <= K) &&
        (B >= 1 && B <= 10000);
}

// Подсчет общего количества бочек
int BargeSimulator::countBarrels() {
    int total = 0;
    CompartmentNode* current = compartments.begin();
    while (current != nullptr) {
        total += current->barrels.getSize();
        current = current->next;
    }
    return total;
}

// Отображение текущего состояния баржи
void BargeSimulator::showState() {
    int total = 0;
    int used = 0;

    CompartmentNode* comp = compartments.begin();
    while (comp != nullptr) {
        int size = comp->barrels.getSize();
        total += size;
        if (size > 0) {
            used++;
        }
        comp = comp->next;
    }

    cout << "\n=== Текущее состояние ===" << endl;
    cout << "Всего бочек: " << total << endl;
    cout << "Используется отсеков: " << used << endl;

    if (total == 0) {
        cout << "Баржа пуста" << endl;
    }
    else {
        comp = compartments.begin();
        while (comp != nullptr) {
            if (!comp->barrels.empty()) {
                cout << "Отсек " << comp->id << ": ";
                BarrelNode* barrel = comp->barrels.begin();
                while (barrel != nullptr) {
                    cout << barrel->value;
                    barrel = barrel->next;
                    if (barrel != nullptr) cout << " <- ";
                }
                cout << " (верхняя: " << comp->barrels.back() << ")" << endl;
            }
            comp = comp->next;
        }
    }
    cout << "========================\n" << endl;
}
// Операция загрузки бочки
void BargeSimulator::load(int A, int B) {
    int total = countBarrels();
    if (total >= P) {
        showError("Превышено максимальное количество бочек (" + to_string(P) + ")");
        has_error = true;
        return;
    }

    compartments.getBarrelList(A).push_back(B);
    cout << "\nДобавлена бочка " << B << " в отсек " << A << endl;

    total++;
    if (total > max_b) {
        max_b = total;
    }
    showState();
}

// Операция выгрузки бочки
void BargeSimulator::unload(int A, int B) {
    BarrelList& barrels = compartments.getBarrelList(A);
    if (barrels.empty()) {
        showError("Отсек " + to_string(A) + " пуст");
        has_error = true;
        return;
    }

    if (barrels.back() != B) {
        showError("Ожидалась бочка " + to_string(B) +
            ", а в отсеке " + to_string(A) +
            " верхняя бочка " + to_string(barrels.back()));
        has_error = true;
        return;
    }

    cout << "\nИзвлечена бочка " << barrels.back()
        << " из отсека " << A << endl;
    barrels.pop_back();
    showState();
}

// Вывод сообщения об ошибке
void BargeSimulator::showError(const string& msg) {
    cerr << "ОШИБКА! " << msg << endl;
}

// Основной метод работы симулятора
void BargeSimulator::run() {
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

        try {
            if (op == '+') {
                load(A, B);
            }
            else {
                unload(A, B);
            }
        }
        catch (const BargeException& e) {
            showError(e.what());
            has_error = true;
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

    // Вывод результата
    cout << "\n=== Результат ===" << endl;
    if (has_error) {
        cout << "Error" << endl;
    }
    else {
        cout << "Максимум бочек: " << max_b << endl;
    }

    // Очистка памяти
    compartments.clear();
}
