#include "../../header/person/Administrator.hpp"
#include "../../header/utils/Configs.hpp"
#include "../../header/utils/IOStreamHelper.hpp"
#include "../../header/manager/FlightManager.hpp"
#include "../../header/manager/UserManager.hpp"
#include "../../header/manager/AircraftManager.hpp"
#include <string>
#include <iostream>
Administrator::Administrator(std::string username, std::string password) : User(username, password)
                                                                        , flightManagerPtr(std::make_shared<FlightManager>())
                                                                        , userManagerPtr(std::make_shared<UserManager>()){}
Administrator::Administrator() : flightManagerPtr(std::make_shared<FlightManager>()) 
                                , userManagerPtr(std::make_shared<UserManager>()){}

void Administrator::viewMainMenu()
{
    int main_menu_choice, choice;
    do{
        std::cout<<"--- Administrator Menu ---\n"
                    "1. Manage Flights\n"
                    "2. Manage Aircraft\n"
                    "3. Manage Users\n"
                    "4. Generate Reports\n"
                    "5. Logout\n"
                    "Enter choice: ";
        main_menu_choice = IOStreamHelper::InputNumeric();
        AdminAction::AdminMenuOption amo = static_cast<AdminAction::AdminMenuOption>(main_menu_choice);
        std::shared_ptr<IManager> managerPtr; 
        switch(amo) {
            case AdminAction::AdminMenuOption::MANAGE_FLIGHTS:
                managerPtr = std::make_shared<FlightManager>();
                break;
            case AdminAction::AdminMenuOption::MANAGE_USERS:
                managerPtr = std::make_shared<UserManager>();
                break;
            case AdminAction::AdminMenuOption::MANAGE_AIRCRAFT:
                managerPtr = std::make_shared<AircraftManager>();
                break;
            case AdminAction::AdminMenuOption::GENERATE_REPORTS:
            //to be implemented
                break;
            case AdminAction::AdminMenuOption::LOGOUT:
                std::cout<<"logging out...\n";
                return;
        }
        if(managerPtr.get() != nullptr) {
            do{
                choice = managerPtr->viewMenu();
                switch(choice) {
                    case 1:
                        managerPtr->create();
                        break;
                    case 2:
                        managerPtr->update();
                        break;
                    case 3:
                        managerPtr->_delete();
                        break;
                    case 4:
                        managerPtr->view();
                        break;
                    case 5:
                        std::cout<<"Back to Main Menu\n";
                        break;
                    default:
                        std::cout<<"Invalid choice. Please try again.\n";
                }
            }while(choice != 5);
        }
    }while(main_menu_choice != 5);
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