#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
#include <vector>

class Room {
public:
  Room() = default;

  Room(const std::string& room_name);

  std::string GetName() const;

  virtual void AddPerson(const std::string& name);

  virtual void RemovePerson(const std::string& name);

  const std::vector<std::string>& GetPeople() const;

protected:
  virtual bool CanAddPerson() = 0;

  std::vector<std::string> people_;

private:
  std::string name_;
};

#endif