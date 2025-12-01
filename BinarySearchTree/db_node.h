#ifndef DB_NODE_H
#define DB_NODE_H

#include <vector>

/**
 * @file db_node.h
 * @brief Определение структуры узла для Двоичного Б-дерева поиска (ДБД)
 *
 * Каждый узел содержит несколько ключей (ключи упорядочены внутри узла)
 * и указатели на дочерние узлы (поддеревья).
 * Используется минимальная степень t (t >= 2), определяющая диапазон ключей в узле.
 */
struct DBNode {
    std::vector<int> keys;       // Ключи в узле, упорядоченные по возрастанию
    std::vector<DBNode*> children; // Указатели на потомков: size = keys.size() + 1
    bool isLeaf;                 // Признак листа
    int level;                   // Уровень узла в дереве (для анализа высоты)

    /**
     * @brief Конструктор нового узла
     * @param leaf true, если узел листовой
     * @param lvl уровень узла в дереве
     */
    DBNode(bool leaf, int lvl) : isLeaf(leaf), level(lvl) {}
};

#endif // DB_NODE_H
