#include "tree_builders.h"
#include <algorithm>
#include <iostream>
#include <climits>

/**
 * @file tree_builders.cpp
 * @brief Реализация функций построения деревьев поиска
 */

 /**
  * @brief Построение Идеально Сбалансированного Дерева Поиска
  *
  * Основная функция-обертка для рекурсивного построения ИСДП.
  * Перед построением проверяет, что массив отсортирован.
  */
TreeNode* TreeBuilders::buildPerfectlyBalancedTree(const std::vector<int>& sortedData) {
    if (sortedData.empty()) {
        return nullptr;
    }

    // Проверяем, что массив отсортирован (для корректности ИСДП)
    if (!std::is_sorted(sortedData.begin(), sortedData.end())) {
        std::cerr << "Предупреждение: массив для ИСДП не отсортирован!" << std::endl;
    }

    return buildBalancedTreeRecursive(sortedData, 0, sortedData.size() - 1);
}

/**
 * @brief Рекурсивное построение ИСДП
 *
 * Алгоритм:
 * 1. Находим средний элемент текущего подмассива
 * 2. Создаем узел с этим значением
 * 3. Рекурсивно строим левое поддерево из левой половины
 * 4. Рекурсивно строим правое поддерево из правой половины
 *
 * Временная сложность: O(n)
 */
TreeNode* TreeBuilders::buildBalancedTreeRecursive(const std::vector<int>& sortedData, int start, int end) {
    // Базовый случай рекурсии
    if (start > end) {
        return nullptr;
    }

    // Находим средний элемент для поддержания баланса
    int mid = start + (end - start) / 2;

    // Создаем узел с средним элементом
    TreeNode* root = new TreeNode(sortedData[mid]);

    // Рекурсивно строим левое и правое поддеревья
    root->left = buildBalancedTreeRecursive(sortedData, start, mid - 1);
    root->right = buildBalancedTreeRecursive(sortedData, mid + 1, end);

    return root;
}

/**
 * @brief Построение Случайного Дерева Поиска
 *
 * Элементы вставляются в дерево в том порядке, в котором они находятся в массиве.
 * Структура дерева зависит от порядка элементов, что делает его "случайным".
 */
TreeNode* TreeBuilders::buildRandomSearchTree(const std::vector<int>& data) {
    TreeNode* root = nullptr;

    for (int key : data) {
        insertNode(root, key);
    }

    return root;
}

/**
 * @brief Вставка узла в дерево поиска
 *
 * Алгоритм вставки в BST:
 * - Если дерево пустое, создаем новый корень
 * - Если ключ меньше корня, идем в левое поддерево
 * - Если ключ больше корня, идем в правое поддерево
 * - Рекурсивно повторяем до нахождения места для вставки
 */
void TreeBuilders::insertNode(TreeNode*& root, int key) {
    if (root == nullptr) {
        root = new TreeNode(key);
        return;
    }

    if (key < root->key) {
        insertNode(root->left, key);
    }
    else if (key > root->key) {
        insertNode(root->right, key);
    }
    // Если ключ уже существует, игнорируем (по условию все ключи уникальны)
}

/**
 * @brief Проверка, является ли дерево деревом поиска
 *
 * Использует вспомогательную рекурсивную функцию с ограничениями min/max
 * для каждого поддерева.
 */
bool TreeBuilders::isBinarySearchTree(TreeNode* root) {
    return isBSTRecursive(root, INT_MIN, INT_MAX);
}

/**
 * @brief Рекурсивная проверка условий BST
 *
 * Для каждого узла проверяет:
 * - Значение должно быть в диапазоне (minValue, maxValue)
 * - Левое поддерево должно содержать значения < текущего узла
 * - Правое поддерево должно содержать значения > текущего узла
 */
bool TreeBuilders::isBSTRecursive(TreeNode* node, int minValue, int maxValue) {
    if (node == nullptr) {
        return true;
    }

    // Проверяем, что значение узла находится в допустимом диапазоне
    if (node->key <= minValue || node->key >= maxValue) {
        return false;
    }

    // Рекурсивно проверяем левое и правое поддеревья
    // Для левого поддерева максимальное значение - текущий узел
    // Для правого поддерева минимальное значение - текущий узел
    return isBSTRecursive(node->left, minValue, node->key) &&
        isBSTRecursive(node->right, node->key, maxValue);
}

/**
 * @brief Освобождение памяти дерева (пост-порядковый обход)
 *
 * Удаляет узлы в порядке: левое поддерево -> правое поддерево -> корень
 * Это гарантирует корректное удаление без обращения к уже удаленной памяти.
 */
void TreeBuilders::deleteTree(TreeNode* root) {
    if (root == nullptr) {
        return;
    }

    // Рекурсивно удаляем левое и правое поддеревья
    deleteTree(root->left);
    deleteTree(root->right);

    // Удаляем текущий узел
    delete root;
}