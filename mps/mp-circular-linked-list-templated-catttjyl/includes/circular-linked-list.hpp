#ifndef CIRCULAR_LINKED_LIST_HPP
#define CIRCULAR_LINKED_LIST_HPP

#include <iostream>

#include "node.hpp"

enum class Order { kASC, kDESC };

template <typename T>
class CircularLinkedList {
public:
  CircularLinkedList() = default;
  CircularLinkedList(const CircularLinkedList<T>& source);
  CircularLinkedList<T>& operator=(const CircularLinkedList<T>& source);
  ~CircularLinkedList();

  void InsertInOrder(const T& data);
  void Ascending(const T& data);
  void Descending(const T& data);

  void Reverse();

  template <typename U>
  friend std::ostream& operator<<(std::ostream& os,
                                  const CircularLinkedList<U>& cll);

private:
  Node<T>* head_ = nullptr;
  Node<T>* tail_ = nullptr;
  Order node_order_ = Order::kASC;
};

// template <typename T>
// CircularLinkedList<T>::CircularLinkedList() {
//   head_ = tail_ = nullptr;
//   node_order_ = Order::kASC;
// }

template <typename T>
CircularLinkedList<T>::CircularLinkedList(const CircularLinkedList<T>& source) {
  if (source.head_ == nullptr) {
    head_ = tail_ = nullptr;
    node_order_ = Order::kASC;
  } else if (source.head_->next == source.head_) {
    head_ = tail_ = new Node<T>(source.head_->data);
    tail_->next = head_;
  } else {
    head_ = new Node<T>(source.head_->data);
    Node<T>* current = head_;
    Node<T>* s_next = source.head_->next;
    while (s_next != source.tail_) {
      current->next = new Node<T>(s_next->data);
      current = current->next;
      s_next = s_next->next;
    }
    current->next = new Node<T>(s_next->data);
    tail_ = current->next;
    tail_->next = head_;
    node_order_ = source.node_order_;
  }
}

template <typename T>
CircularLinkedList<T>& CircularLinkedList<T>::operator=(
    const CircularLinkedList<T>& source) {
  if (this != &source) {
    this->~CircularLinkedList();
    if (source.head_ == nullptr) {
      head_ = tail_ = nullptr;
      node_order_ = Order::kASC;
      return *this;
    }
    if (source.head_->next == source.head_) {
      head_ = tail_ = new Node<T>(source.head_->data);
      tail_->next = head_;
      return *this;
    }
    head_ = new Node<T>(source.head_->data);
    Node<T>* current = head_;
    Node<T>* s_next = source.head_->next;
    while (s_next != source.tail_) {
      current->next = new Node<T>(s_next->data);
      current = current->next;
      s_next = s_next->next;
    }
    current->next = new Node<T>(s_next->data);
    tail_ = current->next;
    tail_->next = head_;
    node_order_ = source.node_order_;
  }
  return *this;
}

template <typename T>
CircularLinkedList<T>::~CircularLinkedList() {
  node_order_ = Order::kASC;

  while (head_ != nullptr && head_ != tail_) {
    Node<T>* next = head_->next;
    delete head_;
    head_ = next;
  }
  delete tail_;
  head_ = tail_ = nullptr;
}

template <typename T>
void CircularLinkedList<T>::InsertInOrder(const T& data) {
  if (head_ == nullptr) {
    head_ = tail_ = new Node<T>(data);
    tail_->next = head_;
  } else {
    if (node_order_ == Order::kASC)
      Ascending(data);
    else
      Descending(data);
  }
}

template <typename T>
void CircularLinkedList<T>::Ascending(const T& data) {
  auto tmp = new Node<T>(data);
  if (data <= head_->data) {
    tail_->next = tmp;
    tmp->next = head_;
    head_ = tmp;
  } else if (data >= tail_->data) {
    tail_->next = tmp;
    tmp->next = head_;
    tail_ = tmp;
  } else {
    Node<T>* current = head_;
    while (current != tail_) {
      if (current->data <= data && current->next->data >= data) {
        tmp->next = current->next;
        current->next = tmp;
        return;
      }
      current = current->next;
    }
  }
}

template <typename T>
void CircularLinkedList<T>::Descending(const T& data) {
  auto tmp = new Node<T>(data);
  if (data >= head_->data) {
    tail_->next = tmp;
    tmp->next = head_;
    head_ = tmp;
  } else if (data <= tail_->data) {
    tail_->next = tmp;
    tmp->next = head_;
    tail_ = tmp;
  } else {
    Node<T>* current = head_;
    while (current != tail_) {
      if (current->data >= data && current->next->data <= data) {
        tmp->next = current->next;
        current->next = tmp;
        return;
      }
      current = current->next;
    }
  }
}

template <typename T>
void CircularLinkedList<T>::Reverse() {
  if (node_order_ == Order::kASC) {
    std::cout << "kASC now become kDESC" << std::endl;
    node_order_ = Order::kDESC;
  } else {
    std::cout << "kDESC now become kASC" << std::endl;
    node_order_ = Order::kASC;
  }
  if (head_ != nullptr) {
    Node<T>* current = head_;
    Node<T>* next = current->next;
    Node<T>* ahead = current->next->next;
    Node<T>* old_head = head_;
    Node<T>* old_tail = tail_;
    while (current != tail_) {
      next->next = current;
      current = next;
      next = ahead;
      ahead = ahead->next;
    }
    next->next = current;
    head_->next = tail_;
    head_ = old_tail;
    tail_ = old_head;
  }
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const CircularLinkedList<T>& cll) {
  // std::cout << "reach operator <<" << std::endl;
  Node<T>* iter = cll.head_;
  // empty list condition
  if (iter == nullptr) {
    os << "Empty list";
    return os;
  }
  // non-empty list condition
  do {
    os << iter->data << '\t';
    iter = iter->next;
  } while (iter != cll.head_);

  return os;
}

#endif