#include "../../header/flight/Flight.hpp"

std::string Flight::getFlightNumber() const
{
    return flightNumber;
}
std::string Flight::getOrigin() const
{
    return origin;
}
std::string Flight::getDestination() const
{
    return destination;
}
DatePtr Flight::getDeptTime() const
{
    return deptTime;
}
DatePtr Flight::getArrivalTime() const
{
    return arrivalTime;
}
std::string Flight::getAircraftType() const
{
    return aircraftType;
}
int Flight::getNumOfSeats() const
{
    return numOfSeats;
}
std::string Flight::getStatus() const
{
    return status;
}
void Flight::setFlightNumber(const std::string& flightNumber)
{
    this->flightNumber = flightNumber;
}
void Flight::setOrigin(const std::string& origin)
{
    this->origin = origin;
}
void Flight::setDestination(const std::string& destination)
{
    this->destination = destination;
}
void Flight::setDeptTime(const DatePtr deptTime)
{
    this->deptTime = deptTime;
}
void Flight::setArrivalTime(const DatePtr arrivalTime)
{
    this->arrivalTime = arrivalTime;
}
void Flight::setAircraftType(const std::string& aircraftType)
{
    this->aircraftType = aircraftType;
}
void Flight::setNumOfSeats(int numOfSeats)
{
    this->numOfSeats = numOfSeats;
}
void Flight::setStatus(const std::string& status)
{
    this->status = status;
}
void Flight::setFlightAttendant(const FAPtr fa_ptr)
{
    this->fa_ptr = fa_ptr;
}
void Flight::setPilot(const PilotPtr pl_ptr)
{
    this->pl_ptr = pl_ptr;
}
int Flight::getNumOfAvailableSeats() const
{
    return numOfAvailableSeats;
}
void Flight::setNumOfAvailableSeats(int numOfAvailableSeats)
{
    this->numOfAvailableSeats = numOfAvailableSeats;
}
double Flight::getPrice() const
{
    return price;
}
void Flight::setPrice(double price)
{
    this->price = price;
}
FAPtr Flight::getFlighAttendant() const
{
    return fa_ptr;
}
PilotPtr Flight::getPilot() const
{
    return pl_ptr;
}
std::ostream& operator<<(std::ostream& os, const Flight& flight)
{
    os << "Flight Number: " << flight.flightNumber << "\n"
    << "Departure: " << *(flight.deptTime) << "\n"
    << "Arrival: " << *(flight.arrivalTime) << "\n"
    << "Aircraft: " << flight.aircraftType << "\n"
    << "Origin: " << flight.origin << "\n"
    << "Destination: " << flight.destination << "\n"
    << "Available Seats: " << flight.numOfAvailableSeats<< "\n"
    << "Price: " << flight.price << "\n";
    if(flight.fa_ptr != nullptr) {
        os << "Flight Attendant: " << *(flight.fa_ptr) << "\n";
    }
    if(flight.pl_ptr != nullptr) {
        os << "Pilot: " << *(flight.pl_ptr) << "\n";
    }
    os << "Status: " << flight.status << "\n";
    return os;
}
std::istream &operator>>(std::istream &is, Flight &flight)
{
    is.ignore();//to free the buffer
    std::cout<<"Enter Flight Number: ";
    std::getline(is, flight.flightNumber);
    std::cout<<"Enter Origin: ";
    std::getline(is, flight.origin);
    std::cout<<"Enter Destination: ";
    std::getline(is, flight.destination);
    std::cout<<"Enter Departure Date and Time (YYYY-MM-DD HH:MM): ";
    flight.deptTime = std::make_shared<Date>();
    is>>*(flight.deptTime);
    std::cout<<"Enter Arrival Date and Time (YYYY-MM-DD HH:MM): ";
    flight.arrivalTime = std::make_shared<Date>();
    is>>*(flight.arrivalTime);
    std::cout<<"Enter Aircraft Type: ";
    std::getline(is, flight.aircraftType);
    std::cout<<"Enter Total Seats: ";
    flight.numOfAvailableSeats = IOStreamHelper::InputNumeric();
    std::cout<<"Enter Status (Scheduled/Delayed/Canceled): ";
    std::getline(is, flight.status);
    std::cout<<"Enter Flight Price: ";
    is>>flight.price;
}

