#include "../../header/manager/BookingManager.hpp"
#include "../../header/person/Passenger.hpp"
#include "../../header/flight/Flight.hpp"
#include "../../header/flight/Reservation.hpp"
#include "../../header/utils/IOStreamHelper.hpp"
#include "../../header/payment/Cash.hpp"
#include "../../header/payment/CreditCard.hpp"
#include "../../header/payment/Paypal.hpp"

std::shared_ptr<Reservation> BookingManager::book(Passenger& passenger, Flight& flight) {
    auto reservation = std::make_shared<Reservation>();
    std::cout<<"Enter Seat Number (e.g., 12A): ";
    std::string seatNumber;
    std::cin.ignore();
    std::getline(std::cin, seatNumber);
    reservation->setFlightNumber(flight.getFlightNumber());
    reservation->setPassengerUsername(passenger.getUsername());
    //checks for seat number
    // 1. the seat number is correct
    // 2. the seat number is not already booked
    try {
        int seatNum = std::stoi(seatNumber.substr(0,2));
        char seatLetter = seatNumber[2];
        if(seatNum < 1 || seatNum > (flight.getNumOfSeats()/NUM_OF_SEATS_PER_ROW)) {
            throw std::out_of_range("Seat number out of range");
        }
        if(seatLetter < 'A' || seatLetter > 'F') {
            throw std::out_of_range("Seat letter out of range");
        }
        // Check if the seat is already booked
        auto reservations = reservationPtr->getArray<Reservation>();
        bool seatBooked = false;
        int lastResId = 0;
        for (const auto& res : reservations) {
            if (res.getFlightNumber() == flight.getFlightNumber() 
                && res.getSeatNumber() == seatNumber
                && res.getStatus() != "Canceled") {
                seatBooked = true;
                break;
            }
            lastResId = std::max(lastResId, res.getID());
        }
        if(seatBooked) {
            throw std::runtime_error("Seat is already booked.");
        }
        reservation->setSeatNumber(seatNumber);
        reservation->setID(++lastResId);
        reservation->setPricePaid(flight.getPrice());
        //payment
        std::cout<<"Enter Payment Method (Credit Card/Cash/PayPal): ";
        std::string paymentMethod;
        std::getline(std::cin, paymentMethod);
        if(paymentMethod == "Credit Card") {
            std::shared_ptr<IPayment> payment = std::make_shared<CreditCard>();
            double amount = flight.getPrice();
            passenger.pay(payment, amount);
            reservation->setPaymentMethod(payment);
            reservation->setPaymentMethodType("CreditCard");
        }
        else if(paymentMethod == "Cash") {
            std::shared_ptr<IPayment> payment = std::make_shared<Cash>();
            double amount = flight.getPrice();
            passenger.pay(payment, amount);
            reservation->setPaymentMethodType("Cash");
        }
        else if(paymentMethod == "PayPal") {
            std::shared_ptr<IPayment> payment = std::make_shared<Paypal>();
            double amount = flight.getPrice();
            passenger.pay(payment, amount);
            reservation->setPaymentMethodType("Paypal");
            reservation->setPaymentMethod(payment);
        }
        else {
            throw std::invalid_argument("Invalid payment method.");
        }
        std::cout << "Payment of $" << flight.getPrice() << " made. Remaining balance: $" << passenger.getBalance() << std::endl<<std::endl;
        reservationPtr->append(*reservation);
        passenger.appendFlight(flight.getFlightNumber());
        auto passengers = passengerPtr->getArray<Passenger>();
        int passengerIndex = std::distance(passengers.begin(), 
            std::find_if(passengers.begin(), passengers.end(), 
            [&passenger](const Passenger& p) { return p.getUsername() == passenger.getUsername(); }));
        if (passengerIndex >= passengerPtr->getArray<Passenger>().size()) {
            throw std::runtime_error("Passenger not found.");
        }
        passengerPtr->update(passengerIndex, passenger);
    }
    catch(const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        return nullptr;
    }
    catch(const std::out_of_range& e) {
        std::cout << e.what() << std::endl;
        return nullptr;
    }
    catch(const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
        return nullptr;
    }
    catch(const std::exception& e) {
        std::cout << "An error occurred: " << e.what() << std::endl;
        return nullptr;
    }
    flight.setNumOfAvailableSeats(flight.getNumOfAvailableSeats() - 1);
    return reservation;
}

Json_file_ptr BookingManager::getFlightPtr() const {
    return flightPtr;
}

Json_file_ptr BookingManager::getReservationPtr() const {
    return reservationPtr;
}

Json_file_ptr BookingManager::getPassengerPtr() const {
    return passengerPtr;
}