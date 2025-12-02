/**
 * @file memory_utils.cpp
 * @brief Реализация утилит для работы с памятью
 *
 * @details
 * Реализация отслеживания выделения и освобождения памяти для узлов деревьев.
 * В режиме отладки (DEBUG_MEMORY) ведется учет всех созданных узлов для
 * обнаружения утечек памяти.
 */

#include "memory_utils.h"
#include <iostream>
#include <unordered_set>

 // Глобальные переменные для отслеживания памяти (только для отладки)
#ifdef DEBUG_MEMORY
/**
 * @brief Множество для отслеживания выделенных узлов
 *
 * @details
 * Хранит указатели на все созданные через MemoryUtils узлы.
 * Используется только при определении макроса DEBUG_MEMORY.
 * В релизной сборке этот код исключается из компиляции.
 */
static std::unordered_set<TreeNode*> allocatedNodes;
#endif

/**
 * @brief Создание узла с отслеживанием памяти
 *
 * @details
 * В режиме DEBUG_MEMORY:
 * 1. Запоминает указатель на созданный узел
 * 2. Выводит отладочную информацию
 * 3. Считает общее количество выделенных узлов
 *
 * В релизном режиме работает как обычный оператор new.
 */
TreeNode* MemoryUtils::createTreeNode(int key) {
    TreeNode* node = new TreeNode(key);

#ifdef DEBUG_MEMORY
    // Отладочный код: отслеживание выделения памяти
    allocatedNodes.insert(node);
    std::cout << "[MEMORY] Создан узел " << node << " с ключом " << key << std::endl;
    std::cout << "[MEMORY] Всего выделено узлов: " << allocatedNodes.size() << std::endl;
#endif

    return node;
}

/**
 * @brief Удаление узла с отслеживанием памяти
 *
 * @details
 * В режиме DEBUG_MEMORY:
 * 1. Проверяет, был ли узел создан через MemoryUtils
 * 2. Удаляет узел из отслеживания
 * 3. Выводит отладочную информацию
 * 4. Предупреждает о попытке удалить неотслеживаемый узел
 *
 * В релизном режиме работает как обычный оператор delete.
 */
void MemoryUtils::deleteTreeNode(TreeNode* node) {
    if (node == nullptr) {
        return;
    }

#ifdef DEBUG_MEMORY
    // Отладочный код: проверка корректности освобождения памяти
    if (allocatedNodes.find(node) != allocatedNodes.end()) {
        allocatedNodes.erase(node);
        std::cout << "[MEMORY] Удален узел " << node << " с ключом " << node->key << std::endl;
        std::cout << "[MEMORY] Осталось узлов: " << allocatedNodes.size() << std::endl;
    }
    else {
        std::cout << "[MEMORY] ПРЕДУПРЕЖДЕНИЕ: Попытка удалить невыделенный узел " << node << std::endl;
    }
#endif

    delete node;
}

/**
 * @brief Проверка утечек памяти
 *
 * @details
 * В режиме DEBUG_MEMORY:
 * 1. Проверяет, остались ли неосвобожденные узлы
 * 2. Выводит подробную информацию об утечках
 * 3. Возвращает количество утечек
 *
 * В релизном режиме всегда возвращает 0.
 *
 * @note Вызывайте эту функцию перед завершением программы для проверки.
 */
int MemoryUtils::checkMemoryLeaks() {
#ifdef DEBUG_MEMORY
    int leaks = allocatedNodes.size();
    if (leaks > 0) {
        std::cout << "[MEMORY] ОБНАРУЖЕНЫ УТЕЧКИ ПАМЯТИ!" << std::endl;
        std::cout << "[MEMORY] Не освобождено " << leaks << " узлов:" << std::endl;

        for (TreeNode* node : allocatedNodes) {
            std::cout << "[MEMORY]   Узел " << node << " с ключом " << node->key << std::endl;
        }
    }
    else {
        std::cout << "[MEMORY] Утечек памяти не обнаружено" << std::endl;
    }

    return leaks;
#else
    // В релизной сборке проверка утечек отключена
    return 0;
#endif
}

/**
 * @brief Аварийная очистка всей памяти
 *
 * @details
 * В режиме DEBUG_MEMORY:
 * 1. Принудительно удаляет все отслеживаемые узлы
 * 2. Очищает множество allocatedNodes
 * 3. Выводит отчет об очистке
 *
 * Используется для аварийного завершения программы или в тестах.
 * В релизном режиме не выполняет никаких действий.
 *
 * @warning Эта функция должна использоваться только в крайних случаях,
 * так как нарушает обычный жизненный цикл объектов.
 */
void MemoryUtils::emergencyCleanup() {
#ifdef DEBUG_MEMORY
    std::cout << "[MEMORY] АВАРИЙНАЯ ОЧИСТКА ПАМЯТИ..." << std::endl;

    int cleaned = 0;
    for (TreeNode* node : allocatedNodes) {
        std::cout << "[MEMORY] Принудительное удаление узла " << node << " с ключом " << node->key << std::endl;
        delete node;
        cleaned++;
    }

    allocatedNodes.clear();
    std::cout << "[MEMORY] Освобождено " << cleaned << " узлов" << std::endl;
#endif
}