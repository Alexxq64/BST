#ifndef MEMORY_UTILS_H
#define MEMORY_UTILS_H

#include "tree_node.h"

/**
 * @file memory_utils.h
 * @brief Утилиты для работы с памятью и отладки утечек памяти
 *
 * Этот файл содержит вспомогательные функции для отслеживания
 * использования памяти и предотвращения утечек при работе с деревьями.
 */

class MemoryUtils {
public:
    /**
     * @brief Отладочная функция для создания узла с отслеживанием памяти
     * @param key Ключ нового узла
     * @return Указатель на созданный узел
     *
     * @note Используется только при определении DEBUG_MEMORY
     *       В релиз-версии работает как обычный new
     */
    static TreeNode* createTreeNode(int key);

    /**
     * @brief Отладочная функция для удаления узла с отслеживанием памяти
     * @param node Указатель на удаляемый узел
     *
     * @note Используется только при определении DEBUG_MEMORY
     *       В релиз-версии работает как обычный delete
     */
    static void deleteTreeNode(TreeNode* node);

    /**
     * @brief Проверка утечек памяти
     * @return Количество неосвобожденных узлов
     *
     * @note Используется только при определении DEBUG_MEMORY
     *       В релиз-версии всегда возвращает 0
     */
    static int checkMemoryLeaks();

    /**
     * @brief Принудительное освобождение всей памяти (аварийная очистка)
     *
     * @note Используется только при определении DEBUG_MEMORY
     *       В релиз-версии не делает ничего
     */
    static void emergencyCleanup();
};

#endif // MEMORY_UTILS_H