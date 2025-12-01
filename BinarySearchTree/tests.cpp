#include "tests.h"
#include "testing.h"
#include <iostream>

void runTests() {
    std::cout << "=== ÒÅÑÒÛ (ÄÅÌÎÍÑÒÐÀÖÈß ÏÎÑÒÐÎÅÍÈß ÄÅÐÅÂÜÅÂ) ===" << std::endl;

    Testing::demonstrateBalancedTree();
    Testing::demonstrateRandomTree();

    std::cout << "=== ÒÅÑÒÛ ÇÀÂÅÐØÅÍÛ ===" << std::endl << std::endl;
}
