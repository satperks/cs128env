#ifndef SCHEDULE_HPP
#define SCHEDULE_HPP

#  include <set>
#  include <string>
#  include <vector>

#  include "timeslot.hpp"

class Schedule {
public:
  Schedule() = default;
  void MarkAvailable(TimeSlot time);
  void MarkBusy(TimeSlot time);
  bool IsAvailable(TimeSlot time) const;

private:
  std::set<TimeSlot> times_;
};

#endif

// Has a list of busy TimeSlots
// Can record times as busy
// Can record times as available
// Can determine what times are available