/**
 * @file memory_utils.h
 * @brief Утилиты для работы с памятью и отладки утечек памяти
 */

#ifndef MEMORY_UTILS_H
#define MEMORY_UTILS_H

#include "tree_node.h"

class MemoryUtils {
public:
    /**
     * @brief Создание узла с отслеживанием памяти
     * @param key Ключ нового узла
     * @return Указатель на созданный узел
     */
    static TreeNode* createTreeNode(int key);

    /**
     * @brief Удаление узла с отслеживанием памяти
     * @param node Указатель на удаляемый узел
     */
    static void deleteTreeNode(TreeNode* node);

    /**
     * @brief Проверка утечек памяти
     * @return Количество неосвобожденных узлов
     */
    static int checkMemoryLeaks();

    /**
     * @brief Аварийная очистка всей памяти
     */
    static void emergencyCleanup();
};

#endif // MEMORY_UTILS_H