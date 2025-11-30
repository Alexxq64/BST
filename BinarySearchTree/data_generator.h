#ifndef DATA_GENERATOR_H
#define DATA_GENERATOR_H

#include <vector>

/**
 * @file data_generator.h
 * @brief Генератор данных для построения деревьев поиска
 *
 * Этот класс предоставляет методы для генерации массивов уникальных случайных чисел,
 * которые используются для построения ИСДП и СДП. Гарантируется уникальность всех
 * элементов в генерируемых массивах.
 */

class DataGenerator {
public:
    /**
     * @brief Генерация массива уникальных случайных чисел
     * @param count Количество чисел для генерации
     * @param minVal Минимальное значение чисел (по умолчанию 1)
     * @param maxVal Максимальное значение чисел (по умолчанию 1000)
     * @return Вектор уникальных случайных чисел
     *
     * @note Если запрошено больше чисел, чем доступно в диапазоне [minVal, maxVal],
     *       будет сгенерировано максимально возможное количество уникальных чисел.
     */
    static std::vector<int> generateUniqueNumbers(int count, int minVal = 1, int maxVal = 1000);

    /**
     * @brief Проверка наличия числа в массиве
     * @param numbers Вектор чисел для проверки
     * @param value Значение для поиска
     * @return true если значение найдено, false в противном случае
     *
     * Вспомогательная функция для проверки уникальности чисел при генерации.
     */
    static bool contains(const std::vector<int>& numbers, int value);
};

#endif // DATA_GENERATOR_H
