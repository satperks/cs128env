#include "bathroom.hpp"

#include <vector>

Bathroom::Bathroom(): Room("bathroom") {}

bool Bathroom::CanAddPerson() { return people_.empty(); }