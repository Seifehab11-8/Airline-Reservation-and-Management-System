#include "../../header/person/Pilot.hpp"

std::istream& operator >> (std::istream & is, Pilot& pilot){
    is.ignore();
    std::cout<<"Enter Captain's name: ";
    std::getline(is, pilot.name);
    std::cout<<"Enter Captain's ID eg.(PLxxx): ";
    std::getline(is,pilot.id);
    return is;
}
std::ostream& operator <<(std::ostream & os, const Pilot& pilot){
    std::cout<<"Pilot ID: "
                <<pilot.id
                <<" - Captain "
                <<pilot.name;
    return os;
}

Pilot::Pilot() : CrewAttendant() {
    this->role = "Pilot";
}

bool Pilot::operator == (const Pilot &other) const {
    return this->id == other.id;
}
