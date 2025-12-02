/**
 * @file output_utils.h
 * @brief Утилиты для вывода данных и форматирования результатов
 *
 * Этот файл содержит функции для красивого вывода деревьев,
 * таблиц результатов и других данных.
 */

#ifndef OUTPUT_UTILS_H
#define OUTPUT_UTILS_H

#include "tree_node.h"
#include <vector>
#include <string>

class OutputUtils {
public:
    /**
     * @brief Вывод дерева в виде скобочной записи
     * @param root Указатель на корень дерева
     *
     * Формат: (корень левое-поддерево правое-поддерево)
     * Пример: (5 (3 (1) (4)) (8 (7) (9)))
     */
    static void printTreeBracket(TreeNode* root);

    /**
     * @brief Вывод in-order обхода дерева
     * @param root Указатель на корень дерева
     * @param title Заголовок для вывода
     *
     * Выводит последовательность ключей в порядке in-order обхода
     */
    static void printInOrder(TreeNode* root, const std::string& title = "In-order обход:");

    /**
     * @brief Вывод in-order обхода дерева с репрезентативной выборкой
     * @param root Указатель на корень дерева
     * @param title Заголовок для вывода
     *
     * Выводит первые 5 элементов, 5 элементов из середины (разделенных через ...)
     * и последние 5 элементов для больших деревьев.
     */
    static void printInOrderSampled(TreeNode* root, const std::string& title = "In-order обход:");

    /**
     * @brief Вывод характеристик дерева
     * @param root Указатель на корень дерева
     * @param treeName Название дерева (для заголовка)
     *
     * Выводит размер, высоту, контрольную сумму и среднюю высоту
     */
    static void printTreeProperties(TreeNode* root, const std::string& treeName);

    /**
     * @brief Вывод заголовка таблицы результатов
     * @param leftGroup Название левой группы деревьев (например, "СДП")
     * @param rightGroup Название правой группы деревьев (например, "ИСДП")
     *
     * Выводит форматированный заголовок для таблицы 1 из задания
     */
    static void printTableHeader(
        const std::string& leftGroup,
        const std::string& rightGroup
    );

    /**
     * @brief Вывод строки таблицы для одного размера дерева
     * @param size Размер дерева
     * @param checkSumSP Контрольная сумма СДП
     * @param heightSP Высота СДП
     * @param theoreticalAvgHeightSP Теоретическая оценка средней высоты СДП
     * @param checkSumIB Контрольная сумма ИСДП
     * @param heightIB Высота ИСДП
     * @param theoreticalAvgHeightIB Теоретическая оценка средней высоты ИСДП
     */
    static void printTableRow(int size,
        int checkSumSP, double heightSP, double theoreticalAvgHeightSP,
        int checkSumIB, double heightIB, double theoreticalAvgHeightIB);

    /**
     * @brief Вывод теоретических оценок
     * @param sizes Вектор размеров деревьев
     *
     * Выводит таблицу с теоретическими оценками для сравнения с практическими результатами
     */
    static void printTheoreticalEstimates(const std::vector<int>& sizes);

    /**
     * @brief Вывод заголовка таблицы для сравнения АВЛ и ДБД
     *
     * Выводит форматированный заголовок таблицы для лабораторной работы 3.
     * Таблица содержит сравнение характеристик АВЛ-деревьев и B-деревьев.
     */
    static void printDBTableHeader();

    /**
     * @brief Вывод строки таблицы для сравнения АВЛ и ДБД
     * @param size Размер дерева (количество элементов)
     * @param avlCheckSum Контрольная сумма АВЛ-дерева
     * @param avlHeight Фактическая высота АВЛ-дерева
     * @param avlAvg Теоретическая средняя высота АВЛ-дерева
     * @param dbCheckSum Контрольная сумма B-дерева
     * @param dbLevels Фактическое количество уровней B-дерева
     * @param dbHeightTheo Теоретическая высота B-дерева
     * @param dbAvgTheo Теоретическая средняя высота B-дерева
     */
    static void printDBTableRow(int size,
        int avlCheckSum, int avlHeight, double avlAvg,
        int dbCheckSum, int dbLevels, double dbHeightTheo, double dbAvgTheo);

private:
    /**
     * @brief Рекурсивная функция для вывода скобочной записи
     * @param node Текущий узел
     */
    static void printTreeBracketRecursive(TreeNode* node);
};

#endif // OUTPUT_UTILS_H