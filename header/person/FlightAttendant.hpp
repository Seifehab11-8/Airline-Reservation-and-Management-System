#ifndef _FLIGHT_ATTENDANT_HPP
#define _FLIGHT_ATTENDANT_HPP
#include "CrewAttendant.hpp"
#include <memory>
class FlightAttendant : public CrewAttendant {
    private:
    friend std::istream& operator >> (std::istream & is, FlightAttendant& pilot);
    friend std::ostream& operator <<(std::ostream & os, const FlightAttendant& pilot);   
    public:
    FlightAttendant();
    FlightAttendant(const FlightAttendant & other) = default;
    FlightAttendant(FlightAttendant && other) = default;
};
using FAPtr = std::shared_ptr<FlightAttendant>;
std::istream& operator >> (std::istream & is, FlightAttendant& pilot);
std::ostream& operator <<(std::ostream & os, const FlightAttendant& pilot);
#endif
