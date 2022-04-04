#include <iostream>

class SuperClass {
public:
  SuperClass() { std::cout << "superclass ctor" << std::endl; }
  virtual void Thing1() { std::cout << "superclass thing1" << std::endl; }
};

class SubClass : public SuperClass {
public:
  SubClass() { std::cout << "subclass ctor" << std::endl; }
  void Thing1() { std::cout << "subclass thing1" << std::endl; }
};

int main() {
  SubClass sub;
  SuperClass& sc = sub;
  sc.Thing1();
}