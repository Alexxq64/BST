#include "data_generator.h"
#include <algorithm>
#include <random>
#include <unordered_set>

/**
 * @file data_generator.cpp
 * @brief Реализация методов генерации данных для деревьев поиска
 */

 /**
  * @brief Генерация массива уникальных случайных чисел
  *
  * Использует современный генератор случайных чисел C++ std::mt19937
  * и равномерное распределение. Для обеспечения уникальности используется
  * хэш-таблица (unordered_set).
  */
std::vector<int> DataGenerator::generateUniqueNumbers(int count, int minVal, int maxVal) {
    // Проверка корректности параметров
    if (count <= 0) {
        return std::vector<int>();
    }

    // Ограничение количества, если запрошено больше чем доступно уникальных чисел
    int availableNumbers = maxVal - minVal + 1;
    if (count > availableNumbers) {
        count = availableNumbers;
    }

    // Генератор случайных чисел
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(minVal, maxVal);

    // Используем unordered_set для гарантии уникальности
    std::unordered_set<int> uniqueNumbers;

    // Генерируем числа пока не наберем нужное количество уникальных
    while (uniqueNumbers.size() < static_cast<size_t>(count)) {
        int num = dist(gen);
        uniqueNumbers.insert(num);
    }

    // Преобразуем set в vector для возврата
    std::vector<int> result(uniqueNumbers.begin(), uniqueNumbers.end());

    return result;
}

/**
 * @brief Проверка наличия числа в массиве
 *
 * Использует стандартный алгоритм std::find для поиска.
 * Временная сложность: O(n) в худшем случае.
 */
bool DataGenerator::contains(const std::vector<int>& numbers, int value) {
    return std::find(numbers.begin(), numbers.end(), value) != numbers.end();
}