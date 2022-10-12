#include "calculation.hpp"

int calculation(double argument_one, double argument_two, char sign) {
    if (sign == '+') {
        std::cout << "Answer: "<< argument_one + argument_two << std::endl;
        return 0;
    }
    if (sign == '-') {
        std::cout << "Answer: "<< argument_one - argument_two << std::endl;
        return 0;
    }
    if (sign == '*') {
        std::cout << "Answer: "<< argument_one * argument_two << std::endl;
        return 0;
    }
    if (sign == '/') {
        std::cout << "Answer: "<< argument_one / argument_two << std::endl;
        return 0;
    }
    return -1;
}