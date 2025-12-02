/**
 * @file lab1.cpp
 * @brief Реализация лабораторной работы №1: сравнение ИСДП и СДП
 */

#include "lab1.h"
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
 * @brief Сравнение характеристик ИСДП и СДП
 * @param sizes Вектор размеров деревьев для анализа
 */
static void compareTreeCharacteristics(const std::vector<int>& sizes) {
    std::cout << "=== ВЫВОД ОБХОДОВ ДЕРЕВЬЕВ ===" << std::endl;

    for (int size : sizes) {
        std::vector<int> data = DataGenerator::generateUniqueNumbers(size, 1, size * 10);
        std::vector<int> sortedData = data;
        std::sort(sortedData.begin(), sortedData.end());

        TreeNode* ibTree = TreeBuilders::buildPerfectlyBalancedTree(sortedData);
        TreeNode* spTree = TreeBuilders::buildRandomSearchTree(data);

        std::cout << "ИСДП " << size << ": ";
        printCompactTraversal(TreeProperties::inOrderTraversal(ibTree));

        std::cout << "СДП " << size << ": ";
        printCompactTraversal(TreeProperties::inOrderTraversal(spTree));
        std::cout << std::endl;

        TreeBuilders::deleteTree(ibTree);
        TreeBuilders::deleteTree(spTree);
    }

    std::cout << "=== СРАВНЕНИЕ ХАРАКТЕРИСТИК ===" << std::endl << std::endl;
    OutputUtils::printTableHeader("СДП", "ИСДП");

    for (int size : sizes) {
        std::vector<int> data = DataGenerator::generateUniqueNumbers(size, 1, size * 10);
        std::vector<int> sortedData = data;
        std::sort(sortedData.begin(), sortedData.end());

        TreeNode* ibTree = TreeBuilders::buildPerfectlyBalancedTree(sortedData);
        TreeNode* spTree = TreeBuilders::buildRandomSearchTree(data);

        int ibCheckSum = TreeProperties::calculateCheckSum(ibTree);
        int ibHeight = TreeProperties::calculateHeight(ibTree);
        double ibTheoreticalAvgHeight = TheoryCalculations::theoreticalAverageHeightBalanced(size);

        int spCheckSum = TreeProperties::calculateCheckSum(spTree);
        int spHeight = TreeProperties::calculateHeight(spTree);
        double spTheoreticalAvgHeight = TheoryCalculations::theoreticalAverageHeightRandomBST(size);

        OutputUtils::printTableRow(size,
            spCheckSum, spHeight, spTheoreticalAvgHeight,
            ibCheckSum, ibHeight, ibTheoreticalAvgHeight);

        TreeBuilders::deleteTree(ibTree);
        TreeBuilders::deleteTree(spTree);
    }

    std::cout << std::string(100, '=') << std::endl;
}

/**
 * @brief Основная функция лабораторной работы 1
 */
void runLab1() {
    std::cout << "==================================================" << std::endl;
    std::cout << "ЛАБОРАТОРНАЯ РАБОТА 1" << std::endl;
    std::cout << "Тема: Идеально сбалансированное дерево поиска (ИСДП)" << std::endl;
    std::cout << "       и случайное дерево поиска (СДП)" << std::endl;
    std::cout << "==================================================" << std::endl;
    std::cout << std::endl;

    std::cout << "Построение и сравнение ИСДП и СДП для размеров: 100, 200, 300, 400, 500" << std::endl;
    std::cout << std::endl;

    std::vector<int> sizes = { 100, 200, 300, 400, 500 };
    compareTreeCharacteristics(sizes);
}