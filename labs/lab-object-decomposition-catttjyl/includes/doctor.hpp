#ifndef DOCTOR_HPP
#  define DOCTOR_HPP

#  include <set>
#  include <string>
#  include <vector>

#  include "schedule.hpp"
#  include "timeslot.hpp"

class Doctor {
public:
  Doctor() = default;
  bool IsAvailable(TimeSlot time) const;
  void AddAppointment(TimeSlot time);
  void RemoveAppointment(TimeSlot time);

private:
  Schedule schedule_;
};

#endif

// Has a Schedule
// Knows when they are available
// Can add appointments
// Can remove appointments
