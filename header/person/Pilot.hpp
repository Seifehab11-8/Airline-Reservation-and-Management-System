#ifndef _PILOT_HPP
#define _PILOT_HPP
#include "CrewAttendant.hpp"
#include <iostream>
#include <memory>
class Pilot : public CrewAttendant {
    private:
    friend std::istream& operator >> (std::istream & is, Pilot& pilot);
    friend std::ostream& operator <<(std::ostream & os, const Pilot& pilot);   
    public:
    Pilot();
    Pilot(const Pilot & other) = default;
    Pilot(Pilot && other) = default;
};
using PilotPtr = std::shared_ptr<Pilot>;
std::istream& operator >> (std::istream & is, Pilot& pilot);
std::ostream& operator <<(std::ostream & os, const Pilot& pilot);
#endif