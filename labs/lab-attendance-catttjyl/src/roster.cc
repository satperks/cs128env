#include "roster.hpp"

#include <iostream>

Roster::Roster(const Student& student) {
  head_ = std::make_unique<RosterEntry>(student, nullptr);
}

void Roster::AddStudent(const Student& student) {
  std::unique_ptr<RosterEntry> tmp =
      std::make_unique<RosterEntry>(student, nullptr);

  if (head_.get() == nullptr) {
    head_ = std::move(tmp);
  } else if (student <= head_->student) {
    tmp->next = std::move(head_);
    head_ = std::move(tmp);
  } else {
    RosterEntry* current = head_.get();
    while (current->next != nullptr) {
      if (current->student <= student && student <= current->next->student) {
        tmp->next = std::move(current->next);
        current->next = std::move(tmp);
        return;
      }
      current = current->next.get();
    }
    current->next = std::move(tmp);
  }
}

Roster::Iterator Roster::begin() const { return Iterator(head_.get()); }

Roster::Iterator Roster::end() const { return Iterator(); }
