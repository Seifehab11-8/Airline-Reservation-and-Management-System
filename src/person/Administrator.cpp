#include "../../header/person/Administrator.hpp"
#include "../../header/utils/Configs.hpp"
#include "../../header/utils/IOStreamHelper.hpp"
#include "../../header/manager/FlightManager.hpp"
#include "../../header/manager/UserManager.hpp"
#include <string>
#include <iostream>
Administrator::Administrator(std::string username, std::string password) : User(username, password)
                                                                        , flightManagerPtr(std::make_shared<FlightManager>())
                                                                        , userManagerPtr(std::make_shared<UserManager>()){}
Administrator::Administrator() : flightManagerPtr(std::make_shared<FlightManager>()) 
                                , userManagerPtr(std::make_shared<UserManager>()){}

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
        case AdminAction::AdminMenuOption::MANAGE_USERS:
            {
                userManagerPtr = std::make_shared<UserManager>();
                do {
                    choice = viewManageUserMenu();
                    switch(choice) {
                        case 1:
                            userManagerPtr->create();
                            break;
                        case 2:
                            userManagerPtr->update();
                            break;
                        case 3:
                            userManagerPtr->_delete();
                            break;
                        case 4:
                            userManagerPtr->view();
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

int Administrator::viewManageUserMenu()
{
    int choice;
    std::cout<<"--- Manage Users ---\n"
                "1. Add User\n"
                "2. Update User\n"
                "3. Delete User\n"
                "4. View Users\n"
                "5. Back to Main Menu\n"
                "Enter choice: ";
    choice = IOStreamHelper::InputNumeric();
    return choice;
}

bool Administrator::operator==(const Administrator& other) const
{
    return (this->username == other.username);
}

std::ostream& operator<<(std::ostream& os, const Administrator& admin)
{
    os << "Administrator: " << admin.username << "\n";
    os << "Name: " << admin.name << "\n";
    os << "ID: " << admin.id << "\n";
    os << "Role: " << admin.role << "\n";
    return os;
}