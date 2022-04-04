#include <iostream>
#include <stdexcept>
#include <vector>

#include "doubly_linked_list.hpp"

using namespace std;

int main() {
  DoublyLinkedList dll('s');
  std::cout << dll << std::endl;
  dll.PushBack('a');
  dll.PushBack('b');
  dll.PushBack('c');
  dll.PushFront('d');
  dll.PushFront('e');
  dll.InsertAt(2, '!');
  dll.EraseAt(2);
  dll.PushBack('f');
  dll.PushBack('g');
  dll.InsertAt(5, '?');
  dll.PushFront('h');
  dll.PopBack();
  dll.PopFront();
  std::cout << dll << std::endl;
  //   std::cout << dll.Front() << std::endl;
  //   std::cout << dll.Back() << std::endl;
  //   std::cout << dll.Find('b') << std::endl;

  // DoublyLinkedList dll_copy(dll);
  // std::cout << dll_copy << std::endl;

  // DoublyLinkedList dll_oper('i');
  // std::cout << dll_oper << std::endl;
  // dll_oper = dll;
  // std::cout << dll_oper << std::endl;

  return 0;
}
