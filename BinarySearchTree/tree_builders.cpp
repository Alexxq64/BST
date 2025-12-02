/**
 * @file tree_builders.cpp
 * @brief Реализация функций построения деревьев поиска: ИСДП, СДП, АВЛ и ДБД
 */

#include "tree_builders.h"
#include <algorithm>
#include <iostream>
#include <climits>

 // ================== ИСДП ==================

 /**
  * @brief Построение Идеально Сбалансированного Дерева Поиска (ИСДП)
  * @param sortedData Отсортированный массив уникальных чисел
  * @return Указатель на корень построенного ИСДП
  *
  * @details
  * Использует стратегию "разделяй и властвуй": выбирает средний элемент
  * массива в качестве корня, затем рекурсивно строит левое и правое поддеревья.
  * Гарантирует минимальную высоту дерева.
  *
  * @note Требует отсортированного массива на входе.
  * @warning Проверяет отсортированность массива, выводит предупреждение если не отсортирован.
  */
TreeNode* TreeBuilders::buildPerfectlyBalancedTree(const std::vector<int>& sortedData) {
    if (sortedData.empty()) return nullptr;

    // Проверка отсортированности массива (опционально, для отладки)
    if (!std::is_sorted(sortedData.begin(), sortedData.end())) {
        std::cerr << "Предупреждение: массив для ИСДП не отсортирован!" << std::endl;
    }

    return buildBalancedTreeRecursive(sortedData, 0, sortedData.size() - 1);
}

/**
 * @brief Рекурсивная функция построения ИСДП
 * @param sortedData Отсортированный массив данных
 * @param start Начальный индекс подмассива
 * @param end Конечный индекс подмассива
 * @return Указатель на корень построенного поддерева
 *
 * @details
 * Алгоритм:
 * 1. Если start > end, возвращаем nullptr (пустое поддерево)
 * 2. Вычисляем средний индекс: mid = start + (end - start) / 2
 * 3. Создаем узел с ключом sortedData[mid]
 * 4. Рекурсивно строим левое поддерево из элементов [start, mid-1]
 * 5. Рекурсивно строим правое поддерево из элементов [mid+1, end]
 *
 * @note Гарантирует сбалансированность: разница высот поддеревьев ≤ 1
 */
TreeNode* TreeBuilders::buildBalancedTreeRecursive(const std::vector<int>& sortedData, int start, int end) {
    if (start > end) return nullptr;

    int mid = start + (end - start) / 2; // Избегаем переполнения
    TreeNode* root = new TreeNode(sortedData[mid]);
    root->left = buildBalancedTreeRecursive(sortedData, start, mid - 1);
    root->right = buildBalancedTreeRecursive(sortedData, mid + 1, end);

    return root;
}

// ================== СДП ==================

/**
 * @brief Построение Случайного Дерева Поиска (СДП)
 * @param data Массив чисел (не обязательно отсортированный)
 * @return Указатель на корень построенного СДП
 *
 * @details
 * Строит BST путем последовательной вставки элементов в том порядке,
 * в котором они идут в массиве. Высота дерева зависит от порядка вставки.
 *
 * @note Для случайных данных ожидаемая высота ~2.99*log₂(n)
 * @note Для отсортированных данных вырождается в список высотой n
 */
TreeNode* TreeBuilders::buildRandomSearchTree(const std::vector<int>& data) {
    TreeNode* root = nullptr;
    for (int key : data) insertNode(root, key);
    return root;
}

/**
 * @brief Вставка узла в BST
 * @param root Корень дерева (передается по ссылке)
 * @param key Ключ для вставки
 *
 * @details
 * Вставляет новый узел в бинарное дерево поиска, сохраняя свойство BST:
 * - Все ключи в левом поддереве меньше ключа корня
 * - Все ключи в правом поддереве больше ключа корня
 *
 * @note Рекурсивная реализация
 */
void TreeBuilders::insertNode(TreeNode*& root, int key) {
    if (!root) {
        root = new TreeNode(key);
        return;
    }

    if (key < root->key) insertNode(root->left, key);
    else if (key > root->key) insertNode(root->right, key);
    // Игнорируем дубликаты (по условию все ключи уникальны)
}

// ================== АВЛ ==================

/**
 * @brief Построение АВЛ-дерева
 * @param data Массив уникальных чисел
 * @return Указатель на корень АВЛ-дерева
 *
 * @details
 * Строит самобалансирующееся бинарное дерево поиска, в котором для каждой вершины
 * высота двух поддеревьев различается не более чем на 1.
 * Обеспечивает гарантированную высоту O(log n).
 *
 * @note Выполняет балансировку после каждой вставки
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
 * @return Новый корень поддерева после вставки и балансировки
 *
 * @details
 * Алгоритм:
 * 1. Рекурсивная вставка как в обычном BST
 * 2. Обновление высоты текущего узла
 * 3. Вычисление баланс-фактора
 * 4. Проверка четырех случаев нарушения баланса и выполнение соответствующих поворотов
 *
 * @note Баланс-фактор = высота(левое_поддерево) - высота(правое_поддерево)
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
 * @param node Указатель на узел
 * @return Высота узла (0 для nullptr)
 */
int TreeBuilders::getHeight(TreeNode* node) {
    return node ? node->height : 0;
}

/**
 * @brief Получение баланс-фактора узла
 * @param node Указатель на узел
 * @return Разность высот левого и правого поддеревьев
 *
 * @note Положительное значение: левое поддерево выше
 * @note Отрицательное значение: правое поддерево выше
 */
int TreeBuilders::getBalance(TreeNode* node) {
    if (!node) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

/**
 * @brief Поворот поддерева влево
 * @param x Корень поддерева до поворота
 * @return Новый корень поддерева после поворота
 *
 * @details
 * Используется для балансировки АВЛ-дерева при правом перевесе.
 * Пример:
 *      x              y
 *       \            / \
 *        y    ->    x   z
 *         \
 *          z
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
 * @param y Корень поддерева до поворота
 * @return Новый корень поддерева после поворота
 *
 * @details
 * Используется для балансировки АВЛ-дерева при левом перевесе.
 * Пример:
 *        y          x
 *       /          / \
 *      x    ->    z   y
 *     /
 *    z
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
 * @brief Проверка, является ли дерево деревом поиска (BST)
 * @param root Корень дерева
 * @return true если дерево является BST, иначе false
 *
 * @details
 * Проверяет выполнение свойства BST:
 * - Все ключи в левом поддереве меньше ключа корня
 * - Все ключи в правом поддереве больше ключа корня
 * - Оба поддерева также являются BST
 *
 * @note Использует рекурсивную проверку с передачей допустимых границ ключей
 */
bool TreeBuilders::isBinarySearchTree(TreeNode* root) {
    return isBSTRecursive(root, INT_MIN, INT_MAX);
}

/**
 * @brief Рекурсивная проверка BST
 * @param node Текущий узел
 * @param minValue Минимально допустимое значение ключа
 * @param maxValue Максимально допустимое значение ключа
 * @return true если поддерево является BST, иначе false
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
 *
 * @details
 * Выполняет пост-порядковый обход дерева (левый-правый-корень)
 * для корректного освобождения памяти всех узлов.
 *
 * @note Рекурсивная реализация
 * @warning Не вызывает delete для nullptr
 */
void TreeBuilders::deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// ================== ДБД ==================

/**
 * @brief Построение B-дерева (ДБД)
 * @param data Массив ключей для вставки
 * @param t Минимальный порядок B-дерева (t ≥ 2)
 * @return Корень построенного B-дерева
 *
 * @details
 * Строит B-дерево заданного порядка t путем последовательной вставки ключей.
 * B-дерево сохраняет балансировку автоматически за счет свойств:
 * - Каждый узел содержит от t-1 до 2t-1 ключей (кроме корня)
 * - Все листья находятся на одном уровне
 *
 * @note Для t=2 получаем 2-3 дерево
 */
DBNode* TreeBuilders::buildDBTree(const std::vector<int>& data, int t) {
    DBNode* root = nullptr;
    for (int key : data) {
        insertDBNode(root, key, t, 0);
    }
    return root;
}

/**
 * @brief Вставка ключа в B-дерево
 * @param node Ссылка на указатель текущего узла (может измениться)
 * @param key Ключ для вставки
 * @param t Минимальный порядок дерева
 * @param level Уровень текущего узла (0 для корня)
 *
 * @details
 * Рекурсивная вставка с разделением переполненных узлов.
 * Если узел переполняется (имеет 2t ключей), он разделяется на два узла
 * по t-1 ключей каждый, а средний ключ поднимается в родительский узел.
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
 * @param parent Родительский узел
 * @param index Индекс дочернего узла для разделения
 * @param t Минимальный порядок дерева
 *
 * @details
 * Разделяет переполненный узел y на два узла (y и z) и поднимает средний ключ
 * в родительский узел. Алгоритм:
 * 1. Создает новый узел z
 * 2. Переносит последние t-1 ключей из y в z
 * 3. Переносит последние t дочерних узлов из y в z (если y не лист)
 * 4. Вставляет средний ключ y в parent
 * 5. Добавляет z как дочерний узел parent
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
 * @brief Освобождение памяти, занятой B-деревом
 * @param root Корень B-дерева
 *
 * @details
 * Рекурсивно удаляет все узлы дерева в порядке пост-порядкового обхода.
 */
void TreeBuilders::deleteDBTree(DBNode* root) {
    if (!root) return;
    for (auto child : root->children) deleteDBTree(child);
    delete root;
}

/**
 * @brief In-order обход B-дерева
 * @param node Текущий узел
 * @param keys Вектор для сохранения ключей в отсортированном порядке
 *
 * @details
 * Выполняет обход B-дерева, возвращая ключи в возрастающем порядке.
 * Алгоритм:
 * 1. Рекурсивно обходит все дочерние узлы
 * 2. После каждого дочернего узла добавляет соответствующий ключ
 * 3. Для листовых узлов добавляет все ключи
 *
 * @note Результат всегда отсортирован для корректного B-дерева
 */
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