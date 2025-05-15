#ifndef _CREW_ATTENDANT_HPP
#define _CREW_ATTENDANT_HPP
#include "Person.hpp"

class CrewAttendant : public Person {
    protected:
    bool occupation = false; // busy or free
    double flyingHours;
    public:
    CrewAttendant() = default;
    CrewAttendant(const CrewAttendant & other) = default;
    CrewAttendant(CrewAttendant && other) = default;
    CrewAttendant& operator = (const CrewAttendant & other) = default;
    CrewAttendant& operator = (CrewAttendant && other) = default;
    void setFlyingHours(const double flyingHours);
    double getFlyingHours() const;
    void setOccupation(const bool occupation);
    bool getOccupation() const;
    bool operator == (const CrewAttendant &other) const;
};

#endif