#include "tree_properties.h"
#include <algorithm>
#include <iostream>

/**
 * @file tree_properties.cpp
 * @brief Реализация функций вычисления характеристик деревьев
 */

 /**
  * @brief Вычисление размера дерева
  *
  * Использует рекурсивный подход для подсчета всех узлов в дереве.
  * Формула: size(node) = 1 + size(left) + size(right)
  */
int TreeProperties::calculateSize(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }

    return 1 + calculateSize(root->left) + calculateSize(root->right);
}

/**
 * @brief Вычисление высоты дерева
 *
 * Высота дерева определяется как максимальная длина пути от корня до листа.
 * Формула: height(node) = 1 + max(height(left), height(right))
 */
int TreeProperties::calculateHeight(TreeNode* root) {
    if (root == nullptr) {
        return 0;  // Высота пустого дерева -1 (альтернативно можно 0 для одного узла)
    }

    int leftHeight = calculateHeight(root->left);
    int rightHeight = calculateHeight(root->right);

    return 1 + std::max(leftHeight, rightHeight);
}

/**
 * @brief Вычисление контрольной суммы
 *
 * Контрольная сумма - это сумма всех ключей в дереве.
 * Используется для проверки, что два дерева содержат одинаковые данные.
 */
int TreeProperties::calculateCheckSum(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }

    return root->key + calculateCheckSum(root->left) + calculateCheckSum(root->right);
}

/**
 * @brief Вычисление средней высоты дерева
 *
 * Средняя высота вычисляется как среднее арифметическое длин путей
 * от корня до всех листьев дерева.
 */
double TreeProperties::calculateAverageHeight(TreeNode* root) {
    if (root == nullptr) {
        return 0.0;
    }

    double totalHeight = 0.0;
    int leafCount = 0;

    calculateAverageHeightRecursive(root, 0, totalHeight, leafCount);

    if (leafCount == 0) {
        return 0.0;
    }

    return totalHeight / leafCount;
}

/**
 * @brief Вспомогательная рекурсивная функция для вычисления средней высоты
 *
 * Обходит дерево и для каждого листа добавляет его глубину к общей сумме
 * и увеличивает счетчик листьев.
 */
void TreeProperties::calculateAverageHeightRecursive(TreeNode* node, int currentHeight,
    double& totalHeight, int& leafCount) {
    if (node == nullptr) {
        return;
    }

    // Если узел является листом (нет потомков)
    if (node->left == nullptr && node->right == nullptr) {
        totalHeight += currentHeight;
        leafCount++;
        return;
    }

    // Рекурсивно обходим левое и правое поддеревья
    calculateAverageHeightRecursive(node->left, currentHeight + 1, totalHeight, leafCount);
    calculateAverageHeightRecursive(node->right, currentHeight + 1, totalHeight, leafCount);
}

/**
 * @brief In-order обход дерева (левый-корень-правый)
 *
 * Для деревьев поиска возвращает отсортированную последовательность ключей.
 * Это полезно для проверки корректности построения BST.
 */
std::vector<int> TreeProperties::inOrderTraversal(TreeNode* root) {
    std::vector<int> result;
    inOrderRecursive(root, result);
    return result;
}

/**
 * @brief Рекурсивная реализация in-order обхода
 *
 * Алгоритм:
 * 1. Рекурсивно обойти левое поддерево
 * 2. Посетить текущий узел (добавить ключ в результат)
 * 3. Рекурсивно обойти правое поддерево
 */
void TreeProperties::inOrderRecursive(TreeNode* node, std::vector<int>& result) {
    if (node == nullptr) {
        return;
    }

    inOrderRecursive(node->left, result);
    result.push_back(node->key);
    inOrderRecursive(node->right, result);
}

/**
 * @brief Поиск узла в дереве поиска
 *
 * Использует свойства BST для эффективного поиска:
 * - Если ключ равен ключу текущего узла - узел найден
 * - Если ключ меньше - ищем в левом поддереве
 * - Если ключ больше - ищем в правом поддереве
 *
 * Временная сложность зависит от высоты дерева: O(h)
 */
TreeNode* TreeProperties::searchNode(TreeNode* root, int key) {
    TreeNode* current = root;

    while (current != nullptr) {
        if (key == current->key) {
            return current;  // Узел найден
        }
        else if (key < current->key) {
            current = current->left;  // Ищем в левом поддереве
        }
        else {
            current = current->right; // Ищем в правом поддереве
        }
    }

    return nullptr;  // Узел не найден
}

int TreeProperties::calculateCheckSumDB(DBNode* root) {
    if (!root) return 0;
    int sum = 0;
    for (int key : root->keys) sum += key;
    for (DBNode* child : root->children) sum += calculateCheckSumDB(child);
    return sum;
}

int TreeProperties::calculateLevelsDB(DBNode* root, int level) {
    if (!root) return 0;
    int sum = level * root->keys.size();
    for (DBNode* child : root->children) sum += calculateLevelsDB(child, level + 1);
    return sum;
}
