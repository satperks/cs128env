#ifndef HOSPITAL_HPP
#  define HOSPITAL_HPP

#  include <set>
#  include <string>
#  include <vector>

#  include "appointment.hpp"
#  include "doctor.hpp"

class Hospital {
public:
  Hospital() = default;
  void AddDoctor(Doctor& d);
  Doctor* GetAvailableDoctor(TimeSlot time);
  void AddAppointment(TimeSlot time, std::string patient);
  void RemoveAppointment(TimeSlot time, std::string patient);

private:
  std::vector<Doctor*> doctors_;
  std::vector<Appointment> appointments_;
};

#endif

// Has Doctors
// Keeps track of Appointments
// Can add doctors
// Can determine which of its doctors are available
// Can add appointments
// Can remove appointments