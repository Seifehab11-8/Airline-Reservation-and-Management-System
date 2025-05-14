#ifndef FLIGHT_RESERVATION_HPP
#define FLIGHT_RESERVATION_HPP
#include <iostream>
#include <string>
#include <memory>
class IPayment;
class Reservation {
    private:
    std::string flightNumber; 
    std::string passengerID; 
    std::string seatNumber;
    int id;
    std::string status = "Pending";
    std::shared_ptr<IPayment> paymentMethod = nullptr;
    std::string paymentMethodType;
    double pricePaid = 0.0;
public:
    Reservation() = default;
    Reservation(const Reservation& other) = default;
    Reservation& operator=(const Reservation& other) = default;
    Reservation(Reservation&& other) = default;
    Reservation& operator=(Reservation&& other) = default;
    ~Reservation() = default;

    std::string getFlightNumber() const;
    std::string getPassengerID() const;
    std::string getSeatNumber() const;
    int getID() const;
    std::string getStatus() const;
    std::string getPaymentMethodType() const;
    std::shared_ptr<IPayment> getPaymentMethod() const;
    double getPricePaid() const;
    void setPricePaid(double price);
    void setPaymentMethod(std::shared_ptr<IPayment> paymentMethod);
    void setFlightNumber(const std::string& flightNumber);
    void setPassengerID(const std::string& passengerID);
    void setSeatNumber(const std::string& seatNumber);
    void setID(int id);
    void setStatus(const std::string& status);
    void setPaymentMethodType(const std::string& type);
    bool operator == (const Reservation &other) const;
};
#endif // FLIGHT_RESERVATION_HPP