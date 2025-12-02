/**
 * @file lab2.cpp
 * @brief Реализация лабораторной работы №2: сравнение АВЛ-деревьев и ИСДП
 */

#include "lab2.h"
#include "data_generator.h"
#include "tree_builders.h"
#include "tree_properties.h"
#include "output_utils.h"
#include "theory_calculations.h"
#include "testing.h"

#include <iostream>
#include <vector>
#include <algorithm>

 /**
  * @brief Компактный вывод обхода дерева
  * @param traversal Вектор ключей для вывода
  */
static void printCompactTraversal(const std::vector<int>& traversal) {
    if (traversal.size() <= 15) {
        for (int key : traversal) std::cout << key << " ";
    }
    else {
        for (int i = 0; i < 5; i++) std::cout << traversal[i] << " ";
        std::cout << "... ";

        int step = traversal.size() / 6;
        for (int i = 1; i <= 5; i++) {
            std::cout << traversal[i * step] << " ";
            if (i < 5) std::cout << "... ";
        }
        std::cout << "... ";

        for (int i = traversal.size() - 5; i < traversal.size(); i++) {
            std::cout << traversal[i] << " ";
        }
    }
    std::cout << std::endl;
}

/**
 * @brief Сравнение характеристик АВЛ-дерева и ИСДП для разных размеров
 * @param sizes Вектор размеров деревьев для анализа
 * @details
 * Генерирует данные, строит АВЛ и идеально сбалансированное дерево,
 * вычисляет характеристики и выводит результаты в таблице.
 */
static void compareTreeCharacteristics(const std::vector<int>& sizes) {
    std::cout << "=== ВЫВОД ОБХОДОВ ДЕРЕВЬЕВ ===" << std::endl;

    for (int size : sizes) {
        std::vector<int> data = DataGenerator::generateUniqueNumbers(size, 1, size * 10);
        std::vector<int> sortedData = data;
        std::sort(sortedData.begin(), sortedData.end());

        TreeNode* avlTree = TreeBuilders::buildAVLTree(data);
        TreeNode* ibTree = TreeBuilders::buildPerfectlyBalancedTree(sortedData);

        std::cout << "АВЛ " << size << ": ";
        printCompactTraversal(TreeProperties::inOrderTraversal(avlTree));

        std::cout << "ИСДП " << size << ": ";
        printCompactTraversal(TreeProperties::inOrderTraversal(ibTree));

        std::cout << std::endl;

        TreeBuilders::deleteTree(avlTree);
        TreeBuilders::deleteTree(ibTree);
    }

    std::cout << "=== СРАВНЕНИЕ ХАРАКТЕРИСТИК ===" << std::endl << std::endl;
    OutputUtils::printTableHeader("АВЛ", "ИСДП");

    for (int size : sizes) {
        std::vector<int> data = DataGenerator::generateUniqueNumbers(size, 1, size * 10);
        std::vector<int> sortedData = data;
        std::sort(sortedData.begin(), sortedData.end());

        TreeNode* avlTree = TreeBuilders::buildAVLTree(data);
        TreeNode* ibTree = TreeBuilders::buildPerfectlyBalancedTree(sortedData);

        int avlCheckSum = TreeProperties::calculateCheckSum(avlTree);
        int avlHeight = TreeProperties::calculateHeight(avlTree);
        double avlAvg = TheoryCalculations::theoreticalAverageHeightBalanced(size);

        int ibCheckSum = TreeProperties::calculateCheckSum(ibTree);
        int ibHeight = TreeProperties::calculateHeight(ibTree);
        double ibAvg = TheoryCalculations::theoreticalAverageHeightBalanced(size);

        OutputUtils::printTableRow(size,
            avlCheckSum, avlHeight, avlAvg,
            ibCheckSum, ibHeight, ibAvg);

        TreeBuilders::deleteTree(avlTree);
        TreeBuilders::deleteTree(ibTree);
    }

    std::cout << std::string(100, '=') << std::endl;
}

/**
 * @brief Основная функция лабораторной работы 2
 * @details
 * Запускает сравнение АВЛ-деревьев и идеально сбалансированных деревьев
 * для размеров 100, 200, 300, 400, 500.
 */
void runLab2() {
    std::cout << "==================================================" << std::endl;
    std::cout << "ЛАБОРАТОРНАЯ РАБОТА 2" << std::endl;
    std::cout << "Тема: Сбалансированные по высоте деревья поиска (АВЛ)" << std::endl;
    std::cout << "==================================================" << std::endl;
    std::cout << std::endl;

    std::cout << "Построение и сравнение АВЛ и ИСДП для размеров: 100, 200, 300, 400, 500" << std::endl;
    std::cout << std::endl;

    std::vector<int> sizes = { 100, 200, 300, 400, 500 };
    compareTreeCharacteristics(sizes);
}