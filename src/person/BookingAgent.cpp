#include "../../header/person/BookingAgent.hpp"
#include "../../header/utils/Configs.hpp"
#include "../../header/utils/IOStreamHelper.hpp"
#include "../../header/manager/BookingManager.hpp"
#include "../../header/person/Passenger.hpp"
#include "../../header/flight/Flight.hpp"
#include "../../header/flight/Reservation.hpp"
#include "../../header/payment/IPayment.hpp"
#include "../../header/payment/CreditCard.hpp"
#include "../../header/payment/Paypal.hpp"
#include "../../header/payment/Cash.hpp"
#include <string>
#include <iostream>
#include <stdexcept>
BookingAgent::BookingAgent():User(), bookingManager(std::make_shared<BookingManager>()) {}
BookingAgent::BookingAgent(std::string username, std::string password):User(username, password), bookingManager(std::make_shared<BookingManager>()) {}
void BookingAgent::viewMainMenu() {
    int choice;
    do{
        std::cout<<"--- Booking Agent Menu ---\n"
                    "1. Search Flights\n"
                    "2. Book a Flight\n"
                    "3. Modify Reservation\n"
                    "4. Cancel Reservation\n"
                    "5. Logout\n"
                    "Enter choice: "; 
        choice = IOStreamHelper::InputNumeric();
        BookingAgentAction::BookingAgentMenuOption bamo = static_cast<BookingAgentAction::BookingAgentMenuOption>(choice);
        switch (bamo) {
            case BookingAgentAction::BookingAgentMenuOption::SEARCH_FLIGHTS:
                searchFlight();
                break;
            case BookingAgentAction::BookingAgentMenuOption::BOOK_TICKET:
                bookFlight();
                break;
            case BookingAgentAction::BookingAgentMenuOption::MODIFY_RESERVATION:
                modifyFlight();
                break;
            case BookingAgentAction::BookingAgentMenuOption::CANCEL_RESERVATION:
                try{
                    cancelFlight();
                }
                catch(const std::exception &e) {
                    std::cerr<<e.what()<<std::endl;
                }
                break;
            case BookingAgentAction::BookingAgentMenuOption::LOGOUT:
                std::cout << "Logging out...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    }while(choice != 5);

}

bool BookingAgent::operator==(const BookingAgent& other) const
{
    return (this->username == other.username);
}

void BookingAgent::searchFlight()
{
    auto flightPtr = bookingManager->getFlightPtr();
    auto flights = flightPtr->getArray<Flight>();
    std::cout<<"--- Search Flights ---"<<std::endl;
    if(flights.empty()) {
        std::cout<<"No flights available."<<std::endl;
        return;
    }
    else {
        int counter = 1;
        // Enter Origin: Chicago (ORD)
        // Enter Destination: Miami (MIA)
        // Enter Departure Date (YYYY-MM-DD): 2023-12-20
        std::string origin, destination, date;
        std::cout<<"Enter Origin: ";
        std::cin.ignore();
        std::getline(std::cin, origin);
        std::cout<<"Enter Destination: ";
        std::getline(std::cin, destination);
        std::cout<<"Enter Departure Date (YYYY-MM-DD): ";
        std::getline(std::cin, date);

        if(flights.empty()) {
            std::cout<<"No flights found for the given criteria."<<std::endl;
            return;
        }
        DatePtr datePtr = Date::processDateFormat(date);
        std::cout<<"--- Available Flights ---"<<std::endl;
        for(const auto& it: flights) {
            if(it.getOrigin() != origin || it.getDestination() != destination 
            || it.getDeptTime()->getDay() != datePtr->getDay()
            || it.getDeptTime()->getMonth() != datePtr->getMonth()
            || it.getDeptTime()->getYear() != datePtr->getYear()) {
                continue;
            }
            std::cout<<counter<<". \n"<<it<<std::endl;
            counter++;
        }
    }
}
void BookingAgent::bookFlight()
{
    std::cout << "--- Booking a flight ---\n";
    std::string passengerId;
    std::cout << "Enter passenger Username: ";
    std::cin >> passengerId;

    std::string flightNumber;
    std::cout << "Enter flight number: ";
    std::cin >> flightNumber;

    auto flightPtr = bookingManager->getFlightPtr();
    auto reservationPtr = bookingManager->getReservationPtr();
    auto passengerPtr = bookingManager->getPassengerPtr();
    auto flights = flightPtr->getArray<Flight>();
    auto passengers = passengerPtr->getArray<Passenger>();
    auto passengerIt = std::find_if(passengers.begin(), passengers.end(), [&](const Passenger& p) {
        return p.getUsername() == passengerId;
    });
    if (passengerIt == passengers.end()) {
        std::cout << "Passenger not found.\n";
        return;
    }
    auto flightIt = std::find_if(flights.begin(), flights.end(), [&](const Flight& f) {
        return f.getFlightNumber() == flightNumber;
    });
    if (flightIt == flights.end()) {
        std::cout << "Flight not found.\n";
        return;
    }
    auto reservation = bookingManager->book(*passengerIt, *flightIt);
    if(reservation == nullptr) {
        std::cout << "Booking failed.\n";
        return;
    }
    flightIt->setNumOfAvailableSeats(flightIt->getNumOfAvailableSeats() - 1);
    flightPtr->update(std::distance(flights.begin(), flightIt), *flightIt);
    std::cout << "\n\nFlight booked successfully!\n";
    std::cout << "Reservation ID: R" << reservation->getID() << "\n";
    std::cout << "Passenger :" << passengerIt->getName() << "\n";
    std::cout << "Flight: " << flightIt->getFlightNumber() << " from " << flightIt->getOrigin()
              << " to " << flightIt->getDestination() << "\n"
              << "Seat: " << reservation->getSeatNumber() << "\n"
              << "Total Cost: " << reservation->getPricePaid() << "\n";
    std::cout << "Payment Method: " << reservation->getPaymentMethodType() << "\n\n";
}
void BookingAgent::cancelFlight()
{
    std::cout << "--- Canceling Reservation ---\n";
    std::string reservationId;
    std::cout << "Enter Reservation ID: ";
    std::cin >> reservationId;
    auto reservationPtr = bookingManager->getReservationPtr();
    auto reservations = reservationPtr->getArray<Reservation>();
    auto reservation = reservations.end();
    for (auto it = reservations.begin(); it != reservations.end(); ++it) {
        if ("R" + std::to_string(it->getID()) == reservationId) {
            reservation = it;
            break;
        }
    }
    if (reservation == reservations.end()) {
        std::cout << "Reservation not found.\n";
        return;
    }
    std::cout<<"Are you sure you want to cancel Reservation ID R321? (yes/no): ";
    std::string confirmation;
    std::cin >> confirmation;
    if (confirmation != "yes") {
        std::cout << "Reservation cancellation aborted.\n";
        return;
    }
    std::cout << "Processing refund to ";
    if(auto payment = std::dynamic_pointer_cast<CreditCard>(reservation->getPaymentMethod())) {
        std::cout << "Credit Card number: "<< payment->getCardNumber() << "\n\n";
        std::cout << "Reservation R"<< reservation->getID() << "has been successfully canceled.\n";
        std::cout << "Refunding amount: $" << reservation->getPricePaid() << " to your credit card."<< "\n\n";
    } else if(auto payment = std::dynamic_pointer_cast<Cash>(reservation->getPaymentMethod())) {
        std::cout << "Cash\n\n";
        std::cout << "Reservation R"<< reservation->getID() << "has been successfully canceled.\n";
        std::cout << "Refunding amount: $" << reservation->getPricePaid() << " in cash."<< "\n\n";
    } else if(auto payment = std::dynamic_pointer_cast<Paypal>(reservation->getPaymentMethod())) {
        std::cout << "PayPal account: " << payment->getEmail() << "\n\n";
        std::cout << "Reservation R"<< reservation->getID() << " has been successfully canceled.\n";
        std::cout << "Refunding amount: $" << reservation->getPricePaid() << " to your PayPal account."<< "\n\n";
    }
    reservation->setStatus("Canceled");
    reservationPtr->update(std::distance(reservationPtr->getArray<Reservation>().begin(), reservation), *reservation);
    auto flightPtr = bookingManager->getFlightPtr();
    auto flights = flightPtr->getArray<Flight>();
    auto flightIt = std::find_if(flights.begin(), flights.end(), [&](const Flight& f) {
        return f.getFlightNumber() == reservation->getFlightNumber();
    });
    if (flightIt != flights.end()) {
        flightIt->setNumOfAvailableSeats(flightIt->getNumOfAvailableSeats() + 1);
        flightPtr->update(std::distance(flights.begin(), flightIt), *flightIt);
    }
    auto passengerPtr = bookingManager->getPassengerPtr();
    auto passengers = passengerPtr->getArray<Passenger>();
    auto passengerIt = std::find_if(passengers.begin(), passengers.end(), [&](const Passenger& p) {
        return p.getUsername() == reservation->getPassengerUsername();
    });
    if (passengerIt != passengers.end()) {
        passengerIt->appendNotification("Your Reservation for flight "+ flightIt->getFlightNumber() + " has been Canceled");
        passengerIt->setBalance(passengerIt->getBalance() + reservation->getPricePaid());
        passengerPtr->update(std::distance(passengers.begin(), passengerIt), *passengerIt);
    }
}
void BookingAgent::modifyFlight()
{
    std::cout << "--- Modifying Reservation ---\n";
    std::string reservationId;
    std::cout << "Enter Reservation ID: ";
    std::cin >> reservationId;
    auto reservationPtr = bookingManager->getReservationPtr();
    auto reservations = reservationPtr->getArray<Reservation>();
    auto reservation = reservations.end();
    for (auto it = reservations.begin(); it != reservations.end(); ++it) {
        if ("R" + std::to_string(it->getID()) == reservationId) {
            reservation = it;
            break;
        }
    }
    if (reservation >= reservations.end()) {
        std::cout << "Reservation not found.\n";
        return;
    }
    std::cout << "1. Change Seat\n"
              << "2. Cancel Update\n"
              << "Enter your choice: ";
    int choice;
    std::cin >> choice;
    switch (choice) {
        case 1:
            {
                std::string newSeatNumber;
                std::cout << "Enter new seat number: ";
                std::cin >> newSeatNumber;
                int seatNum = std::stoi(newSeatNumber.substr(0,2));
                char seatLetter = newSeatNumber[2];
                auto flightPtr = bookingManager->getFlightPtr();
                auto flights = flightPtr->getArray<Flight>();
                auto flight = std::find_if(flights.begin(), flights.end(), [&](const Flight& f) {
                    return f.getFlightNumber() == reservation->getFlightNumber();
                });
                if(seatNum < 1 || seatNum > (flight->getNumOfSeats()/NUM_OF_SEATS_PER_ROW)) {
                    throw std::out_of_range("Seat number out of range");
                }
                if(seatLetter < 'A' || seatLetter > 'F') {
                    throw std::out_of_range("Seat letter out of range");
                }
                reservation->setSeatNumber(newSeatNumber);
                reservation->setStatus("Pending");
                reservationPtr->update(std::distance(reservations.begin(), reservation), *reservation);
                std::cout << "Reservation updated successfully!\n";
                std::cout << "New Seat Number: " << reservation->getSeatNumber() << "\n";
            }
            break;
        case 2:
            std::cout << "Update canceled.\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
    }
}

std::ostream& operator<<(std::ostream& os, const BookingAgent& bookingAgent)
{
    os << "Booking Agent: " << bookingAgent.username << "\n";
    os << "Name: " << bookingAgent.name << "\n";
    os << "ID: " << bookingAgent.id << "\n";
    os << "Role: " << bookingAgent.role << "\n";
    return os;
}