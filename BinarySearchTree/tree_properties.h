#ifndef TREE_PROPERTIES_H
#define TREE_PROPERTIES_H

#include "tree_node.h"
#include <vector>

/**
 * @file tree_properties.h
 * @brief Вычисление характеристик бинарных деревьев
 *
 * Этот файл содержит функции для вычисления различных характеристик
 * бинарных деревьев: размера, высоты, контрольной суммы и средней высоты.
 */

class TreeProperties {
public:
    /**
     * @brief Вычисление размера дерева (количество узлов)
     * @param root Указатель на корень дерева
     * @return Количество узлов в дереве
     *
     * @note Размер пустого дерева равен 0.
     */
    static int calculateSize(TreeNode* root);

    /**
     * @brief Вычисление высоты дерева
     * @param root Указатель на корень дерева
     * @return Высота дерева (максимальная длина пути от корня до листа)
     *
     * @note Высота пустого дерева равна -1, высота дерева из одного узла равна 0.
     */
    static int calculateHeight(TreeNode* root);

    /**
     * @brief Вычисление контрольной суммы данных дерева
     * @param root Указатель на корень дерева
     * @return Сумма ключей всех узлов дерева
     *
     * @note Контрольная сумма используется для проверки корректности данных
     *       при сравнении различных представлений одного набора данных.
     */
    static int calculateCheckSum(TreeNode* root);

    /**
     * @brief Вычисление средней высоты дерева
     * @param root Указатель на корень дерева
     * @return Средняя высота дерева (средняя длина пути от корня до всех листьев)
     *
     * @note Средняя высота вычисляется как сумма длин путей до всех листьев,
     *       деленная на количество листьев.
     */
    static double calculateAverageHeight(TreeNode* root);

    /**
     * @brief Обход дерева слева направо (in-order traversal)
     * @param root Указатель на корень дерева
     * @return Вектор ключей в порядке in-order обхода
     *
     * @note In-order обход для BST возвращает отсортированную последовательность.
     */
    static std::vector<int> inOrderTraversal(TreeNode* root);

    /**
     * @brief Поиск узла с заданным ключом в дереве поиска
     * @param root Указатель на корень дерева поиска
     * @param key Ключ для поиска
     * @return Указатель на найденный узел или nullptr если узел не найден
     *
     * @note Функция работает только для деревьев поиска (BST).
     *       Временная сложность: O(h), где h - высота дерева.
     */
    static TreeNode* searchNode(TreeNode* root, int key);

private:
    /**
     * @brief Вспомогательная функция для вычисления средней высоты
     * @param node Текущий узел
     * @param currentHeight Текущая глубина узла
     * @param totalHeight Суммарная высота (аккумулируется)
     * @param leafCount Количество листьев (аккумулируется)
     *
     * Рекурсивно обходит дерево и аккумулирует данные для вычисления средней высоты.
     */
    static void calculateAverageHeightRecursive(TreeNode* node, int currentHeight,
        double& totalHeight, int& leafCount);

    /**
     * @brief Вспомогательная функция для in-order обхода
     * @param node Текущий узел
     * @param result Вектор для сохранения результата
     *
     * Рекурсивно выполняет обход в порядке: левое поддерево -> узел -> правое поддерево.
     */
    static void inOrderRecursive(TreeNode* node, std::vector<int>& result);
};

#endif // TREE_PROPERTIES_H