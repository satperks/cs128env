#include <iostream>

#include "branched-linked-list.hpp"

int main() {
  /* EXAMPLE INTERACTIONS WITH BLL */

  BLL* test = new BLL();
  test->PushBack('H');
  test->PushBack('I');
  test->PushBack('O');
  test->PushBack('K');

  BLL* join = new BLL();
  join->PushBack('A');
  join->PushBack('B');
  join->PushBack('C');
  join->PushBack('D');

  // BLL* join2 = new BLL();
  // join->PushBack('X');
  // join->PushBack('Y');
  // join->PushBack('Z');

  test->Join(3, join);
  std::cout << test->ToString() << std::endl;  // HIOKABCDF
  // join->Join(2, join2);
  // std::cout << test->ToString() << std::endl;  // HIOKABCXYZDF

  test->SetAt(4, '?');
  std::cout << test->ToString() << std::endl;  // HIOK?BCDF
  std::cout << test->GetAt(2) << std::endl;    // O
  std::cout << test->GetAt(6) << std::endl;    // C

  std::cout << test->Size() << std::endl;  // 6

  test->PushBack('@');
  std::cout << test->ToString() << std::endl;  // HIOK?BCDF@

  delete test;
  // test->~BLL();
  // std::cout << test->ToString() << std::endl;

  // BLL* test_clone1 = new BLL();
  // *test_clone1 = *test;
  // BLL* test_clone2(test);

  // std::cout << test_clone1->ToString() << std::endl;  // HA?CIO
  // std::cout << test_clone2->ToString() << std::endl;  // HA?CIO

  // BLL* first = new BLL();
  // first->PushBack('h');
  // first->PushBack('i');
  // std::cout << "first-----" << std::endl;
  // std::cout << first->ToString() << std::endl;  // hi
  // std::cout << first->Size() << std::endl;      // 2

  // // /////////////////////////////////////

  // BLL* second = new BLL();
  // second->PushBack('i');
  // second->PushBack('!');
  // second->PushBack('@');

  // std::cout << "second-----" << std::endl;
  // std::cout << second->ToString() << std::endl;  // i!@
  // std::cout << second->Size() << std::endl;      // 3

  // // /////////////////////////////////////

  // std::cout << "after join-----" << std::endl;
  // first->Join(1, second);

  // std::cout << first->ToString() << std::endl;  // hii!@
  // std::cout << first->Size() << std::endl;      // 5

  // std::cout << second->ToString() << std::endl;  // i!@
  // std::cout << second->Size() << std::endl;      // 3

  // // /////////////////////////////////////

  // BLL* first_clone = new BLL();
  // *first_clone = *first;
  // std::cout << "first_clone-----" << std::endl;
  // std::cout << first_clone->ToString() << std::endl;  // hii!@
  // std::cout << first_clone->Size() << std::endl;      // 5

  // BLL* second_clone(second);
  // std::cout << "second_clone-----" << std::endl;
  // std::cout << second_clone->ToString() << std::endl;  // i!@
  // std::cout << second_clone->Size() << std::endl;      // 3

  return 0;
}
