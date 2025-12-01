#ifndef TREE_BUILDERS_H
#define TREE_BUILDERS_H

#include "tree_node.h"
#include "db_node.h"
#include <vector>

/**
 * @file tree_builders.h
 * @brief Построение различных типов деревьев поиска
 *
 * Этот класс содержит функции для построения:
 *  - Идеально Сбалансированного Дерева Поиска (ИСДП)
 *  - Случайного Дерева Поиска (СДП)
 *  - АВЛ-дерева
 *  - Двоичного Б-дерева поиска (ДБД)
 *
 * Все методы статические, так как не требуется хранение состояния объекта.
 */
class TreeBuilders {
public:
    // ==== ИСДП ====

    /**
     * @brief Построение Идеально Сбалансированного Дерева Поиска (ИСДП)
     * @param sortedData Отсортированный массив уникальных чисел
     * @return Указатель на корень построенного ИСДП
     *
     * @note Массив должен быть отсортирован. Алгоритм выбирает средний элемент как корень.
     */
    static TreeNode* buildPerfectlyBalancedTree(const std::vector<int>& sortedData);

    // ==== СДП ====

    /**
     * @brief Построение Случайного Дерева Поиска (СДП)
     * @param data Массив чисел (может быть неотсортированным)
     * @return Указатель на корень построенного СДП
     *
     * @note Элементы вставляются в порядке массива. Дерево "случайное".
     */
    static TreeNode* buildRandomSearchTree(const std::vector<int>& data);

    // ==== АВЛ ====

    /**
     * @brief Построение АВЛ-дерева из массива данных
     * @param data Массив уникальных чисел
     * @return Указатель на корень АВЛ-дерева
     *
     * @note Для каждого элемента вызывается insertAVL с балансировкой.
     */
    static TreeNode* buildAVLTree(const std::vector<int>& data);

    /**
     * @brief Вставка узла в АВЛ-дерево с балансировкой
     * @param node Указатель на текущий узел
     * @param key Ключ для вставки
     * @return Новый корень поддерева после вставки
     *
     * @note Автоматически выполняются повороты для сохранения балансировки.
     */
    static TreeNode* insertAVL(TreeNode* node, int key);

    // ==== ДБД ====

    /**
     * @brief Построение Двоичного Б-дерева поиска (ДБД) с минимальной степенью t
     * @param data Массив уникальных чисел
     * @param t Минимальная степень узла (t >= 2)
     * @return Указатель на корень ДБД
     */
    static DBNode* buildDBTree(const std::vector<int>& data, int t);

    /**
     * @brief Вставка ключа в ДБД
     * @param node Узел дерева
     * @param key Вставляемый ключ
     * @param t Минимальная степень узла
     */
    static void insertDBNode(DBNode*& node, int key, int t, int level = 0);

    /**
     * @brief Разделение дочернего узла при переполнении
     * @param parent Родительский узел
     * @param index Индекс дочернего узла в массиве детей
     * @param t Минимальная степень узла
     */
    static void splitChild(DBNode* parent, int index, int t);

    /**
     * @brief Освобождение памяти ДБД
     * @param root Корень дерева
     */
    static void deleteDBTree(DBNode* root);

    // ==== Общие функции ====

    /**
     * @brief Проверка, является ли дерево деревом поиска
     * @param root Корень дерева
     * @return true если дерево является BST, иначе false
     */
    static bool isBinarySearchTree(TreeNode* root);

    /**
     * @brief Освобождение памяти, занятой деревом
     * @param root Корень дерева
     *
     * @important Всегда вызывайте после работы с деревом, чтобы избежать утечек памяти.
     */
    static void deleteTree(TreeNode* root);


    // В секции ДБД
    static void inOrderTraversalDB(DBNode* node, std::vector<int>& keys);


private:
    // ==== Вспомогательные для ИСДП ====

    /**
     * @brief Рекурсивная функция для построения ИСДП
     * @param sortedData Отсортированный массив
     * @param start Начальный индекс подмассива
     * @param end Конечный индекс подмассива
     * @return Корень поддерева
     */
    static TreeNode* buildBalancedTreeRecursive(const std::vector<int>& sortedData, int start, int end);

    // ==== Вспомогательные для СДП ====

    /**
     * @brief Вставка узла в СДП (BST)
     * @param root Корень дерева (может изменяться)
     * @param key Ключ для вставки
     */
    static void insertNode(TreeNode*& root, int key);

    // ==== Вспомогательные для BST-проверки ====

    /**
     * @brief Рекурсивная проверка BST
     * @param node Текущий узел
     * @param minValue Минимальное допустимое значение
     * @param maxValue Максимальное допустимое значение
     * @return true если поддерево является BST
     */
    static bool isBSTRecursive(TreeNode* node, int minValue, int maxValue);

    // ==== Вспомогательные для АВЛ ====

    /**
     * @brief Получение высоты узла
     * @param node Узел дерева
     * @return Высота узла (0 если nullptr)
     */
    static int getHeight(TreeNode* node);

    /**
     * @brief Получение баланс-фактора узла
     * @param node Узел дерева
     * @return Разница высот левого и правого поддеревьев
     */
    static int getBalance(TreeNode* node);

    /**
     * @brief Поворот поддерева влево
     * @param x Корень поддерева
     * @return Новый корень после поворота
     */
    static TreeNode* rotateLeft(TreeNode* x);

    /**
     * @brief Поворот поддерева вправо
     * @param y Корень поддерева
     * @return Новый корень после поворота
     */
    static TreeNode* rotateRight(TreeNode* y);

};

#endif // TREE_BUILDERS_H
