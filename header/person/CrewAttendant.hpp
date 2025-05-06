#ifndef _CREW_ATTENDANT_HPP
#define _CREW_ATTENDANT_HPP
#include "Person.hpp"

class CrewAttendant : public Person {
    protected:
    double flyingHours;
    public:
    CrewAttendant() = default;
    CrewAttendant(const CrewAttendant & other) = default;
    CrewAttendant(CrewAttendant && other) = default;
    void setFlyingHours(const double flyingHours);
    double getFlyingHours() const;
};

#endif