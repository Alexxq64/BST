#include "testing.h"
#include "data_generator.h"
#include "tree_builders.h"
#include "tree_properties.h"
#include <iostream>
#include <algorithm>
#include <cassert>

/**
 * @file testing.cpp
 * @brief Реализация функций демонстрации построения деревьев
 */

 /**
  * @brief Демонстрация построения ИСДП
  */
void Testing::demonstrateBalancedTree() {
    std::cout << "=== ДЕМОНСТРАЦИЯ ИСДП ===" << std::endl;

    std::vector<int> data = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector<int> sortedData = data;
    std::sort(sortedData.begin(), sortedData.end());
    TreeNode* ibTree = TreeBuilders::buildPerfectlyBalancedTree(sortedData);

    std::cout << "Структура ИСДП:" << std::endl;
    std::cout << "               5" << std::endl;
    std::cout << "              /   \\" << std::endl;
    std::cout << "             /     \\" << std::endl;
    std::cout << "            /       \\" << std::endl;
    std::cout << "           2         8" << std::endl;
    std::cout << "          / \\       / \\" << std::endl;
    std::cout << "         /   \\     /   \\" << std::endl;
    std::cout << "        1     3   6     9" << std::endl;
    std::cout << "               \\   \\     \\" << std::endl;
    std::cout << "                4   7     10" << std::endl;

    // Проверяем свойства ИСДП
    assert(TreeProperties::calculateSize(ibTree) == 10);
    assert(TreeProperties::calculateHeight(ibTree) == 4);
    assert(TreeBuilders::isBinarySearchTree(ibTree));
    assert(TreeProperties::searchNode(ibTree, 5) != nullptr);

    std::cout << "+ Размер: " << TreeProperties::calculateSize(ibTree) << " вершин" << std::endl;
    std::cout << "+ Высота: " << TreeProperties::calculateHeight(ibTree) << " вершин в самой длинной ветви" << std::endl;
    std::cout << "+ Является BST: ДА" << std::endl;
    std::cout << "+ Поиск работает корректно" << std::endl;

    TreeBuilders::deleteTree(ibTree);
    std::cout << std::endl;
}

/**
 * @brief Демонстрация построения СДП
 */
void Testing::demonstrateRandomTree() {
    std::cout << "=== ДЕМОНСТРАЦИЯ СДП ===" << std::endl;

    std::vector<int> data = { 7, 2, 9, 1, 5, 8, 3, 6, 4, 10 };
    TreeNode* spTree = TreeBuilders::buildRandomSearchTree(data);

    std::cout << "Структура СДП:" << std::endl;
    std::cout << "               7" << std::endl;
    std::cout << "              /   \\" << std::endl;
    std::cout << "             /     \\" << std::endl;
    std::cout << "            /       \\" << std::endl;
    std::cout << "           2         9" << std::endl;
    std::cout << "          / \\       / \\" << std::endl;
    std::cout << "         /   \\     /   \\" << std::endl;
    std::cout << "        1     5   8     10" << std::endl;
    std::cout << "             / \\" << std::endl;
    std::cout << "            /   \\" << std::endl;
    std::cout << "           3     6" << std::endl;
    std::cout << "            \\" << std::endl;
    std::cout << "             4" << std::endl;

    // Проверяем свойства СДП
    assert(TreeProperties::calculateSize(spTree) == 10);
    assert(TreeBuilders::isBinarySearchTree(spTree));
    assert(TreeProperties::searchNode(spTree, 7) != nullptr);

    std::cout << "+ Размер: " << TreeProperties::calculateSize(spTree) << " вершин" << std::endl;
    std::cout << "+ Высота: " << TreeProperties::calculateHeight(spTree) << " вершин в самой длинной ветви" << std::endl;
    std::cout << "+ Является BST: ДА" << std::endl;
    std::cout << "+ Поиск работает корректно" << std::endl;

    TreeBuilders::deleteTree(spTree);
    std::cout << std::endl;
}



/**
 * @brief Создание тестового дерева для демонстрации
 */
TreeNode* Testing::createTestTree() {
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(3);
    root->right = new TreeNode(8);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(4);
    root->right->right = new TreeNode(9);
    return root;
}