#include "schedule.hpp"

// Schedule() = default;
void Schedule::MarkAvailable(TimeSlot time) {
  for (const TimeSlot& ts : times_) {
    if (time.startTime == ts.startTime && time.endTime == ts.endTime) {
      times_.erase(ts);
      return;
    }
  }
}

void Schedule::MarkBusy(TimeSlot time) {
  if (!IsAvailable(time)) {
    return;
  }
  times_.insert(time);
}

bool Schedule::IsAvailable(TimeSlot time) const {
  for (TimeSlot busy : times_) {
    if (busy.startTime == time.startTime) {
      // if they have the same start times, then no matter
      // the duration, the time slot we are checking is
      // not available
      return false;
    } else if (time.startTime < busy.endTime &&
               time.startTime >= busy.startTime) {
      // if the time slot we are checking starts in the middle
      // of a busy block, then the time slot is at least
      // partially unavailable
      return false;
    } else if (time.startTime < busy.startTime) {
      // if the above conditions are false, and the slot we are
      // checking starts before the busy time, then the slot is
      // only available if it ends before the busy start time
      return time.endTime < busy.startTime;
    }

    // all of the above are false when the time we are checking
    // starts after the current busy time
  }

  // if this is reached, then the time slot does not overlap any
  // busy times and occurs after the last busy time
  return true;
}