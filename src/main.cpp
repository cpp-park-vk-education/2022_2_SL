//Простой калькулятор

#include "calculation.hpp"

int main() {
  double argument_one = 0;
  double argument_two = 0;
  char sign = 0;
  std::cout << "Enter the expression: ";
  std::cin >> argument_one >> sign >> argument_two;
  std::cout << std::endl;
  try {
    throw calculation(argument_one, argument_two, sign, std::cin.good());
  } catch (int e) {
    if (e == -1) {
      std::cerr << "Incorrect input argument" << std::endl
                << "Please try again" << std::endl;
    }
    if (e == -2) {
      std::cerr << "Incorrect input sign" << std::endl
                << "Please try again" << std::endl;
    }
    if (e == -3) {
      std::cerr << "Incorrect input argument and sign" << std::endl
                << "Please try again" << std::endl;
    }
  }
  return 0;
}
