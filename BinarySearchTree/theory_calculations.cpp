/**
 * @file theory_calculations.cpp
 * @brief Реализация теоретических расчетов для деревьев поиска
 */

#include "theory_calculations.h"
#include <cmath>
#include <algorithm>

 /**
  * @brief Теоретическая оценка высоты ИСДП
  * @param n Количество узлов в дереве
  * @return Теоретическая высота идеально сбалансированного дерева
  *
  * @details
  * Для идеально сбалансированного дерева высота вычисляется как:
  * h = ⌊log₂(n)⌋
  * Это минимально возможная высота для BST с n узлами.
  */
double TheoryCalculations::theoreticalHeightBalanced(int n) {
    if (n <= 0) return 0.0;
    return std::floor(log2(n));
}

/**
 * @brief Теоретическая оценка средней высоты ИСДП
 * @param n Количество узлов в дереве
 * @return Теоретическая средняя высота узлов
 *
 * @details
 * Вычисляет среднюю глубину узлов в идеально сбалансированном дереве.
 * Алгоритм:
 * 1. Заполняет уровни дерева максимально возможным количеством узлов
 * 2. Суммирует произведение уровня на количество узлов на этом уровне
 * 3. Делит сумму на общее количество узлов
 *
 * @note Использует long double для точности при больших n
 */
double TheoryCalculations::theoreticalAverageHeightBalanced(int n) {
    if (n <= 0) return 0.0;

    long long nodes_remaining = n;
    long long level = 1;
    long double sum = 0.0L;   // level * nodes, безопасно

    while (nodes_remaining > 0) {
        long long possible = 1LL << (level - 1); // 2^(L-1)
        long long use = (possible < nodes_remaining) ? possible : nodes_remaining;

        sum += (long double)level * (long double)use;

        nodes_remaining -= use;
        level++;
    }

    return (double)(sum / (long double)n);
}

/**
 * @brief Теоретическая оценка высоты СДП
 * @param n Количество узлов в дереве
 * @return Теоретическая высота случайного дерева поиска
 *
 * @details
 * Для случайного BST средняя высота оценивается как:
 * h ≈ 2.99 * log₂(n)
 * Это эмпирическая формула, основанная на статистических свойствах BST.
 */
double TheoryCalculations::theoreticalHeightRandomBST(int n) {
    if (n <= 1) return 0.0;
    return 2.99 * log2(n); // приближение для случайного BST
}

/**
 * @brief Теоретическая оценка средней высоты СДП
 * @param n Количество узлов в дереве
 * @return Теоретическая средняя высота узлов в случайном BST
 *
 * @details
 * Средняя высота узлов в случайном BST оценивается как:
 * H_avg ≈ 2 * ln(n)
 * Это математическое ожидание глубины случайного узла.
 */
double TheoryCalculations::theoreticalAverageHeightRandomBST(int n) {
    if (n <= 1) return 0.0;
    return 2.0 * ln(n); // приближение для средней высоты случайного BST
}

/**
 * @brief Теоретическая оценка высоты B-дерева (ДБД)
 * @param n Количество ключей в дереве
 * @param t Минимальная степень B-дерева (t ≥ 2)
 * @return Теоретическая высота B-дерева
 *
 * @details
 * Высота B-дерева оценивается по формуле:
 * h ≤ ⌈log_m(n)⌉, где m = минимальное количество ключей на узел
 * Для t-дерева: m = ceil(t/2)
 *
 * @note Для t=2 получаем 2-3 дерево с m=2
 */
int TheoryCalculations::theoreticalDBHeight(int n, int t) {
    if (n == 0) return 0;

    // Минимальное количество ключей на узел (кроме корня)
    int minKeysPerNode = std::max(2, (int)std::ceil(t / 2.0));

    // Формула высоты B-дерева: h ≤ ⌈log_m(n)⌉
    return (int)std::ceil(std::log(static_cast<double>(n)) / std::log(static_cast<double>(minKeysPerNode)));
}

/**
 * @brief Вычисление логарифма по основанию 2
 * @param x Аргумент логарифма
 * @return log₂(x), или 0 если x ≤ 0
 *
 * @details
 * Использует формулу замены основания:
 * log₂(x) = ln(x) / ln(2)
 */
double TheoryCalculations::log2(double x) {
    if (x <= 0.0) return 0.0;
    return std::log(x) / std::log(2.0);
}

/**
 * @brief Вычисление натурального логарифма
 * @param x Аргумент логарифма
 * @return ln(x), или 0 если x ≤ 0
 *
 * @details
 * Обертка над std::log с проверкой на неположительные значения.
 */
double TheoryCalculations::ln(double x) {
    if (x <= 0.0) return 0.0;
    return std::log(x);
}