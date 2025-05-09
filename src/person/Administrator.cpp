#include "../../header/person/Administrator.hpp"
#include "../../header/utils/Configs.hpp"
#include "../../header/utils/IOStreamHelper.hpp"
#include "../../header/manager/FlightManager.hpp"
#include <string>
#include <iostream>
Administrator::Administrator(std::string username, std::string password) : User(username, password), flightManagerPtr(std::make_shared<FlightManager>()) {}
Administrator::Administrator() : flightManagerPtr(std::make_shared<FlightManager>()) {}

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
    switch(amo) {
        case AdminAction::AdminMenuOption::MANAGE_FLIGHTS:
            {
                do {
                    choice = viewManageFlightMenu();
                    switch(choice) {
                        case 1:
                            flightManagerPtr->create();
                            break;
                        case 2:
                            flightManagerPtr->update();
                            break;
                        case 3:
                            flightManagerPtr->_delete();
                            break;
                        case 4:
                            flightManagerPtr->view();
                            break;
                        case 5:
                            std::cout<<"Returning to Main Menu...\n";
                            break;
                        default:
                            std::cout<<"Invalid choice. Please try again.\n";
                    }
                } while (choice != 5);
            }
            break;
    }
}
int Administrator::viewManageFlightMenu()
{
    int choice;
    std::cout<<"--- Manage Flights ---\n"
                "1. Add Flight\n"
                "2. Update Flight\n"
                "3. Delete Flight\n"
                "4. View Flights\n"
                "5. Back to Main Menu\n"
                "Enter choice: ";
    choice = IOStreamHelper::InputNumeric();
    return choice;
}