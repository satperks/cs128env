#ifndef LIVING_ROOM_HPP
#define LIVING_ROOM_HPP

#include <string>

#include "room.hpp"

class LivingRoom : public Room {
public:
  LivingRoom();
  void RemovePerson(const std::string& name) override;

protected:
  bool CanAddPerson() override { return true; }
};

#endif
