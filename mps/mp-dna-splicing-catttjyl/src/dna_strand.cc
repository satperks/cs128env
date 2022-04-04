#include "dna_strand.hpp"

#include <cassert>
#include <stdexcept>

#include "node.hpp"

DNAstrand::DNAstrand(const char* pt) {
  head_ = tail_ = new Node(pt[0]);
  Node* current = head_;
  for (unsigned int i = 1; i < StrLen(pt); i++) {
    Node* tmp = new Node(pt[i]);
    current->next = tmp;
    current = current->next;
  }
  tail_ = current;
}

DNAstrand::~DNAstrand() {
  while (head_ != nullptr) {
    Node* next = head_->next;
    delete head_;
    head_ = next;
  }
}

unsigned int StrLen(const char* input) {
  unsigned int len = 0;
  while (input[len] != '\0') {
    len++;
  }
  return len;
}

void DNAstrand::RemoveIdx(unsigned int& idx, const char* pattern) {
  Node* current = head_;
  unsigned int order = 1;
  unsigned int len = StrLen(pattern);
  while (current != nullptr) {
    unsigned int check = 0;
    Node* pt_current = current;
    for (size_t i = 0; i < len; i++) {
      if (pt_current == nullptr) return;
      // std::cout << "check for [" << pt_current->data << "] match ["
      //           << pattern[i] << "]" << std::endl;
      if (pt_current != nullptr && pt_current->data == pattern[i]) {
        check++;
        if (check == len) {
          idx = order;
        }
      }
      pt_current = pt_current->next;
    }
    // std::cout << '\n';
    current = current->next;
    order++;
  }
}

void DNAstrand::RemoveAt(unsigned int index) {
  if (index == 1) {
    Node* next = head_->next;
    delete head_;
    head_ = next;
    return;
  }
  Node* current = head_;
  for (unsigned int i = 1; i < index - 1; i++) {
    current = current->next;
  }
  // std::cout << current->next->data << std::endl;
  // std::cout << "current is " << current->data << std::endl;
  if (current->next == tail_) {
    // std::cout << "remove tail" << std::endl;
    delete tail_;
    tail_ = current;
    tail_->next = nullptr;
  } else {
    Node* next = current->next->next;
    delete current->next;
    current->next = next;
  }
}

void DNAstrand::InsertAtFront(Node*& begin, Node*& end) {
  // std::cout << "insert at front \n";
  Node* old_head = head_;
  head_ = begin;
  end->next = old_head;
}

void DNAstrand::InsertMiddle(unsigned int index, Node*& begin, Node*& end) {
  // std::cout << "insert in middle \n";
  Node* current = head_;
  for (unsigned int i = 1; i < index - 1; i++) {
    current = current->next;
  }
  Node* next = current->next;
  current->next = begin;
  end->next = next;
}

void DNAstrand::InsertAtEnd(Node*& begin, Node*& end) {
  // std::cout << "insert at end \n";
  tail_->next = begin;
  tail_ = end;
}

int DNAstrand::Size() {
  if (head_ == nullptr) {
    return 0;
  }
  int size = 0;
  Node* current = head_;
  while (current != nullptr) {
    size++;
    current = current->next;
  }
  return size;
}

void DNAstrand::SpliceIn(const char* pattern, DNAstrand& to_splice_in) {
  int this_size = Size();
  int splice_size = to_splice_in.Size();
  unsigned int idx = 0;
  unsigned int len = StrLen(pattern);
  RemoveIdx(idx, pattern);
  if (idx == 0) {
    throw std::invalid_argument("pattern doesn't exist");
  }
  // std::cout << "len of seq is: " << this_size << std::endl;
  // std::cout << "start to remove from " << idx << std::endl;
  // std::cout << "remove " << len << " strands" << std::endl;
  for (unsigned int i = 0; i < len; i++) {
    // std::cout << "remove" << i << ": ";
    RemoveAt(idx);
  }
  // std::cout << "--seq after remove: ";
  // PrintDNA(*this);
  Node* add_current = to_splice_in.head_;
  Node* begin = add_current;
  for (int i = 1; i < splice_size; i++) {
    add_current = add_current->next;
    // std::cout << add_current->data << std::endl;
  }
  Node* end = add_current;
  if (head_ == nullptr) {
    head_ = begin;
    tail_ = end;
    return;
  }
  // std::cout << "idx: " << idx << ", size: " << this_size << ", len: " << len
  //           << std::endl;
  if (idx == 1) {
    InsertAtFront(begin, end);
  } else if (idx == this_size - len + 1) {
    InsertAtEnd(begin, end);
  } else {
    InsertMiddle(idx, begin, end);
  }
  to_splice_in.head_ = to_splice_in.tail_ = nullptr;
}

// void DNAstrand::PrintDNA(const DNAstrand& dna) {
//   Node* current = dna.head_;
//   while (current != nullptr) {
//     std::cout << current->data << " ";
//     current = current->next;
//   }
//   std::cout << '\n';

//   std::cout << dna.head_ << std::endl;
//   std::cout << dna.tail_ << std::endl;
// }
