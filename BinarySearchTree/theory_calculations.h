#ifndef THEORY_CALCULATIONS_H
#define THEORY_CALCULATIONS_H

#include <cmath>

/**
 * @file theory_calculations.h
 * @brief Теоретические оценки характеристик деревьев поиска
 *
 * Этот файл содержит функции для вычисления теоретических оценок
 * высоты и средней высоты для Идеально Сбалансированных Деревьев Поиска (ИСДП)
 * и Случайных Деревьев Поиска (СДП).
 */

class TheoryCalculations {
public:
    /**
     * @brief Теоретическая оценка высоты Идеально Сбалансированного Дерева
     * @param n Количество узлов в дереве
     * @return Теоретическая оценка высоты ИСДП
     *
     * @note Для идеально сбалансированного дерева высота оценивается как ⌊log₂(n)⌋
     */
    static double theoreticalHeightBalanced(int n);

    /**
     * @brief Теоретическая оценка средней высоты Идеально Сбалансированного Дерева
     * @param n Количество узлов в дереве
     * @return Теоретическая оценка средней высоты ИСДП
     *
     * @note Для ИСДП средняя высота близка к log₂(n) - 1
     */
    static double theoreticalAverageHeightBalanced(int n);

    /**
     * @brief Теоретическая оценка высоты Случайного Дерева Поиска
     * @param n Количество узлов в дереве
     * @return Теоретическая оценка высоты СДП
     *
     * @note Для случайного BST ожидаемая высота оценивается как ~2.99 * log₂(n)
     *       на основе результатов Льюиса-Дойча-Рандома
     */
    static double theoreticalHeightRandomBST(int n);

    /**
     * @brief Теоретическая оценка средней высоты Случайного Дерева Поиска
     * @param n Количество узлов в дереве
     * @return Теоретическая оценка средней высоты СДП
     *
     * @note Для случайного BST средняя высота пути оценивается как ~2 * ln(n)
     */
    static double theoreticalAverageHeightRandomBST(int n);

    /**
     * @brief Вычисление логарифма по основанию 2
     * @param x Аргумент логарифма
     * @return log₂(x)
     */
    static double log2(double x);

    /**
     * @brief Вычисление натурального логарифма
     * @param x Аргумент логарифма
     * @return ln(x)
     */
    static double ln(double x);
};

#endif // THEORY_CALCULATIONS_H