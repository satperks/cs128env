#include <iostream>

#include "circular-linked-list.hpp"

int main() {
  CircularLinkedList<int> cll;
  //   cll.Reverse();
  //   cll.Reverse();
  cll.InsertInOrder(2);
  std::cout << "cll: " << cll << std::endl;
  //   cll.InsertInOrder(5);
  //   cll.InsertInOrder(8);
  //   std::cout << cll << std::endl;
  //   cll.InsertInOrder(4);
  //   std::cout << cll << std::endl;

  CircularLinkedList<int> cll_cons(cll);
  std::cout << "cll_cons: " << cll_cons << std::endl;

  CircularLinkedList<int> cll_copy;
  cll_copy = cll;
  std::cout << "cll_copy:" << cll_copy << std::endl;

  //   cll.Reverse();
  //   std::cout << "after reverse1: " << cll << std::endl;
  //   cll.InsertInOrder(3);
  //   std::cout << "adding 3: " << cll << std::endl;
  //   cll.Reverse();
  //   std::cout << "after reverse2: " << cll << std::endl;

  return 0;
}
