#include "../../header/person/BookingAgent.hpp"
#include "../../header/utils/Configs.hpp"
#include "../../header/utils/IOStreamHelper.hpp"
#include <string>
#include <iostream>
BookingAgent::BookingAgent(std::string username, std::string password):User(username, password) {}
void BookingAgent::viewMainMenu() {
    int choice;
    std::cout<<"--- Booking Agent Menu ---\n"
                "1. Search Flights\n"
                "2. Book a Flight\n"
                "3. Modify Reservation\n"
                "4. Cancel Reservation\n"
                "5. Logout\n"
                "Enter choice:"; 
    choice = IOStreamHelper::InputNumeric();
    BookingAgentAction::BookingAgentMenuOption bamo = static_cast<BookingAgentAction::BookingAgentMenuOption>(choice);
    /*
    TODO: contiue to managers
    */
}