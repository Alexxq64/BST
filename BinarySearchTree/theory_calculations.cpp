#include "theory_calculations.h"
#include <cmath>

/**
 * @file theory_calculations.cpp
 * @brief Реализация теоретических расчетов для деревьев поиска
 */

 /**
  * @brief Теоретическая оценка высоты ИСДП
  */
double TheoryCalculations::theoreticalHeightBalanced(int n) {
    if (n <= 0) return 0.0;
    return std::floor(log2(n));
}

/**
 * @brief Теоретическая оценка средней высоты ИСДП
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
 */
double TheoryCalculations::theoreticalHeightRandomBST(int n) {
    if (n <= 1) return 0.0;
    return 2.99 * log2(n); // приближение для случайного BST
}

/**
 * @brief Теоретическая оценка средней высоты СДП
 */
double TheoryCalculations::theoreticalAverageHeightRandomBST(int n) {
    if (n <= 1) return 0.0;
    return 2.0 * ln(n); // приближение для средней высоты случайного BST
}

/**
 * @brief Логарифм по основанию 2
 */
double TheoryCalculations::log2(double x) {
    if (x <= 0.0) return 0.0;
    return std::log(x) / std::log(2.0);
}

/**
 * @brief Натуральный логарифм
 */
double TheoryCalculations::ln(double x) {
    if (x <= 0.0) return 0.0;
    return std::log(x);
}


int TheoryCalculations::theoreticalDBHeight(int n, int t) {
    if (n == 0) return 0;
    return std::ceil(std::log(n + 1) / std::log(t));
}
