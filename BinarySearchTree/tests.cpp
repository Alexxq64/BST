/**
 * @file tests.cpp
 * @brief Тесты для демонстрации деревьев
 */

#include "tests.h"
#include "testing.h"
#include <iostream>

 /**
  * @brief Запуск всех демонстрационных тестов
  */
void runTests() {
    std::cout << "=== ТЕСТЫ (ДЕМОНСТРАЦИЯ ПОСТРОЕНИЯ ДЕРЕВЬЕВ) ===" << std::endl;

    Testing::demonstrateBalancedTree();
    Testing::demonstrateRandomTree();
    Testing::demonstrateAVLTree();
    Testing::demonstrateDBTree();

    std::cout << "=== ТЕСТЫ ЗАВЕРШЕНЫ ===" << std::endl << std::endl;
}