#include <cassert>
#include <iostream>

#include "cord-utilities.hpp"
#include "cord.hpp"

int main() {
  // std::shared_ptr<Cord> c2 = std::make_shared<Cord>("CS12");
  // std::shared_ptr<Cord> c4 = std::make_shared<Cord>("8 is stu");
  // std::shared_ptr<Cord> c5 = std::make_shared<Cord>("pid");
  // std::shared_ptr<Cord> c3 = ConcatCords(c4, c5);
  // std::shared_ptr<Cord> c1 = ConcatCords(c2, c3);

  // std::cout << c1->ToString() << std::endl;
  // std::cout << c2->ToString() << std::endl;
  // std::cout << c3->ToString() << std::endl;
  // std::cout << c4->ToString() << std::endl;
  // std::cout << c5->ToString() << std::endl;

  // for (size_t i = 0; i < c1->Length(); ++i) {
  //   std::cout << c1->At(i) << std::endl;
  // }

  // helloworld
  // std::shared_ptr<Cord> c3 = std::make_shared<Cord>("he");
  // std::shared_ptr<Cord> c4 = std::make_shared<Cord>("llo");
  // std::shared_ptr<Cord> c6 = std::make_shared<Cord>("wor");
  // std::shared_ptr<Cord> c7 = std::make_shared<Cord>("ld");
  // std::shared_ptr<Cord> c2 = ConcatCords(c3, c4);
  // std::shared_ptr<Cord> c5 = ConcatCords(c6, c7);
  // std::shared_ptr<Cord> c1 = ConcatCords(c2, c5);

  // // prepossession
  std::shared_ptr<Cord> c2 = std::make_shared<Cord>("pre");
  std::shared_ptr<Cord> c4 = std::make_shared<Cord>("po");
  std::shared_ptr<Cord> c6 = std::make_shared<Cord>("sse");
  std::shared_ptr<Cord> c7 = std::make_shared<Cord>("ssion");
  std::shared_ptr<Cord> c5 = ConcatCords(c6, c7);
  std::shared_ptr<Cord> c3 = ConcatCords(c4, c5);
  std::shared_ptr<Cord> c1 = ConcatCords(c2, c3);

  std::cout << c1->ToString() << std::endl;
  std::cout << c1->SubString(3, 8)->ToString() << std::endl;
  return 0;
}
