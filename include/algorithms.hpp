#pragma once

#include <vector>

namespace sem16 {

// ---------- Task 1: median via sorting ----------
int median_sort(std::vector<int> v); // принимает копию, сортирует, возвращает v[n/2]

// ---------- Task 3: intersection ----------
std::vector<int> intersection_bruteforce(const std::vector<int>& a, const std::vector<int>& b);
std::vector<int> intersection_sort_two_pointers(std::vector<int> a, std::vector<int> b);

// ---------- Task 4: min/max ----------
struct MinMax {
    int min_value;
    int max_value;
};

MinMax minmax_bruteforce(const std::vector<int>& v);        // один проход
MinMax minmax_sort(std::vector<int> v);                      // сортировка
MinMax minmax_decomposition(const std::vector<int>& v);      // попарное сравнение

} // namespace sem16
