#include "../header/APP.hpp"
#include "../header/person/User.hpp"
#include "../header/factory/ConcreteUserFactory.hpp"
#include <iostream>
#include "../header/utils/IOStreamHelper.hpp"
#include "../header/utils/Configs.hpp"
#include "../header/utils/exceptions/Undefined_role_exception.hpp"

using CreatorPtr = std::shared_ptr<ConcreteUserFactory>;

void APP::start() 
{
    CreatorPtr c_ptr = std::make_shared<ConcreteUserFactory>();
    int choice;
    std::string username, password;
    std::cout<<"Welcome to Airline Reservation and Management System\n"
            "Please select your role\n"
            "1. Administrator\n"
            "2. Booking Agent\n"
            "3. Passenger\n"
            "Enter choice: ";
    choice = IOStreamHelper::InputNumeric();
    LoginAction::UserRole ur = static_cast<LoginAction::UserRole>(choice);

    std::cin.ignore();//to free the buffer
    std::cout<<"---- Login ----"<<std::endl;
    std::cout<<"Username : ";
    std::getline(std::cin, username);
    std::cout<<"Password : ";
    std::getline(std::cin, password);
    try{
        UserPtr u_ptr = c_ptr->create(ur, username, password);
        u_ptr->viewMainMenu();
    }
    catch(const Undefined_role_exception& e) {
        std::cerr<<e.what();
    }
}