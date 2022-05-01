#include "cord.hpp"

#include <stdexcept>

#include "cord-utilities.hpp"

Cord::Cord(const std::string& dat) {
  data_ = dat;
  length_ = dat.length();
}

Cord::Cord(const std::shared_ptr<Cord>& left_cord,
           const std::shared_ptr<Cord>& right_cord):
    left_(left_cord), right_(right_cord) {
  length_ = left_cord->length_ + right_cord->length_;
}

size_t Cord::Length() const { return length_; }

std::shared_ptr<Cord> Cord::GetLeft() const { return left_; }

std::shared_ptr<Cord> Cord::GetRight() const { return right_; }

const std::string& Cord::GetData() const { return data_; }

std::string Cord::ToString() const {
  std::string to_return;
  // std::cout << "reach here '\n'";
  if (!data_.empty())
    to_return += data_;
  else
    to_return += left_->ToString() + right_->ToString();

  // std::cout << "succeed '\n'";
  return to_return;
}

std::shared_ptr<Cord> Cord::SubString(size_t lower_idx, size_t upper_idx) {
  std::shared_ptr<Cord> to_return;
  if (lower_idx == 0 && upper_idx == length_) return shared_from_this();

  if (!data_.empty()) {
    // std::cout << data_.substr(lower_idx, upper_idx - lower_idx) << std::endl;
    return std::make_shared<Cord>(
        data_.substr(lower_idx, upper_idx - lower_idx));
  }

  if (upper_idx <= left_->length_) {
    // std::cout << "go left: (" << lower_idx << ", " << upper_idx << ")"
    //           << std::endl;
    to_return = left_->SubString(lower_idx, upper_idx);
  } else if (lower_idx >= left_->length_) {
    // std::cout << "go right : (" << lower_idx - left_->length_ << ", "
    //           << upper_idx - left_->length_ << ")" << std::endl;
    to_return = right_->SubString(lower_idx - left_->length_,
                                  upper_idx - left_->length_);
  } else {
    // std::cout << "separate: connect(" << lower_idx << ", " << left_->length_
    //           << ") and (0, " << upper_idx - left_->length_ << ")" <<
    //           std::endl;
    to_return = ConcatCords(left_->SubString(lower_idx, left_->length_),
                            right_->SubString(0, upper_idx - left_->length_));
  }
  return to_return;
}

char Cord::At(size_t idx) const {
  char to_return = ' ';
  if (idx < 0 || idx >= length_)
    throw std::invalid_argument("idx out of bound");

  if (!data_.empty()) {
    return data_.at(idx);
  }

  if (left_ != nullptr && idx < left_->length_) {
    to_return = left_->At(idx);
  } else {
    to_return = right_->At(idx - left_->length_);
  }
  return to_return;
}

bool Cord::IsValidCord() const {
  if (left_ == nullptr && right_ == nullptr) {
    if (data_.length() != length_) return false;
  } else {
    if ((length_ != left_->length_ + right_->length_) || !data_.empty())
      return false;
    return left_->IsValidCord() && right_->IsValidCord();
  }
  return true;
}
