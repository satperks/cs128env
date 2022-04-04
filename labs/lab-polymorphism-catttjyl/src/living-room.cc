#include "living-room.hpp"

LivingRoom::LivingRoom(): Room("living room") {}

void LivingRoom::RemovePerson(const std::string& name) {
  for (size_t i = 0; i < people_.size(); ++i) {
    if (people_.at(i) == name) {
      people_.erase(people_.begin() + i);
      people_.erase(people_.begin());
      return;
    }
  }
}