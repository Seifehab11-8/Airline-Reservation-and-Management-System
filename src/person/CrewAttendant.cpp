#include "../../header/person/CrewAttendant.hpp"


void CrewAttendant::setFlyingHours(const double flyingHours) {
    this->flyingHours = flyingHours;
}

double CrewAttendant::getFlyingHours() const {
    return flyingHours;
}