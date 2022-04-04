#include "doctor.hpp"

bool Doctor::IsAvailable(TimeSlot time) const {
  return schedule_.IsAvailable(time);
}

void Doctor::AddAppointment(TimeSlot time) {
  if (!IsAvailable(time)) {
    return;
  }
  schedule_.MarkBusy(time);
}

void Doctor::RemoveAppointment(TimeSlot time) { schedule_.MarkAvailable(time); }
