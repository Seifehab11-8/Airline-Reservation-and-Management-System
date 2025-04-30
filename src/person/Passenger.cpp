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