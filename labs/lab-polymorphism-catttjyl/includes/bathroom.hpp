#ifndef BATHROOM_HPP
#define BATHROOM_HPP

#include "room.hpp"

class Bathroom : public Room {
public:
  Bathroom();

protected:
  bool CanAddPerson() override;
};

#endif