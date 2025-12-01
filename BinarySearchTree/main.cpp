#include <iostream>
#include "lab1.h"
#include "lab2.h"
#include "lab3.h"
#include "tests.h"



int main() {
    std::locale::global(std::locale(""));
    std::cout.imbue(std::locale());

    while (true) {
        std::cout << "==================================================\n";
        std::cout << "                 М Е Н Ю   \n";
        std::cout << "==================================================\n";
        std::cout << "1. Лабораторная 1 (ИСДП и СДП)\n";
        std::cout << "2. Лабораторная 2 (АВЛ и ИСДП)\n";
        std::cout << "3. Лабораторная 3 (АВЛ и ДБД)\n";
        std::cout << "4. Тесты\n";
        std::cout << "0. Выход\n";
        std::cout << "--------------------------------------------------\n";
        std::cout << "Ваш выбор: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1:
            runLab1();
            break;

        case 2:
            runLab2();
            break;

        case 3:
            runLab3();
            break;

        case 4:
            runTests();
            break;

        case 0:
            return 0;

        default:
            std::cout << "Некорректный выбор!\n";
        }

    }

    return 0;
}
