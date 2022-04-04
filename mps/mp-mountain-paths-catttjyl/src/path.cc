#include "path.hpp"

Path::Path(size_t length, size_t starting_row):
    length_(length), starting_row_(starting_row) {
  for (size_t i = 0; i < length; i++) {
    path_.push_back(starting_row);
  }
}
// Initializes the primitive data members with their respective values from
// arguments; initializes path_ std::vector<size_t> of length elements.

size_t Path::Length() const { return length_; }

size_t Path::StartingRow() const { return starting_row_; }

unsigned int Path::EleChange() const { return ele_change_; }

void Path::IncEleChange(unsigned int value) {
  if (value > 0) {
    ele_change_ += value;
  }
}

const std::vector<size_t>& Path::GetPath() const { return path_; }

void Path::SetLoc(size_t col, size_t row) { path_.at(col) = row; }
// Assigns the value of row (path_.at(col) will evaluate to row)

// size_t length_;
// size_t starting_row_;
// std::vector<size_t> path_;
// unsigned int ele_change_ = 0;
