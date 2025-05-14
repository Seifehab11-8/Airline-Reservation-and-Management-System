#include "../../header/person/Passenger.hpp"
#include "../../header/utils/IOStreamHelper.hpp"
#include "../../header/payment/IPayment.hpp"
#include "../../header/utils/Constants.hpp"
#include "../../header/utils/JSONFileManager.hpp"
#include "../../header/flight/Flight.hpp"
#include "../../header/flight/Reservation.hpp"
#include "../../header/manager/BookingManager.hpp"
#include <string>
#include <iostream>

Passenger::Passenger(): User() {}
Passenger::Passenger(std::string username, std::string password): User(username, password) {}

void Passenger::viewMainMenu() {
    int choice;
    do{
        std::cout<<"--- Passenger Menu ---\n"
                    "1. Search Flights\n"
                    "2. View My Reservations\n"
                    "3. Check-In\n"
                    "4. Logout\n"
                    "Enter choice: \n";
        choice = IOStreamHelper::InputNumeric();
        PassengerAction::PassengerMenuOption bamo = static_cast<PassengerAction::PassengerMenuOption>(choice);
        switch(bamo) {
            case PassengerAction::PassengerMenuOption::SEARCH_FLIGHTS:
                searchFlight();
                break;
            case PassengerAction::PassengerMenuOption::VIEW_RESERVATIONS:
                viewMyReservation();
                break;
            case PassengerAction::PassengerMenuOption::CHECK_IN:
                checkIn();
                break;
            case PassengerAction::PassengerMenuOption::LOGOUT:
                std::cout<<"Logging out..."<<std::endl;
                break;
            default:
                std::cout<<"Invalid choice. Please try again."<<std::endl;
        }
    }while(choice != 4);
}
void Passenger::appendPreference(std::string pref)
{
    preference.emplace_back(pref);
}

void Passenger::appendFlight(std::string flight)
{
    flightHistory.emplace_back(flight);
}

void Passenger::appendNotification(std::string note)
{
    notifications.emplace_back(note);
}

void Passenger::setContact(std::string contact)
{
    this->contact = contact;
}

void Passenger::setPerference(std::vector<std::string> preference)
{
    this->preference = preference;
}

void Passenger::setFlightHistory(std::vector<std::string> flightHistory)
{
    this->flightHistory = flightHistory;
}

void Passenger::setNotifications(std::vector<std::string> notifications)
{
    this->notifications = notifications;
}

std::string Passenger::getContact() const
{
    return contact;
}

std::vector<std::string> Passenger::getPreference() const
{
    return preference;
}

std::vector<std::string> Passenger::getFlightHistory() const
{
    return flightHistory;
}

std::vector<std::string> Passenger::getNotifications() const
{
    return notifications;
}

double Passenger::getBalance() const
{
    return balance;
}
void Passenger::setBalance(double balance)
{
    this->balance = balance;
}

void Passenger::pay(std::shared_ptr<IPayment> payment, double amount)
{
    if (amount <= 0) {
        std::cout << "Invalid amount. Payment failed." << std::endl;
        return;
    }
    else if(balance - amount < 0) {
        std::cout << "Insufficient balance. Payment failed." << std::endl;
        return;
    }
    payment->pay(amount, balance);
}

void Passenger::searchFlight() {
    auto flightPtr = std::make_shared<JSONFileManager>(FLIGHT_FILE_PATH);
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

        std::cout<<"--- Available Flights ---"<<std::endl;
        for(const auto& it: flights) {
            if(it.getOrigin() != origin || it.getDestination() != destination || it.getDeptTime()->to_string() != date) {
                continue;
            }
            std::cout<<counter<<". \n"<<it<<std::endl;
            counter++;
        }
        std::cout<<"Enter the Flight Number you wish to book (or '0' to cancel): ";
        std::string flightNumber;
        std::cin.ignore();
        std::getline(std::cin, flightNumber);
        if(flightNumber == "0") {
            std::cout<<"Back to Menu."<<std::endl;
            return;
        }
        else {
            auto it = std::find_if(flights.begin(), flights.end(), [&flightNumber](const Flight& flight) {
                return flight.getFlightNumber() == flightNumber;
            });
            int flight_index = std::distance(flights.begin(), it);
            if(it != flights.end()) {
                auto bookingManager = std::make_shared<BookingManager>();   
                auto reservation = bookingManager->book(*this, *it);
                if(reservation == nullptr) {
                    std::cout<<"Booking failed."<<std::endl;
                    return;
                }
                flightPtr->update(flight_index, *it);
                std::cout<<"Flight booked successfully!"<<std::endl;
                std::cout<<"Reservation ID: R"<<reservation->getID()<<std::endl;
                std::cout<<"Flight: "<<it->getFlightNumber()<<" from"<<it->getOrigin()
                            <<" to "<<it->getDestination()<<"\n"
                            <<"Seat: "<<reservation->getSeatNumber()<<"\n"
                            <<"Total Cost: "<<reservation->getPricePaid()<<std::endl;
                std::cout<<"Payment Method: "<<reservation->getPaymentMethodType()<<std::endl;
            }
            else {
                std::cout<<"Flight not found."<<std::endl;
            }
        }
    }
}
void Passenger::viewMyReservation() {
    auto reservationPtr = std::make_shared<JSONFileManager>(RESERVATION_FILE_PATH);
    auto flightPtr = std::make_shared<JSONFileManager>(FLIGHT_FILE_PATH);
    auto flights = flightPtr->getArray<Flight>();
    auto reservations = reservationPtr->getArray<Reservation>();

    if(reservations.empty()) {
        std::cout<<"No reservations found."<<std::endl;
        return;
    }
    else {
        std::cout<<"--- My Reservations ---"<<std::endl;
        int counter = 1;
        for(const auto& it: reservations) {
            if(it.getPassengerID() == this->id) {
                auto flight = std::find_if(flights.begin(), flights.end(), [&it](const Flight& flight) {
                    return flight.getFlightNumber() == it.getFlightNumber();
                });
                if(flight != flights.end()) {
                    std::cout<<counter<<". \n"
                            <<"Reservation ID: R"<<it.getID()<<"\n"
                            <<"Flight: "<<it.getFlightNumber()<<" from "<<flight->getOrigin()
                            <<" to "<<flight->getDestination()<<"\n"
                            <<"Departure: "<<flight->getDeptTime()->to_string()<<"\n"
                            <<"Seat: "<<it.getSeatNumber()<<"\n"
                            <<"Status: "<<it.getStatus()<<"\n";
                }
            }
        }
    }
}

void Passenger::checkIn() {
    auto reservationPtr = std::make_shared<JSONFileManager>(RESERVATION_FILE_PATH);
    auto flightPtr = std::make_shared<JSONFileManager>(FLIGHT_FILE_PATH);
    auto flights = flightPtr->getArray<Flight>();
    auto reservations = reservationPtr->getArray<Reservation>();

    if(reservations.empty()) {
        std::cout<<"No reservations found."<<std::endl;
        return;
    }
    else {
        std::cout<<"--- Check-In ---"<<std::endl;
        std::cout<<"Enter Reservation ID: ";
        std::string id;
        std::cin.ignore();
        std::getline(std::cin, id);
        try{
            int reservation_id = std::stoi(id.substr(1, id.length()-1));
            auto it = std::find_if(reservations.begin(), reservations.end(), [&reservation_id](const Reservation& reservation) {
                return reservation.getID() == reservation_id;
            });
            if(it != reservations.end()) {
                if(it->getStatus() == "Confirmed") {
                    std::cout<<"Already Checked In."<<std::endl;
                    return;
                }
                else if(it->getStatus() == "Canceled") {
                    std::cout<<"Your Flight is Canceled. "<<std::endl;
                    return;
                }
                auto flight = std::find_if(flights.begin(), flights.end(), [&it](const Flight& flight) {
                    return flight.getFlightNumber() == it->getFlightNumber();
                });
                if(flight != flights.end()) {
                    std::cout<<"Check-In successful!\n"
                            <<"Boarding Pass: \n"
                            <<"---------------------------------\n"
                            <<"Flight: "<<it->getFlightNumber()<<"\n"
                            <<"Origin: "<<flight->getOrigin()<<"\n"
                            <<"Destination: "<<flight->getDestination()<<"\n"
                            <<"Departure: "<<flight->getDeptTime()->to_string()<<"\n"
                            <<"Seat: "<<it->getSeatNumber()<<"\n"
                            <<"Gate: "<< flight->getGateNumber()<<"\n"
                            <<"Boarding Time: ";
                    DatePtr boardingTime = std::make_shared<Date>();
                    
                    DatePtr deptTime = flight->getDeptTime();
                    if(deptTime) {
                        // Convert departure hour/min to total minutes
                        int totalDepartureMinutes = deptTime->getHour() * 60 + deptTime->getMin();
                        // Subtract 90 minutes
                        totalDepartureMinutes -= 90;

                        // Calculate new hour/min
                        int newHour = totalDepartureMinutes / 60;
                        int newMin = totalDepartureMinutes % 60;

                        // Set boarding time date to the same day as departure for simplicity
                        boardingTime->setDate(deptTime->getDay(), deptTime->getMonth(), deptTime->getYear());
                        boardingTime->setTime(newHour, newMin);

                        std::cout << boardingTime->to_string() << std::endl;
                    } else {
                        std::cout << "No departure time available.\n";
                    }
                    it->setStatus("Confirmed");
                    int res_index = std::distance(reservations.begin(), it);
                    reservationPtr->update(res_index, *it);
                    
                }
            }
            else {
                std::cout<<"Reservation not found."<<std::endl;
            }
        } catch (const std::invalid_argument&) {
            std::cout << "Invalid Reservation ID format." << std::endl;
        } catch (const std::out_of_range&) {
            std::cout << "Reservation ID out of range." << std::endl;
        }
    }
}
void Passenger::viewMyNotification() {
    if(notifications.empty()) {
        std::cout<<"Your notification box is empty"<<std::endl;
    }
    else {
        auto it = notifications.rbegin();
        while (it != notifications.rend()) {
            std::cout << *it << std::endl;
            ++it;
        }
    }
}

bool Passenger::operator==(const Passenger& other) const
{
    return (this->username == other.username);
}

std::ostream& operator<<(std::ostream& os, const Passenger& passenger)
{
    os << "Passenger username: " << passenger.username << "\n";
    os<< "Name: " << passenger.name << "\n";
    os << "ID: " << passenger.id << "\n";
    os << "Role: " << passenger.role << "\n";
    os << "Contact: " << passenger.contact << "\n";
    os << "Preferences: ";
    for (const auto& pref : passenger.preference) {
        os << pref << " ";
    }
    os << "\nFlight History: ";
    for (const auto& flight : passenger.flightHistory) {
        os << flight << " ";
    }
    os << "\nNotifications: ";
    for (const auto& note : passenger.notifications) {
        os << note << " ";
    }
    return os;
}