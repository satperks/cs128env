#include <iostream>
#include <string>

#include "bathroom.hpp"
#include "kitchen.hpp"
#include "living-room.hpp"
#include "room.hpp"

void PrintVec(std::vector<std::string> vec) {
  std::cout << "[ ";
  for (std::string s : vec) {
    std::cout << "'" << s << "' ";
  }
  std::cout << "]" << std::endl;
}

/* As you begin to develop Room, uncomment below */

void PrintRoomContents(const Room& room) {
  std::cout << "People in " << room.GetName() << ": ";
  PrintVec(room.GetPeople());
}

int main() {
  Bathroom bathroom;
  Room& rb = bathroom;

  PrintRoomContents(rb);
  rb.AddPerson("Steve");
  PrintRoomContents(rb);
  rb.AddPerson("Andy");
  PrintRoomContents(rb);
  rb.RemovePerson("Steve");
  rb.AddPerson("Andy");
  PrintRoomContents(rb);

  Kitchen kitchen;
  Room& rk = kitchen;

  rk.AddPerson("Helen");
  rk.AddPerson("Mia");
  PrintRoomContents(rk);

  LivingRoom living_room;
  Room& rl = living_room;

  rl.AddPerson("Alex");
  rl.AddPerson("Daniel");
  PrintRoomContents(rl);
  rl.RemovePerson("Daniel");
  PrintRoomContents(rl);
}