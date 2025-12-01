#include "output_utils.h"
#include "tree_properties.h"
#include "theory_calculations.h"
#include <iostream>
#include <iomanip>

/**
 * @file output_utils.cpp
 * @brief Реализация утилит для вывода данных
 */

 /**
  * @brief Вывод дерева в виде скобочной записи
  *
  * Скобочная запись удобна для визуализации структуры дерева.
  * Формат: (корень левое-поддерево правое-поддерево)
  * Пустые поддеревья не выводятся.
  */
void OutputUtils::printTreeBracket(TreeNode* root) {
    if (root == nullptr) {
        std::cout << "()";
        return;
    }

    std::cout << "(";
    printTreeBracketRecursive(root);
    std::cout << ")";
    std::cout << std::endl;
}

/**
 * @brief Рекурсивная функция для вывода скобочной записи
 *
 * Рекурсивно обходит дерево и выводит его структуру.
 * Для каждого узла выводит его ключ и рекурсивно левое и правое поддеревья.
 */
void OutputUtils::printTreeBracketRecursive(TreeNode* node) {
    if (node == nullptr) {
        return;
    }

    std::cout << node->key;

    // Выводим левое поддерево, если оно не пустое
    if (node->left != nullptr || node->right != nullptr) {
        std::cout << " (";
        if (node->left != nullptr) {
            printTreeBracketRecursive(node->left);
        }
        std::cout << ")";
    }

    // Выводим правое поддерево, если оно не пустое
    if (node->right != nullptr) {
        std::cout << " (";
        printTreeBracketRecursive(node->right);
        std::cout << ")";
    }
}

/**
 * @brief Вывод in-order обхода дерева
 *
 * Выводит последовательность ключей, полученную при in-order обходе.
 * Для BST это должна быть отсортированная последовательность.
 */
void OutputUtils::printInOrder(TreeNode* root, const std::string& title) {
    std::vector<int> traversal = TreeProperties::inOrderTraversal(root);

    std::cout << title << std::endl;
    std::cout << "Количество элементов: " << traversal.size() << std::endl;
    std::cout << "Элементы: ";

    // Выводим первые 20 элементов для компактности
    int count = 0;
    for (int key : traversal) {
        std::cout << key << " ";
        count++;
        if (count >= 20 && traversal.size() > 20) {
            std::cout << "... (всего " << traversal.size() << " элементов)";
            break;
        }
    }
    std::cout << std::endl << std::endl;
}

/**
 * @brief Вывод in-order обхода дерева с репрезентативной выборкой
 *
 * Для больших деревьев выводит:
 * - Первые 5 элементов
 * - 5 элементов из середины, разделенных через ...
 * - Последние 5 элементов
 */
void OutputUtils::printInOrderSampled(TreeNode* root, const std::string& title) {
    std::vector<int> traversal = TreeProperties::inOrderTraversal(root);

    std::cout << title << std::endl;
    std::cout << "Количество элементов: " << traversal.size() << std::endl;
    std::cout << "Элементы: ";

    if (traversal.size() <= 15) {
        // Если элементов мало - выводим все
        for (int key : traversal) {
            std::cout << key << " ";
        }
    }
    else {
        // Первые 5 элементов
        for (int i = 0; i < 5; i++) {
            std::cout << traversal[i] << " ";
        }
        std::cout << "... ";

        // 5 элементов из середины, равномерно распределенных
        int step = traversal.size() / 6; // Делим на 6 частей, берем точки между ними
        for (int i = 1; i <= 5; i++) {
            int index = i * step;
            std::cout << traversal[index] << " ";
            if (i < 5) std::cout << "... ";
        }
        std::cout << "... ";

        // Последние 5 элементов
        for (int i = traversal.size() - 5; i < traversal.size(); i++) {
            std::cout << traversal[i] << " ";
        }
    }
    std::cout << std::endl << std::endl;
}

/**
 * @brief Вывод характеристик дерева
 *
 * Выводит все основные характеристики дерева в удобном формате.
 * Используется для отладки и демонстрации работы программы.
 */
void OutputUtils::printTreeProperties(TreeNode* root, const std::string& treeName) {
    std::cout << "=== " << treeName << " ===" << std::endl;

    if (root == nullptr) {
        std::cout << "Дерево пустое" << std::endl << std::endl;
        return;
    }

    int size = TreeProperties::calculateSize(root);
    int height = TreeProperties::calculateHeight(root);
    int checkSum = TreeProperties::calculateCheckSum(root);
    double avgHeight = TreeProperties::calculateAverageHeight(root);

    std::cout << "Размер дерева: " << size << std::endl;
    std::cout << "Высота дерева: " << height << std::endl;
    std::cout << "Контрольная сумма: " << checkSum << std::endl;
    std::cout << "Средняя высота: " << std::fixed << std::setprecision(2) << avgHeight << std::endl;

    // ТОЛЬКО релевантные теоретические оценки
    if (treeName.find("ИСДП") != std::string::npos || treeName.find("Сбалансирован") != std::string::npos) {
        // Для ИСДП выводим только теоретические оценки ИСДП
        double theoreticalHeightIB = TheoryCalculations::theoreticalHeightBalanced(size);
        double theoreticalAvgHeightIB = TheoryCalculations::theoreticalAverageHeightBalanced(size);
        std::cout << "Теор. высота ИСДП: " << std::fixed << std::setprecision(2) << theoreticalHeightIB << std::endl;
        std::cout << "Теор. сред. высота ИСДП: " << std::fixed << std::setprecision(2) << theoreticalAvgHeightIB << std::endl;
    }
    else if (treeName.find("СДП") != std::string::npos || treeName.find("Случайн") != std::string::npos) {
        // Для СДП выводим только теоретические оценки СДП
        double theoreticalHeightSP = TheoryCalculations::theoreticalHeightRandomBST(size);
        double theoreticalAvgHeightSP = TheoryCalculations::theoreticalAverageHeightRandomBST(size);
        std::cout << "Теор. высота СДП: " << std::fixed << std::setprecision(2) << theoreticalHeightSP << std::endl;
        std::cout << "Теор. сред. высота СДП: " << std::fixed << std::setprecision(2) << theoreticalAvgHeightSP << std::endl;
    }
    else {
        // Для неизвестного типа - выводим все
        double theoreticalHeightIB = TheoryCalculations::theoreticalHeightBalanced(size);
        double theoreticalAvgHeightIB = TheoryCalculations::theoreticalAverageHeightBalanced(size);
        double theoreticalHeightSP = TheoryCalculations::theoreticalHeightRandomBST(size);
        double theoreticalAvgHeightSP = TheoryCalculations::theoreticalAverageHeightRandomBST(size);
        std::cout << "Теор. высота ИСДП: " << std::fixed << std::setprecision(2) << theoreticalHeightIB << std::endl;
        std::cout << "Теор. сред. высота ИСДП: " << std::fixed << std::setprecision(2) << theoreticalAvgHeightIB << std::endl;
        std::cout << "Теор. высота СДП: " << std::fixed << std::setprecision(2) << theoreticalHeightSP << std::endl;
        std::cout << "Теор. сред. высота СДП: " << std::fixed << std::setprecision(2) << theoreticalAvgHeightSP << std::endl;
    }

    std::cout << std::endl;
}

/**
 * @brief Вывод заголовка таблицы результатов
 *
 * Форматирует и выводит заголовок для таблицы 1 из задания лабораторной работы.
 * Столбцы выравниваются для удобства чтения.
 */
void OutputUtils::printTableHeader(
    const std::string& leftGroup,
    const std::string& rightGroup)
{

    // ==== ГРУППЫ ====
    std::cout << std::setw(9) << "Размер" << std::setw(6) << " | ";

    std::cout << std::setw(22) << leftGroup
        << std::setw(21) << " | "
        << std::setw(22) << rightGroup
        << std::setw(21) << std::endl;

    // ==== Подзаголовки 1 ====
    std::cout << std::setw(12) << " " << " | ";

    std::cout << std::setw(10) << "Контр."
        << std::setw(12) << "Высота"
        << std::setw(18) << "Теор." << " | ";

    std::cout << std::setw(10) << "Контр."
        << std::setw(12) << "Высота"
        << std::setw(18) << "Теор." << std::endl;

    // ==== Подзаголовки 2 ====
    std::cout << std::setw(12) << " " << " | ";

    std::cout << std::setw(10) << "сумма"
        << std::setw(12) << "факт."
        << std::setw(18) << "сред. высота" << " | ";

    std::cout << std::setw(10) << "сумма"
        << std::setw(12) << "факт."
        << std::setw(18) << "сред. высота" << std::endl;

    std::cout << std::string(100, '-') << std::endl;
}


/**
 * @brief Вывод строки таблицы для одного размера дерева
 *
 * Форматирует и выводит одну строку таблицы с результатами для конкретного размера дерева.
 * Все числовые значения выравниваются для удобства сравнения.
 */
void OutputUtils::printTableRow(int size,
    int checkSumSP, double heightSP, double theoreticalAvgHeightSP,
    int checkSumIB, double heightIB, double theoreticalAvgHeightIB) {
    std::cout << std::setw(12) << size << " | ";

    // Данные для СДП
    std::cout << std::setw(10) << checkSumSP << " "
        << std::setw(12) << std::fixed << std::setprecision(1) << heightSP << " "
        << std::setw(16) << std::fixed << std::setprecision(2) << theoreticalAvgHeightSP << " | ";

    // Данные для ИСДП
    std::cout << std::setw(10) << checkSumIB << " "
        << std::setw(12) << std::fixed << std::setprecision(1) << heightIB << " "
        << std::setw(16) << std::fixed << std::setprecision(2) << theoreticalAvgHeightIB << std::endl;
}

/**
 * @brief Вывод теоретических оценок
 *
 * Выводит таблицу с теоретическими оценками высоты и средней высоты
 * для ИСДП и СДП различных размеров.
 */
void OutputUtils::printTheoreticalEstimates(const std::vector<int>& sizes) {
    std::cout << std::endl << std::string(80, '=') << std::endl;
    std::cout << "ТЕОРЕТИЧЕСКИЕ ОЦЕНКИ" << std::endl;
    std::cout << std::string(80, '=') << std::endl;

    std::cout << std::setw(8) << "Размер" << " | ";
    std::cout << std::setw(12) << "ИСДП высота" << " | ";
    std::cout << std::setw(15) << "ИСДП ср.высота" << " | ";
    std::cout << std::setw(12) << "СДП высота" << " | ";
    std::cout << std::setw(15) << "СДП ср.высота" << std::endl;
    std::cout << std::string(80, '-') << std::endl;

    for (int size : sizes) {
        double thHeightIB = TheoryCalculations::theoreticalHeightBalanced(size);
        double thAvgHeightIB = TheoryCalculations::theoreticalAverageHeightBalanced(size);
        double thHeightSP = TheoryCalculations::theoreticalHeightRandomBST(size);
        double thAvgHeightSP = TheoryCalculations::theoreticalAverageHeightRandomBST(size);

        std::cout << std::setw(8) << size << " | ";
        std::cout << std::setw(12) << std::fixed << std::setprecision(2) << thHeightIB << " | ";
        std::cout << std::setw(15) << std::fixed << std::setprecision(2) << thAvgHeightIB << " | ";
        std::cout << std::setw(12) << std::fixed << std::setprecision(2) << thHeightSP << " | ";
        std::cout << std::setw(15) << std::fixed << std::setprecision(2) << thAvgHeightSP << std::endl;
    }

    std::cout << std::string(80, '=') << std::endl << std::endl;
}




void OutputUtils::printDBTableHeader() {
    std::cout
        << std::setw(6) << ""
        << std::setw(30) << "АВЛ"
        << std::setw(30) << "ДБД"
        << std::endl;

    std::cout << std::right
        << std::setw(6) << ""
        << std::setw(12) << "Контр."
        << std::setw(8) << "Факт."
        << std::setw(12) << "Теор. ср."
        << std::setw(15) << "Контр."
        << std::setw(10) << ""
        << std::setw(9) << "Теор."
        << std::setw(12) << "Теор. ср"
        << std::endl;

    std::cout << std::right
        << std::setw(6) << "Размер"
        << std::setw(12) << "сумма."
        << std::setw(8) << "высота"
        << std::setw(12) << "высота"
        << std::setw(15) << "сумма."
        << std::setw(10) << "Уровни"
        << std::setw(9) << "высота"
        << std::setw(12) << "высота"
        << std::endl;

    std::cout << std::string(108, '-') << std::endl;
}

void OutputUtils::printDBTableRow(int size,
    int avlCheckSum, int avlHeight, double avlAvg,
    int dbCheckSum, int dbLevels, double dbHeightTheo, double dbAvgTheo) {
    std::cout << std::right
        << std::setw(6) << size
        << std::setw(12) << avlCheckSum
        << std::setw(8) << avlHeight
        << std::setw(12) << std::fixed << std::setprecision(2) << avlAvg
        << std::setw(15) << dbCheckSum
        << std::setw(10) << dbLevels
        << std::setw(9) << dbHeightTheo
        << std::setw(12) << dbAvgTheo
        << std::endl;
}

