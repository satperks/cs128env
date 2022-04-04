#include <iomanip>
#include <sstream>
#include <stdexcept>
using std::endl;
using std::ostream;
using std::ostringstream;
using std::setfill;
using std::setw;
using std::string;

#include "doubly_linked_list.hpp"

DoublyLinkedList::DoublyLinkedList(char val): size_(1) {
  head_ = tail_ = new Node(val);
}

DoublyLinkedList::DoublyLinkedList(const std::vector<char>& values) {
  if (values.empty()) {
    size_ = 0;
    head_ = tail_ = nullptr;
  } else {
    size_ = values.size();
    for (size_t i = 0; i < values.size(); i++) {
      Node* tmp = new Node(values[i]);
      if (head_ == nullptr) {
        head_ = tail_ = tmp;
      } else {
        tail_->next = tmp;
        tmp->prev = tail_;
        tail_ = tmp;
      }
    }
  }
}

DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList& rhs) {
  if (rhs.Empty()) {
    size_ = 0;
    head_ = tail_ = nullptr;
  } else {
    size_ = rhs.size_;
    head_ = new Node(rhs.head_->data);
    Node* current = rhs.head_;
    Node* this_current = head_;
    while (current->next != nullptr) {
      this_current->next = new Node(current->next->data);
      this_current->next->prev = new Node(current->data);
      current = current->next;
      this_current = this_current->next;
    }
    tail_ = new Node(current->data);
  }
}

DoublyLinkedList& DoublyLinkedList::operator=(const DoublyLinkedList& rhs) {
  if (this != &rhs) {
    Clear();
    if (rhs.Empty()) {
      size_ = 0;
      head_ = tail_ = nullptr;
    } else {
      Node* current = rhs.head_;
      while (current != nullptr) {
        PushBack(current->data);
        current = current->next;
      }
    }
  }
  return *this;
}

DoublyLinkedList::~DoublyLinkedList() { Clear(); }

char& DoublyLinkedList::Front() {
  if (Empty()) {
    throw std::runtime_error("List is empty.");
  }
  return head_->data;
}

char& DoublyLinkedList::Back() {
  if (Empty()) {
    throw std::runtime_error("List is empty.");
  }
  return tail_->data;
}

void DoublyLinkedList::PopFront() {
  if (Empty()) {
    throw std::runtime_error("List is empty.");
  }
  size_--;
  if (size_ == 0) {
    head_ = tail_ = nullptr;
  } else {
    Node* tmp = head_->next;
    delete head_;
    head_ = tmp;
    head_->prev = nullptr;
  }
}

void DoublyLinkedList::PopBack() {
  if (Empty()) {
    throw std::runtime_error("List is empty.");
  }
  size_--;
  if (size_ == 0) {
    head_ = tail_ = nullptr;
  } else {
    Node* tmp = tail_->prev;
    delete tail_;
    tail_ = tmp;
    tail_->next = nullptr;
  }
}

void DoublyLinkedList::PushFront(char val) {
  size_++;
  Node* tmp = new Node(val);
  if (Empty()) {
    head_ = tail_ = tmp;
  } else {
    head_->prev = tmp;
    tmp->next = head_;
    head_ = tmp;
  }
}

void DoublyLinkedList::PushBack(char val) {
  size_++;
  Node* tmp = new Node(val);
  if (Empty()) {
    head_ = tail_ = tmp;
  } else {
    tail_->next = tmp;
    tmp->prev = tail_;
    tail_ = tmp;
  }
}

void DoublyLinkedList::InsertAt(size_t idx, char val) {
  if (idx > size_ || idx < 0) {
    throw std::invalid_argument("invalid input");
  }
  Node* tmp = new Node(val);
  if (idx == 0) {
    PushFront(val);
  } else if (idx == size_) {
    PushBack(val);
  } else {
    size_++;
    Node* current = head_;
    for (size_t i = 0; i < idx; i++) {
      current = current->next;
    }
    Node* prior = current->prev;
    current->prev->next = tmp;
    tmp->prev = prior;
    tmp->next = current;
    current->prev = tmp;
  }
}

void DoublyLinkedList::EraseAt(size_t idx) {
  if (Empty() || idx >= size_ || idx < 0) {
    throw std::invalid_argument("invalid input");
  }
  if (idx == 0) {
    PopFront();
  } else if (idx == size_ - 1) {
    PopBack();
  } else {
    size_--;
    Node* current = head_;
    for (size_t i = 0; i < idx; i++) {
      current = current->next;
    }
    current->next->prev = current->prev;
    current->prev->next = current->next;
    delete current;
  }
}

char& DoublyLinkedList::Find(char val) {
  if (Empty()) {
    throw std::invalid_argument("List is empty");
  }
  Node* current = head_;
  while (current != nullptr) {
    if (current->data == val) {
      return current->data;
    }
    current = current->next;
  }
  throw std::invalid_argument("val not found");
}

void DoublyLinkedList::Clear() {
  size_ = 0;
  while (head_ != nullptr) {
    Node* next = head_->next;
    delete head_;
    head_ = next;
  }
  tail_ = nullptr;
}

// Functions provided to you
ostream& operator<<(ostream& os, const DoublyLinkedList& ll) {
  constexpr unsigned int kWidth = 16;
  os << "Doubly Linked List" << endl;
  os << "Head: " << ll.head_ << "\t Tail: " << ll.tail_ << endl;
  os << "Size: " << ll.size_ << endl;
  if (ll.head_ == nullptr) return (os << "Empty" << endl);
  const Node* curr = ll.head_;
  os << "Nodes (accessible from head to tail):" << endl << endl;
  os << setw(kWidth) << setfill(' ') << ' ' << ' ' << Center("prev", kWidth - 1)
     << ' ' << Center("data", kWidth - 1) << ' ' << Center("next", kWidth - 1)
     << endl;
  while (curr != nullptr) {
    ostringstream oss;
    oss << (curr->prev);
    string prev = oss.str();
    oss.str("");
    oss << (curr->next);
    string next = oss.str();
    oss.str("");
    oss << (curr->data);
    string data = oss.str();
    oss.str("");
    oss << curr;
    string address = oss.str();
    os << setw(kWidth) << setfill(' ') << ' ' << '.' << setw(kWidth)
       << setfill('-') << '.' << setw(kWidth) << '.' << setw(kWidth) << '.'
       << endl;
    os << setw(kWidth) << setfill(' ') << Center(address, kWidth - 1) << '|'
       << setw(kWidth - 1) << setfill(' ') << Center(prev, kWidth - 1) << '|'
       << setw(kWidth - 1) << Center(data, kWidth - 1) << '|'
       << setw(kWidth - 1) << Center(next, kWidth - 1) << '|' << endl;
    os << setw(kWidth) << setfill(' ') << ' ' << '\'' << setw(kWidth)
       << setfill('-') << '\'' << setw(kWidth) << '\'' << setw(kWidth) << '\''
       << endl;
    os << endl;
    curr = curr->next;
  }
  return os;
}

std::string Center(const std::string& str, decltype(str.length()) col_width) {
  // quick and easy (but error-prone) implementation
  decltype(str.length()) padl = (col_width - str.length()) / 2;
  decltype(str.length()) padr = (col_width - str.length()) - padl;
  string strf = string(padl, ' ') + str + string(padr, ' ');
  return strf;
}