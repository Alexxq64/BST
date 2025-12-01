#include "lab3.h"
#include "db_node.h"
#include "data_generator.h"
#include "tree_builders.h"
#include "tree_properties.h"
#include "output_utils.h"
#include "theory_calculations.h"
#include "testing.h"

#include <iostream>
#include <vector>
#include <algorithm>

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
        for (int i = traversal.size() - 5; i < traversal.size(); i++) std::cout << traversal[i] << " ";
    }
    std::cout << std::endl;
}

static void compareDBDCharacteristics(const std::vector<int>& sizes) {
    std::cout << "=== ВЫВОД ОБХОДОВ ДЕРЕВЬЕВ ===" << std::endl;

    for (int size : sizes) {
        std::vector<int> data = DataGenerator::generateUniqueNumbers(size, 1, size * 10);

        TreeNode* avlTree = TreeBuilders::buildAVLTree(data);
        DBNode* dbTree = TreeBuilders::buildDBTree(data, 2); // t=2, минимальная степень

        std::cout << "АВЛ " << size << ": ";
        printCompactTraversal(TreeProperties::inOrderTraversal(avlTree));

        std::vector<int> dbTraversal;
        TreeBuilders::inOrderTraversalDB(dbTree, dbTraversal);
        std::cout << "ДБД " << size << ": ";
        printCompactTraversal(dbTraversal);

        TreeBuilders::deleteTree(avlTree);
        TreeBuilders::deleteDBTree(dbTree);
    }

    std::cout << std::endl << "=== СРАВНЕНИЕ ХАРАКТЕРИСТИК ===" << std::endl;
    OutputUtils::printDBTableHeader();

    for (int size : sizes) {
        std::vector<int> data = DataGenerator::generateUniqueNumbers(size, 1, size * 10);

        TreeNode* avlTree = TreeBuilders::buildAVLTree(data);
        DBNode* dbTree = TreeBuilders::buildDBTree(data, 2);

        int avlCheckSum = TreeProperties::calculateCheckSum(avlTree);
        int avlHeight = TreeProperties::calculateHeight(avlTree);
        double avlAvg = TheoryCalculations::theoreticalAverageHeightBalanced(size);

        int dbCheckSum = TreeProperties::calculateCheckSumDB(dbTree);
        int dbLevels = TreeProperties::calculateLevelsDB(dbTree);
        double dbHeightTheo = TheoryCalculations::theoreticalDBHeight(size, 2); // передаем t
        double dbAvgTheo = TheoryCalculations::theoreticalAverageHeightBalanced(size);

        // Выводим минимально: size и уровни (остальное можно расширить позже)
        OutputUtils::printDBTableRow(size,
            avlCheckSum, avlHeight, avlAvg,
            dbCheckSum, dbLevels, dbHeightTheo, dbAvgTheo);
        TreeBuilders::deleteTree(avlTree);
        TreeBuilders::deleteDBTree(dbTree);
    }

    std::cout << std::string(100, '=') << std::endl;
}

void runLab3() {
    std::cout << "==================================================" << std::endl;
    std::cout << "ЛАБОРАТОРНАЯ РАБОТА 3" << std::endl;
    std::cout << "Тема: Двоичное Б-дерево поиска (ДБД)" << std::endl;
    std::cout << "==================================================" << std::endl;
    std::cout << std::endl;

    std::cout << "Построение и сравнение АВЛ и ДБД для размеров: 100, 200, 300, 400, 500" << std::endl;
    std::cout << std::endl;

    std::vector<int> sizes = { 100, 200, 300, 400, 500 };
    compareDBDCharacteristics(sizes);
}
