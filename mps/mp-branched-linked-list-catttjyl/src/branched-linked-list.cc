#include "branched-linked-list.hpp"

#include <stdexcept>
#include <string>

BLL::BLL(const BLL& to_copy) {
  if (to_copy.head_ == nullptr) {
    head_ = nullptr;
  } else {
    head_ = new Node(to_copy.head_->data_);
    Node* this_current = head_;
    Node* copy_current = to_copy.head_;
    while (copy_current != nullptr) {
      if (copy_current->next_bll_ != nullptr) {
        BLL* tmp = new BLL(*copy_current->next_bll_);
        this_current->next_bll_ = tmp;
      }
      if (copy_current->next_node_ != nullptr) {
        Node* next = copy_current->next_node_;
        this_current->next_node_ = new Node(next->data_);
      }
      this_current = this_current->next_node_;
      copy_current = copy_current->next_node_;
    }
  }
}

BLL::~BLL() {
  ClearRecur(head_);
  head_ = nullptr;
}

void BLL::ClearRecur(Node* node) {
  if (node != nullptr) {
    delete node->next_bll_;
    ClearRecur(node->next_node_);
    delete node;
  }
}

BLL& BLL::operator=(const BLL& rhs) {
  if (this != &rhs) {
    this->~BLL();
    if (rhs.head_ == nullptr) {
      head_ = nullptr;
      return *this;
    }
    head_ = new Node(rhs.head_->data_);
    Node* this_current = head_;
    // std::cout << "create head_ with" << head_->data_ << std::endl;
    Node* rhs_current = rhs.head_;
    while (rhs_current != nullptr) {
      if (rhs_current->next_bll_ != nullptr) {
        BLL* tmp = new BLL(*rhs_current->next_bll_);
        this_current->next_bll_ = tmp;
      }
      if (rhs_current->next_node_ != nullptr) {
        Node* next = rhs_current->next_node_;
        this_current->next_node_ = new Node(next->data_);
        // std::cout << "create node with" << next->data_ << std::endl;
      }
      this_current = this_current->next_node_;
      rhs_current = rhs_current->next_node_;
    }
  }
  return *this;
}

Node* BLL::PushBack(char dat) {
  Node* tmp = new Node(dat);
  if (head_ == nullptr) {
    head_ = tmp;
  } else {
    Node* current = head_;
    while (current->next_node_ != nullptr) {
      current = current->next_node_;
    }
    current->next_node_ = tmp;
  }
  return tmp;
}

char BLL::GetAt(size_t idx) const {
  if (idx >= this->Size() || idx < 0)
    throw std::invalid_argument("invalid idx");
  // if (idx == 0) return head_->data_;
  Node* current = head_;
  for (size_t i = 0; i < this->Size(); i++) {
    if (i == idx) {
      break;
    }
    current = GetNextNode(current);
  }
  return current->data_;
}

void BLL::SetAt(size_t idx, char dat) {
  if (idx >= this->Size() || idx < 0)
    throw std::invalid_argument("invalid idx");
  Node* current = head_;
  for (size_t i = 0; i < this->Size(); i++) {
    if (i == idx) {
      current->data_ = dat;
      return;
    }
    current = GetNextNode(current);
  }
}

void BLL::Join(size_t idx, BLL* list) {
  // std::cout << this->Size() << std::endl;
  size_t size = Size();
  if (idx >= size) throw std::invalid_argument("idx too large");
  Node* current = head_;
  for (size_t i = 0; i < size; i++) {
    if (current->next_bll_ != nullptr)
      throw std::invalid_argument("next_bll_ already exist");
    if (i == idx) {
      current->next_bll_ = list;
      break;
    }
    current = current->next_node_;
  }
  if (!IsBLLAcyclic()) {
    current->next_bll_ = nullptr;
    throw std::invalid_argument("cyclic BLL");
  }
}

std::string BLL::ToString() const {
  std::string to_return;
  if (head_ != nullptr) {
    Node* current = head_;
    while (current != nullptr) {
      to_return.push_back(current->data_);
      if (current->next_bll_ != nullptr) {
        to_return += current->next_bll_->ToString();
      }
      current = current->next_node_;
    }
  }
  return to_return;
}

size_t BLL::Size() const {
  size_t count = 0;
  if (head_ != nullptr) {
    Node* current = head_;
    while (current != nullptr) {
      count++;
      if (current->next_bll_ != nullptr) {
        count += current->next_bll_->Size();
      }
      current = current->next_node_;
    }
  }
  return count;
}

bool BLL::IsBLLAcyclic() const {
  if (head_ != nullptr) {
    Node* tor = head_;
    Node* hare = GetNextNode(head_);
    while (tor != nullptr && hare != nullptr && GetNextNode(hare) != nullptr) {
      if (tor == hare) {
        return false;
      }
      tor = GetNextNode(tor);
      hare = GetNextNode(GetNextNode(hare));
    }
  }
  return true;
}

Node* BLL::GetNextNode(const Node* first) const {
  Node* next = nullptr;
  if (first->next_bll_ != nullptr) {
    next = first->next_bll_->head_;
  } else if (first->next_node_ != nullptr) {
    next = first->next_node_;
  }
  return next;
}