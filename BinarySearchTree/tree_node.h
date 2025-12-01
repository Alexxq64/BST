#ifndef TREE_NODE_H
#define TREE_NODE_H

/**
 * @file tree_node.h
 * @brief Узел бинарного дерева / АВЛ-дерева
 *
 * Для лабораторной 2 (АВЛ) добавлено поле height — высота поддерева,
 * необходимая для расчёта баланс-фактора и выполнения поворотов.
 */

 // Узел бинарного дерева / АВЛ-дерева
struct TreeNode {
    int key;           // Ключ узла
    TreeNode* left;    // Левое поддерево
    TreeNode* right;   // Правое поддерево
    int height;        // Высота поддерева с данным узлом

    /**
     * @brief Конструктор узла
     * @param k значение ключа
     *
     * Создаёт узел-лист с высотой 1 (как принято в АВЛ).
     */
    TreeNode(int k)
        : key(k), left(nullptr), right(nullptr), height(1) {
    }
};

#endif // TREE_NODE_H
