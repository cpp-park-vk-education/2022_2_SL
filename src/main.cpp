//Простой калькулятор

#include "calculation.hpp"

int main() {
    double argument_one;
    double argument_two;
    char sign;
    std::cout << "Enter the expression: ";
    std::cin >> argument_one >> sign >> argument_two;
    std::cout << std::endl;
    try {
        throw calculation(argument_one, argument_two, sign);
    }
    catch(int e) {
        if (e == -1) {
            std::cerr << "Incorrect input" << std::endl << "Please try again" << std::endl;
        }
    }
    return 0;
}