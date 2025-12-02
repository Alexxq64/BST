/**
 * @file theory_calculations.h
 * @brief Теоретические оценки характеристик деревьев поиска
 *
 * Этот файл содержит функции для вычисления теоретических оценок
 * высоты и средней высоты для различных типов деревьев поиска.
 */

#ifndef THEORY_CALCULATIONS_H
#define THEORY_CALCULATIONS_H

#include <cmath>

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
     * @brief Теоретическая оценка высоты B-дерева (ДБД)
     * @param n Количество ключей в дереве
     * @param t Минимальная степень B-дерева (t ≥ 2)
     * @return Теоретическая высота B-дерева
     *
     * @note Для t-дерева высота оценивается как ⌈log_m(n)⌉, где m = ceil(t/2)
     *       Для t=2 получаем 2-3 дерево
     */
    static int theoreticalDBHeight(int n, int t);

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