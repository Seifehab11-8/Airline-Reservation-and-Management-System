#include "../../header/person/Administrator.hpp"
#include "../../header/utils/Configs.hpp"
#include "../../header/utils/IOStreamHelper.hpp"
#include <string>
#include <iostream>
Administrator::Administrator(std::string username, std::string password) : User(username, password) {}
void Administrator::viewMainMenu()
{
    int choice;
    std::cout<<"--- Administrator Menu ---\n"
                "1. Manage Flights\n"
                "2. Manage Aircraft\n"
                "3. Manage Users\n"
                "4. Generate Reports\n"
                "5. Logout\n"
                "Enter choice: ";
    choice = IOStreamHelper::InputNumeric();
    AdminAction::AdminMenuOption amo = static_cast<AdminAction::AdminMenuOption>(choice);
    /*
    TODO: manager managment
    */
}