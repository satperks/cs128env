#include <iostream>
#include <string>
#include <vector>

#include "illini_book.hpp"

int main() {
  IlliniBook ib("./example/persons.csv", "./example/relations.csv");
  std::cout << "set IlliniBook successfully" << std::endl;
  std::cout << ib.AreRelated(1, 2) << std::endl;         // true
  std::cout << ib.AreRelated(3, 2) << std::endl;         // true
  std::cout << ib.AreRelated(1, 9) << std::endl;         // false
  std::cout << ib.AreRelated(1, 2, "128") << std::endl;  // true
  std::cout << ib.AreRelated(1, 2, "124") << std::endl;  // false
  std::cout << ib.AreRelated(1, 6, "128") << std::endl;  // true
  std::cout << ib.AreRelated(1, 6, "124") << std::endl;  // true
  std::cout << ib.GetRelated(1, 2) << std::endl;         // 1
  std::cout << ib.GetRelated(3, 2) << std::endl;         // 2
  std::cout << ib.GetRelated(1, 9) << std::endl;         //-1
  std::cout << ib.GetRelated(1, 2, "128") << std::endl;  // 1
  std::cout << ib.GetRelated(1, 2, "124") << std::endl;  //-1
  std::cout << ib.GetRelated(1, 6, "128") << std::endl;  // 2
  std::cout << ib.GetRelated(1, 6, "124") << std::endl;  // 1
  for (auto const& each : ib.GetSteps(1, 1)) {
    std::cout << each << ' ';
  }
  std::cout << '\n';
  //{ 2, 3, 6 }*
  for (auto const& each : ib.GetSteps(1, 2)) {
    std::cout << each << ' ';
  }
  std::cout << '\n';
  //{ 7, 8 }*
  for (auto const& each : ib.GetSteps(1, 3)) {
    std::cout << each << ' ';
  }
  std::cout << '\n';
  //{ }
  for (auto const& each : ib.GetSteps(9, 1)) {
    std::cout << each << ' ';
  }
  std::cout << '\n';
  //{ }
  std::cout << ib.CountGroups() << std::endl;       // 3
  std::cout << ib.CountGroups("128") << std::endl;  // 6
  std::cout << ib.CountGroups("124") << std::endl;  // 6
  std::cout << ib.CountGroups("173") << std::endl;  // 10
  std::cout << ib.CountGroups(std::vector<std::string>{"128", "173"})
            << std::endl;  // 6
  std::cout << ib.CountGroups(std::vector<std::string>{"128", "124", "173"})
            << std::endl;  // 3
  ib.~IlliniBook();
  return 0;
}
