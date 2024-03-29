#include "help.hpp"

void Print(std::string output) { std::cout << output << std::flush; }

std::string GetPlayerInput(std::string prompt) {
  std::string input;
  Print(prompt);
  std::cin >> input;
  return input;
}

void ClearCin() {
  std::cin.clear();
  fflush(stdin);
}