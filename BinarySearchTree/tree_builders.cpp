#include "tree_builders.h"
#include <algorithm>
#include <iostream>
#include <climits>

/**
 * @file tree_builders.cpp
 * @brief Реализация функций построения деревьев поиска: ИСДП, СДП, АВЛ и ДБД
 */

 // ================== ИСДП ==================

 /**
  * @brief Построение Идеально Сбалансированного Дерева Поиска (ИСДП)
  * @param sortedData Отсортированный массив уникальных чисел
  * @return Указатель на корень построенного ИСДП
  *
  * @note Проверяет, что массив отсортирован, и вызывает рекурсивную функцию построения.
  */
TreeNode* TreeBuilders::buildPerfectlyBalancedTree(const std::vector<int>& sortedData) {
    if (sortedData.empty()) return nullptr;

    if (!std::is_sorted(sortedData.begin(), sortedData.end())) {
        std::cerr << "Предупреждение: массив для ИСДП не отсортирован!" << std::endl;
    }

    return buildBalancedTreeRecursive(sortedData, 0, sortedData.size() - 1);
}

/**
 * @brief Рекурсивная функция построения ИСДП
 */
TreeNode* TreeBuilders::buildBalancedTreeRecursive(const std::vector<int>& sortedData, int start, int end) {
    if (start > end) return nullptr;

    int mid = start + (end - start) / 2;
    TreeNode* root = new TreeNode(sortedData[mid]);
    root->left = buildBalancedTreeRecursive(sortedData, start, mid - 1);
    root->right = buildBalancedTreeRecursive(sortedData, mid + 1, end);

    return root;
}

// ================== СДП ==================

/**
 * @brief Построение Случайного Дерева Поиска (СДП)
 */
TreeNode* TreeBuilders::buildRandomSearchTree(const std::vector<int>& data) {
    TreeNode* root = nullptr;
    for (int key : data) insertNode(root, key);
    return root;
}

/**
 * @brief Вставка узла в BST
 * @param root Корень дерева (может изменяться)
 * @param key Ключ для вставки
 */
void TreeBuilders::insertNode(TreeNode*& root, int key) {
    if (!root) {
        root = new TreeNode(key);
        return;
    }

    if (key < root->key) insertNode(root->left, key);
    else if (key > root->key) insertNode(root->right, key);
}

// ================== АВЛ ==================

/**
 * @brief Построение АВЛ-дерева
 * @param data Массив уникальных чисел
 * @return Указатель на корень АВЛ-дерева
 */
TreeNode* TreeBuilders::buildAVLTree(const std::vector<int>& data) {
    TreeNode* root = nullptr;
    for (int key : data) root = insertAVL(root, key);
    return root;
}

/**
 * @brief Вставка узла в АВЛ-дерево с балансировкой
 * @param node Указатель на текущий узел
 * @param key Ключ для вставки
 * @return Новый корень поддерева после вставки
 */
TreeNode* TreeBuilders::insertAVL(TreeNode* node, int key) {
    if (!node) return new TreeNode(key);

    if (key < node->key) node->left = insertAVL(node->left, key);
    else if (key > node->key) node->right = insertAVL(node->right, key);
    else return node; // уникальные ключи

    // Обновление высоты узла
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node);

    // Левый Левый случай
    if (balance > 1 && key < node->left->key) return rotateRight(node);

    // Правый Правый случай
    if (balance < -1 && key > node->right->key) return rotateLeft(node);

    // Левый Правый случай
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Правый Левый случай
    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

/**
 * @brief Получение высоты узла
 */
int TreeBuilders::getHeight(TreeNode* node) {
    return node ? node->height : 0;
}

/**
 * @brief Получение баланс-фактора узла
 */
int TreeBuilders::getBalance(TreeNode* node) {
    if (!node) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

/**
 * @brief Поворот поддерева влево
 * @param x Корень поддерева
 * @return Новый корень после поворота
 */
TreeNode* TreeBuilders::rotateLeft(TreeNode* x) {
    TreeNode* y = x->right;
    TreeNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + std::max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + std::max(getHeight(y->left), getHeight(y->right));

    return y;
}

/**
 * @brief Поворот поддерева вправо
 * @param y Корень поддерева
 * @return Новый корень после поворота
 */
TreeNode* TreeBuilders::rotateRight(TreeNode* y) {
    TreeNode* x = y->left;
    TreeNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + std::max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + std::max(getHeight(x->left), getHeight(x->right));

    return x;
}

// ================== Общие функции ==================

/**
 * @brief Проверка, является ли дерево деревом поиска
 * @param root Корень дерева
 * @return true если дерево является BST, иначе false
 */
bool TreeBuilders::isBinarySearchTree(TreeNode* root) {
    return isBSTRecursive(root, INT_MIN, INT_MAX);
}

/**
 * @brief Рекурсивная проверка BST
 */
bool TreeBuilders::isBSTRecursive(TreeNode* node, int minValue, int maxValue) {
    if (!node) return true;
    if (node->key <= minValue || node->key >= maxValue) return false;
    return isBSTRecursive(node->left, minValue, node->key) &&
        isBSTRecursive(node->right, node->key, maxValue);
}

/**
 * @brief Освобождение памяти, занятой деревом
 * @param root Корень дерева
 */
void TreeBuilders::deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// ================== ДБД ==================

/**
 * @brief Построение ДБД-дерева
 * @param data Массив ключей
 * @param t Минимальный порядок ДБД
 * @return Корень построенного дерева
 */
DBNode* TreeBuilders::buildDBTree(const std::vector<int>& data, int t) {
    DBNode* root = nullptr;
    for (int key : data) {
        insertDBNode(root, key, t, 0);
    }
    return root;
}

/**
 * @brief Вставка ключа в ДБД-дерево
 * @param node Указатель на текущий узел
 * @param key Ключ для вставки
 * @param t Минимальный порядок
 * @param level Уровень узла
 */
void TreeBuilders::insertDBNode(DBNode*& node, int key, int t, int level) {
    if (!node) {
        node = new DBNode(true, level);
        node->keys.push_back(key);
        return;
    }

    int i = node->keys.size() - 1;

    if (node->isLeaf) {
        // Вставка в лист
        node->keys.push_back(0);
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;

        if (node->keys.size() == 2 * t) {
            // Корень переполнен
            DBNode* newRoot = new DBNode(false, node->level);
            newRoot->children.push_back(node);
            splitChild(newRoot, 0, t);
            node = newRoot;
        }
    }
    else {
        // Вставка во внутренний узел
        while (i >= 0 && key < node->keys[i]) i--;
        i++;
        if (i < node->children.size() && node->children[i]->keys.size() == 2 * t) {
            splitChild(node, i, t);
            if (key > node->keys[i]) i++;
        }
        insertDBNode(node->children[i], key, t, level + 1);
    }
}

/**
 * @brief Разделение переполненного дочернего узла
 */
void TreeBuilders::splitChild(DBNode* parent, int index, int t) {
    DBNode* y = parent->children[index];
    DBNode* z = new DBNode(y->isLeaf, y->level);

    int midKey = y->keys[t];

    for (int j = t + 1; j < y->keys.size(); j++) z->keys.push_back(y->keys[j]);
    y->keys.resize(t);

    if (!y->isLeaf) {
        for (int j = t + 1; j <= y->children.size() - 1; j++) z->children.push_back(y->children[j]);
        y->children.resize(t + 1);
    }

    parent->children.insert(parent->children.begin() + index + 1, z);
    parent->keys.insert(parent->keys.begin() + index, midKey);
}

/**
 * @brief Освобождение памяти, занятой ДБД-деревом
 */
void TreeBuilders::deleteDBTree(DBNode* root) {
    if (!root) return;
    for (auto child : root->children) deleteDBTree(child);
    delete root;
}


void TreeBuilders::inOrderTraversalDB(DBNode* node, std::vector<int>& keys) {
    if (!node) return;
    if (!node->isLeaf) {
        for (size_t i = 0; i < node->children.size(); ++i) {
            inOrderTraversalDB(node->children[i], keys);
            if (i < node->keys.size()) keys.push_back(node->keys[i]);
        }
    }
    else {
        for (int key : node->keys) keys.push_back(key);
    }
}
