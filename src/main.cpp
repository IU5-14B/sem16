#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <random>

#include "algorithms.hpp"

static void clear_input() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

static int read_int(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        int x;
        if (std::cin >> x) return x;
        std::cout << "Ошибка ввода. Попробуйте ещё раз.\n";
        clear_input();
    }
}

static std::vector<int> read_vector_manual(const std::string& name) {
    int n = read_int("Введите размер " + name + ": ");
    while (n < 0) {
        std::cout << "Размер не может быть отрицательным.\n";
        n = read_int("Введите размер " + name + ": ");
    }

    std::vector<int> v;
    v.reserve(static_cast<std::size_t>(n));

    std::cout << "Введите " << n << " целых чисел:\n";
    for (int i = 0; i < n; ++i) {
        int x = read_int("  " + std::to_string(i) + ": ");
        v.push_back(x);
    }
    return v;
}

static std::vector<int> read_vector_random(const std::string& name) {
    int n = read_int("Введите размер " + name + ": ");
    while (n < 0) {
        std::cout << "Размер не может быть отрицательным.\n";
        n = read_int("Введите размер " + name + ": ");
    }
    int lo = read_int("Минимальное значение: ");
    int hi = read_int("Максимальное значение: ");
    while (hi < lo) {
        std::cout << "Максимум должен быть >= минимума.\n";
        lo = read_int("Минимальное значение: ");
        hi = read_int("Максимальное значение: ");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(lo, hi);

    std::vector<int> v;
    v.reserve(static_cast<std::size_t>(n));
    for (int i = 0; i < n; ++i) v.push_back(dist(gen));

    std::cout << name << " сгенерирован.\n";
    return v;
}

static std::vector<int> read_vector(const std::string& name) {
    while (true) {
        std::cout << "Как задать " << name << "?\n";
        std::cout << "  1) Ввести вручную\n";
        std::cout << "  2) Сгенерировать случайно\n";
        int mode = read_int("Выбор: ");
        if (mode == 1) return read_vector_manual(name);
        if (mode == 2) return read_vector_random(name);
        std::cout << "Неверный выбор.\n";
    }
}

static void print_vector(const std::vector<int>& v) {
    std::cout << "[";
    for (std::size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i];
        if (i + 1 < v.size()) std::cout << ", ";
    }
    std::cout << "]";
}

static void task1_median() {
    std::cout << "\n--- Задача 1: медиана через сортировку ---\n";
    std::vector<int> v = read_vector("массив");
    if (v.empty()) {
        std::cout << "Массив пустой — медиана не определена.\n";
        return;
    }
    int med = sem16::median_sort(v);
    std::cout << "Массив: ";
    print_vector(v);
    std::cout << "\nМедиана (элемент с индексом n/2 после сортировки): " << med << "\n";
    std::cout << "Сложность: O(n log n)\n";
}

static void task3_intersection() {
    std::cout << "\n--- Задача 3: пересечение множеств A и B ---\n";
    std::vector<int> a = read_vector("A");
    std::vector<int> b = read_vector("B");

    std::cout << "A = ";
    print_vector(a);
    std::cout << "\nB = ";
    print_vector(b);
    std::cout << "\n";

    auto r1 = sem16::intersection_bruteforce(a, b);
    auto r2 = sem16::intersection_sort_two_pointers(a, b);

    std::cout << "\n(a) Грубая сила (O(n*m)):\nC = ";
    print_vector(r1);
    std::cout << "\n";

    std::cout << "\n(b) Сортировка + два указателя (O(n log n + m log m)):\nC = ";
    print_vector(r2);
    std::cout << "\n";
}

static void task4_minmax() {
    std::cout << "\n--- Задача 4: минимум и максимум ---\n";
    std::vector<int> v = read_vector("массив");
    if (v.empty()) {
        std::cout << "Массив пустой — min/max не определены.\n";
        return;
    }

    std::cout << "Массив: ";
    print_vector(v);
    std::cout << "\n";

    auto mm1 = sem16::minmax_bruteforce(v);
    auto mm2 = sem16::minmax_sort(v);
    auto mm3 = sem16::minmax_decomposition(v);

    std::cout << "\n1) Грубая сила (1 проход): min=" << mm1.min_value << ", max=" << mm1.max_value
              << "  | сложность O(n)\n";
    std::cout << "2) Через сортировку:        min=" << mm2.min_value << ", max=" << mm2.max_value
              << "  | сложность O(n log n)\n";
    std::cout << "3) Декомпозиция (пары):     min=" << mm3.min_value << ", max=" << mm3.max_value
              << "  | сложность O(n)\n";

    std::cout << "\nСравнение:\n"
              << "- Грубая сила и декомпозиция работают за O(n).\n"
              << "- Сортировка медленнее по асимптотике: O(n log n), но после сортировки могут быть полезны другие операции.\n";
}

static void show_menu() {
    std::cout << "\n========== Семинар 16 ==========\n";
    std::cout << "1) Задача 1: медиана через сортировку\n";
    std::cout << "2) Задача 3: пересечение множеств A и B\n";
    std::cout << "3) Задача 4: минимум и максимум (3 алгоритма)\n";
    std::cout << "0) Выход\n";
}

int main() {
    while (true) {
        show_menu();
        int choice = read_int("Выберите пункт: ");

        try {
            if (choice == 0) {
                std::cout << "Выход.\n";
                return 0;
            } else if (choice == 1) {
                task1_median();
            } else if (choice == 2) {
                task3_intersection();
            } else if (choice == 3) {
                task4_minmax();
            } else {
                std::cout << "Неверный пункт меню.\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << "\n";
        }
    }
}
