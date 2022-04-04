#ifndef DOUBLYLINKEDLIST_HPP
#define DOUBLYLINKEDLIST_HPP

#include <cstdlib>  // provides definition for size_t, the maximum size of a theoretically possible object of any type
#include <iostream>
#include <string>
#include <vector>

#include "node.hpp"

class DoublyLinkedList {
public:
  DoublyLinkedList() = default;
  DoublyLinkedList(char val);
  explicit DoublyLinkedList(const std::vector<char>& values);
  DoublyLinkedList(const DoublyLinkedList& rhs);
  DoublyLinkedList& operator=(const DoublyLinkedList& rhs);
  ~DoublyLinkedList();

  char& Back();
  char& Front();
  void PopBack();
  void PopFront();

  void PushBack(char val);
  void PushFront(char val);

  void InsertAt(size_t idx, char val);
  void EraseAt(size_t idx);

  char& Find(char val);
  void Clear();

  size_t Size() const { return size_; }
  bool Empty() const { return (head_ == nullptr); };

  friend std::ostream& operator<<(
      std::ostream& os,
      const DoublyLinkedList& ll);  // friend b/c we don't have iterators yet!

private:
  Node* head_ = nullptr;
  Node* tail_ = nullptr;
  size_t size_ = 0;
};

std::ostream& operator<<(std::ostream& os, const DoublyLinkedList& ll);
std::string Center(const std::string& str, decltype(str.length()) col_width);

#endif