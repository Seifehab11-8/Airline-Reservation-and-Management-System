#include "../../header/flight/Reservation.hpp"
#include "../../header/payment/IPayment.hpp"

std::string Reservation::getFlightNumber() const {
    return flightNumber;
}
std::string Reservation::getPassengerID() const {
    return passengerID;
}
std::string Reservation::getSeatNumber() const {
    return seatNumber;
}
int Reservation::getID() const {
    return id;
}
void Reservation::setFlightNumber(const std::string& flightNumber) {
    this->flightNumber = flightNumber;
}
void Reservation::setPassengerID(const std::string& passengerID) {
    this->passengerID = passengerID;
}
void Reservation::setSeatNumber(const std::string& seatNumber) {
    this->seatNumber = seatNumber;
}
void Reservation::setID(int id) {
    this->id = id;
}
void Reservation::setStatus(const std::string& status) {
    this->status = status;
}
std::string Reservation::getStatus() const {
    return status;
}
std::shared_ptr<IPayment> Reservation::getPaymentMethod() const {
    return paymentMethod;
}
void Reservation::setPaymentMethod(std::shared_ptr<IPayment> paymentMethod) {
    this->paymentMethod = paymentMethod;
}
std::string Reservation::getPaymentMethodType() const {
    return paymentMethodType;
}
void Reservation::setPaymentMethodType(const std::string& type) {
    this->paymentMethodType = type;
}
double Reservation::getPricePaid() const {
    return pricePaid;
}

void Reservation::setPricePaid(double price) {
    this->pricePaid = price;
}

bool Reservation::operator==(const Reservation&other) const {
    return (this->id == other.id);
}