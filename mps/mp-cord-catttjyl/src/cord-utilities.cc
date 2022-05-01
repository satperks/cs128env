#include "cord-utilities.hpp"

#include <stdexcept>

std::shared_ptr<Cord> ConcatCords(std::shared_ptr<Cord> left_cord,
                                  std::shared_ptr<Cord> right_cord) {
  if (!left_cord->IsValidCord() || !right_cord->IsValidCord())
    throw std::invalid_argument("input not valid");
  return std::make_shared<Cord>(left_cord, right_cord);
}

void ReduceCords(cs128::ReferenceList<std::shared_ptr<Cord>> cords) {
  cords.size();
}
