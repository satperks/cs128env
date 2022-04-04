#include <iostream>
#include <vector>

#include "solution.hpp"

int main() {
  const char* test = "c-style string";
  int index = 0;
  std::vector<char> to_return;
  while (test[index] != '\0') {
    to_return.push_back(test[index]);
    index++;
  }
  std::cout << test << std::endl;
  std::cout << to_return.size() << std::endl;
  return 0;
}