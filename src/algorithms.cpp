#include "algorithms.hpp"

#include <algorithm>
#include <stdexcept>

namespace sem16 {

static bool contains(const std::vector<int>& v, int x) {
    for (int item : v) {
        if (item == x) return true;
    }
    return false;
}

int median_sort(std::vector<int> v) {
    if (v.empty()) {
        throw std::invalid_argument("median_sort: empty array");
    }
    std::sort(v.begin(), v.end());
    return v[v.size() / 2];
}

std::vector<int> intersection_bruteforce(const std::vector<int>& a, const std::vector<int>& b) {
    // O(n*m). Чтобы результат был "множеством", не добавляем дубликаты.
    std::vector<int> result;
    for (int x : a) {
        for (int y : b) {
            if (x == y) {
                if (!contains(result, x)) {
                    result.push_back(x);
                }
                break; // x уже найден в b
            }
        }
    }
    return result;
}

std::vector<int> intersection_sort_two_pointers(std::vector<int> a, std::vector<int> b) {
    // Сортируем обе последовательности и идём двумя указателями.
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());

    std::vector<int> result;

    std::size_t i = 0, j = 0;
    while (i < a.size() && j < b.size()) {
        if (a[i] < b[j]) {
            ++i;
        } else if (b[j] < a[i]) {
            ++j;
        } else {
            // a[i] == b[j]
            int value = a[i];
            if (result.empty() || result.back() != value) {
                result.push_back(value);
            }

            ++i;
            ++j;

            // пропускаем дубликаты (если вход был не совсем множеством)
            while (i < a.size() && a[i] == value) ++i;
            while (j < b.size() && b[j] == value) ++j;
        }
    }

    return result;
}

MinMax minmax_bruteforce(const std::vector<int>& v) {
    if (v.empty()) {
        throw std::invalid_argument("minmax_bruteforce: empty array");
    }
    int mn = v[0];
    int mx = v[0];
    for (std::size_t i = 1; i < v.size(); ++i) {
        if (v[i] < mn) mn = v[i];
        if (v[i] > mx) mx = v[i];
    }
    return {mn, mx};
}

MinMax minmax_sort(std::vector<int> v) {
    if (v.empty()) {
        throw std::invalid_argument("minmax_sort: empty array");
    }
    std::sort(v.begin(), v.end());
    return {v.front(), v.back()};
}

MinMax minmax_decomposition(const std::vector<int>& v) {
    // Идея: сравниваем элементы попарно.
    // Из каждой пары получаем локальный min и локальный max.
    // Потом ищем min среди локальных min и max среди локальных max.
    if (v.empty()) {
        throw std::invalid_argument("minmax_decomposition: empty array");
    }
    if (v.size() == 1) {
        return {v[0], v[0]};
    }

    std::vector<int> local_mins;
    std::vector<int> local_maxs;
    local_mins.reserve((v.size() + 1) / 2);
    local_maxs.reserve((v.size() + 1) / 2);

    std::size_t i = 0;
    while (i + 1 < v.size()) {
        int a = v[i];
        int b = v[i + 1];
        if (a < b) {
            local_mins.push_back(a);
            local_maxs.push_back(b);
        } else {
            local_mins.push_back(b);
            local_maxs.push_back(a);
        }
        i += 2;
    }

    // если нечётное количество — последний элемент добавляем и туда, и туда
    if (i < v.size()) {
        local_mins.push_back(v[i]);
        local_maxs.push_back(v[i]);
    }

    int mn = local_mins[0];
    for (std::size_t k = 1; k < local_mins.size(); ++k) {
        if (local_mins[k] < mn) mn = local_mins[k];
    }

    int mx = local_maxs[0];
    for (std::size_t k = 1; k < local_maxs.size(); ++k) {
        if (local_maxs[k] > mx) mx = local_maxs[k];
    }

    return {mn, mx};
}

} // namespace sem16
