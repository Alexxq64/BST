/**
 * @file testing.cpp
 * @brief Реализация функций демонстрации построения деревьев
 */

#include "testing.h"
#include "data_generator.h"
#include "tree_builders.h"
#include "tree_properties.h"
#include <iostream>
#include <algorithm>
#include <cassert>

 /**
  * @brief Демонстрация построения ИСДП
  *
  * @details
  * Создает пример идеально сбалансированного дерева из отсортированных данных.
  * Демонстрирует структуру дерева ASCII-графикой и проверяет основные свойства:
  * - Корректный размер (10 узлов)
  * - Высота (4 уровня)
  * - Свойство BST (упорядоченность)
  * - Корректность поиска
  */
void Testing::demonstrateBalancedTree() {
    std::cout << "=== ДЕМОНСТРАЦИЯ ИСДП ===" << std::endl;

    // Подготовка данных
    std::vector<int> data = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector<int> sortedData = data;
    std::sort(sortedData.begin(), sortedData.end());

    // Построение дерева
    TreeNode* ibTree = TreeBuilders::buildPerfectlyBalancedTree(sortedData);

    // Визуализация структуры дерева
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

    // Проверка свойств ИСДП
    assert(TreeProperties::calculateSize(ibTree) == 10);
    assert(TreeProperties::calculateHeight(ibTree) == 4);
    assert(TreeBuilders::isBinarySearchTree(ibTree));
    assert(TreeProperties::searchNode(ibTree, 5) != nullptr);

    // Вывод результатов проверки
    std::cout << "+ Размер: " << TreeProperties::calculateSize(ibTree) << " вершин" << std::endl;
    std::cout << "+ Высота: " << TreeProperties::calculateHeight(ibTree) << " вершин в самой длинной ветви" << std::endl;
    std::cout << "+ Является BST: ДА" << std::endl;
    std::cout << "+ Поиск работает корректно" << std::endl;

    // Очистка памяти
    TreeBuilders::deleteTree(ibTree);
    std::cout << std::endl;
}

/**
 * @brief Демонстрация построения СДП
 *
 * @details
 * Создает пример дерева поиска из неотсортированных данных.
 * Визуализирует структуру и проверяет базовые свойства BST.
 * СДП строится в порядке поступления данных без балансировки.
 */
void Testing::demonstrateRandomTree() {
    std::cout << "=== ДЕМОНСТРАЦИЯ СДП ===" << std::endl;

    // Неотсортированные данные для СДП
    std::vector<int> data = { 7, 2, 9, 1, 5, 8, 3, 6, 4, 10 };
    TreeNode* spTree = TreeBuilders::buildRandomSearchTree(data);

    // Визуализация структуры дерева
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

    // Проверка свойств СДП
    assert(TreeProperties::calculateSize(spTree) == 10);
    assert(TreeBuilders::isBinarySearchTree(spTree));
    assert(TreeProperties::searchNode(spTree, 7) != nullptr);

    // Вывод результатов проверки
    std::cout << "+ Размер: " << TreeProperties::calculateSize(spTree) << " вершин" << std::endl;
    std::cout << "+ Высота: " << TreeProperties::calculateHeight(spTree) << " вершин в самой длинной ветви" << std::endl;
    std::cout << "+ Является BST: ДА" << std::endl;
    std::cout << "+ Поиск работает корректно" << std::endl;

    // Очистка памяти
    TreeBuilders::deleteTree(spTree);
    std::cout << std::endl;
}

/**
 * @brief Демонстрация построения АВЛ-дерева
 *
 * @details
 * Построение АВЛ-дерева с пошаговой вставкой элементов.
 * Демонстрирует автоматическую балансировку после каждой вставки.
 * Отслеживает изменение размера и высоты дерева.
 */
void Testing::demonstrateAVLTree() {
    std::cout << "=== ДЕМОНСТРАЦИЯ АВЛ ===" << std::endl;

    // Данные для построения АВЛ-дерева
    std::vector<int> data = { 24, 26, 67, 76, 78, 215, 359, 511, 650, 786 };
    TreeNode* avlTree = nullptr;

    // Пошаговая вставка с выводом информации
    for (int key : data) {
        avlTree = TreeBuilders::insertAVL(avlTree, key);
        std::cout << "Вставка: " << key << std::endl;
        std::cout << "+ Текущий размер: " << TreeProperties::calculateSize(avlTree)
            << ", высота: " << TreeProperties::calculateHeight(avlTree) << std::endl;
    }

    // Проверка свойств АВЛ-дерева
    assert(TreeBuilders::isBinarySearchTree(avlTree));
    assert(TreeProperties::searchNode(avlTree, 76) != nullptr);

    // Итоговые характеристики
    std::cout << "+ Размер: " << TreeProperties::calculateSize(avlTree) << " вершин" << std::endl;
    std::cout << "+ Высота: " << TreeProperties::calculateHeight(avlTree) << " вершин в самой длинной ветви" << std::endl;
    std::cout << "+ Является BST: ДА" << std::endl;
    std::cout << "+ Поиск работает корректно" << std::endl;

    // Очистка памяти
    TreeBuilders::deleteTree(avlTree);
    std::cout << std::endl;
}

/**
 * @brief Демонстрация построения B-дерева (ДБД)
 *
 * @details
 * Построение двоичного B-дерева с минимальной степенью t=2.
 * Демонстрирует in-order обход и проверяет основные свойства:
 * - Корректность обхода (упорядоченность ключей)
 * - Размер дерева
 * - Высоту дерева
 * - Работоспособность поиска
 */
void Testing::demonstrateDBTree() {
    std::cout << "=== ДЕМОНСТРАЦИЯ ДБД ===" << std::endl;

    // Данные для построения B-дерева
    std::vector<int> data = { 10, 20, 5, 6, 12, 30, 7, 17 };
    int t = 2; // минимальный порядок (2-3 дерево)

    // Построение дерева
    DBNode* dbTree = TreeBuilders::buildDBTree(data, t);

    // In-order обход для проверки упорядоченности
    std::vector<int> keys;
    TreeBuilders::inOrderTraversalDB(dbTree, keys);

    std::cout << "In-order обход ДБД:" << std::endl;
    for (int key : keys) std::cout << key << " ";
    std::cout << std::endl;

    // Проверка свойств B-дерева
    int size = keys.size();
    int height = TreeProperties::calculateHeightDB(dbTree);

    std::cout << "+ Размер: " << size << " вершин" << std::endl;
    std::cout << "+ Высота: " << height << " вершин в самой длинной ветви" << std::endl;
    std::cout << "+ Поиск (ключ 12): "
        << (TreeProperties::searchNodeDB(dbTree, 12) ? "ДА" : "НЕТ") << std::endl;

    // Очистка памяти
    TreeBuilders::deleteDBTree(dbTree);
    std::cout << std::endl;
}

/**
 * @brief Создание тестового дерева для демонстрации
 *
 * @return TreeNode* Указатель на корень тестового дерева
 *
 * @details
 * future feature
 * Создает простое тестовое дерево с фиксированной структурой:
 *         5
 *        / \
 *       3   8
 *      / \   \
 *     1   4   9
 *
 * Используется для демонстрации и тестирования базовых операций.
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