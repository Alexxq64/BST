/**
 * @file memory_utils.cpp
 * @brief Реализация утилит для работы с памятью
 */

#include "memory_utils.h"
#include <iostream>
#include <unordered_set>

 // Глобальные переменные для отслеживания памяти (только для отладки)
#ifdef DEBUG_MEMORY
static std::unordered_set<TreeNode*> allocatedNodes;
#endif

TreeNode* MemoryUtils::createTreeNode(int key) {
    TreeNode* node = new TreeNode(key);

#ifdef DEBUG_MEMORY
    allocatedNodes.insert(node);
    std::cout << "[MEMORY] Создан узел " << node << " с ключом " << key << std::endl;
    std::cout << "[MEMORY] Всего выделено узлов: " << allocatedNodes.size() << std::endl;
#endif

    return node;
}

void MemoryUtils::deleteTreeNode(TreeNode* node) {
    if (node == nullptr) {
        return;
    }

#ifdef DEBUG_MEMORY
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
    return 0;
#endif
}

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