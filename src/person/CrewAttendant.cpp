#include "../../header/person/CrewAttendant.hpp"


void CrewAttendant::setFlyingHours(const double flyingHours) {
    this->flyingHours = flyingHours;
}

double CrewAttendant::getFlyingHours() const {
    return flyingHours;
}

void CrewAttendant::setOccupation(const bool occupation) {
    this->occupation = occupation;
}

bool CrewAttendant::getOccupation() const {
    return occupation;
}
bool CrewAttendant::operator==(const CrewAttendant &other) const {
    return (this->id == other.id);
}
