#ifndef _FLIGHT_HPP
#define _FLIGHT_HPP
#include <string>
#include "../utils/Date.hpp"
#include "../utils/IOStreamHelper.hpp"

class Flight {
    private:
    std::string flightNumber;
    std::string origin;
    std::string destination;
    DatePtr deptTime;
    DatePtr arrivalTime;
    std::string aircraftType;
    int numOfSeats;
    int numOfAvailableSeats;
    std::string status;
    double price;
    friend std::ostream& operator<<(std::ostream& os, const Flight& flight);
    friend std::istream& operator>>(std::istream &is, Flight& flight);
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
    double getPrice() const;
    std::string getStatus() const;
    int getNumOfAvailableSeats() const;
    void setPrice(double price);
    void setNumOfAvailableSeats(int numOfAvailableSeats);
    void setFlightNumber(const std::string& flightNumber);
    void setOrigin(const std::string& origin);
    void setDestination(const std::string& destination);
    void setDeptTime(const DatePtr& deptTime);
    void setArrivalTime(const DatePtr& arrivalTime);
    void setAircraftType(const std::string& aircraftType);
    void setNumOfSeats(int numOfSeats);
    void setStatus(const std::string& status);
    bool operator == (const Flight& other);
};
std::ostream& operator<<(std::ostream& os, const Flight& flight);
std::istream& operator>>(std::istream &is, Flight& flight);
using FLightPtr = std::shared_ptr<Flight>;
#endif