#include "calculation.hpp"

int calculation(double argument_one, double argument_two, char sign, bool correct) {
    if (sign == '+' && correct) {
        std::cout << "Answer: "<< argument_one + argument_two << std::endl;
        return 0;
    } else if (sign == '-' && correct) {
        std::cout << "Answer: "<< argument_one - argument_two << std::endl;
        return 0;
    } else if (sign == '*' && correct) {
        std::cout << "Answer: "<< argument_one * argument_two << std::endl;
        return 0;
    } else if (sign == '/' && correct) {
        std::cout << "Answer: "<< argument_one / argument_two << std::endl;
        return 0;
    } else if (!correct && (sign == '+' || sign == '-' || sign == '*' || sign == '/')) {
        return -1;
    } else if (correct) {
        return -2;
    } else {
        return -3;
    }
}