#ifndef _FLIGHT_HPP
#define _FLIGHT_HPP
#include <string>
#include "../utils/Date.hpp"
class Flight {
    private:
    std::string flightNumber;
    std::string origin;
    std::string destination;
    DatePtr deptTime;
    DatePtr arrivalTime;
    std::string aircraftType;
    int numOfSeats;
    std::string status;
    public:
    Flight() = default;
    Flight(const Flight& other) = default;
    Flight(Flight &&other) = default;
    std::string getFlightNumber() const;
    std::string getOrigin() const;
    std::string getDestination() const;
    DatePtr getDeptTime() const;
    DatePtr getArrivalTime() const;
    std::string getAircraftType() const;
    int getNumOfSeats() const;
    std::string getStatus() const;
    void setFlightNumber(const std::string& flightNumber);
    void setOrigin(const std::string& origin);
    void setDestination(const std::string& destination);
    void setDeptTime(const DatePtr& deptTime);
    void setArrivalTime(const DatePtr& arrivalTime);
    void setAircraftType(const std::string& aircraftType);
    void setNumOfSeats(int numOfSeats);
    void setStatus(const std::string& status);
};
std::ostream& operator<<(std::ostream& os, const Flight& flight);
#endif