#include "../../header/person/Passenger.hpp"
#include "../../header/utils/IOStreamHelper.hpp"
#include <string>
#include <iostream>

Passenger::Passenger(std::string username, std::string password): User(username, password){}
void Passenger::viewMainMenu() {
    int choice;
    std::cout<<"--- Passenger Menu ---\n"
                "1. Search Flights\n"
                "2. View My Reservations\n"
                "3. Check-In\n"
                "4. Logout\n"
                "Enter choice: \n";
    choice = IOStreamHelper::InputNumeric();
    PassengerAction::PassengerMenuOption bamo = static_cast<PassengerAction::PassengerMenuOption>(choice);
    /*
    TODO: contiue to managers
    */
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
