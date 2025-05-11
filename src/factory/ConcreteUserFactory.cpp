#include "../../header/factory/ConcreteUserFactory.hpp"
#include "../../header/person/Administrator.hpp"
#include "../../header/person/BookingAgent.hpp"
#include "../../header/person/Passenger.hpp"
#include "../../header/utils/exceptions/Undefined_role_exception.hpp"
#include <iostream>

UserPtr ConcreteUserFactory::create(LoginAction::UserRole role, std::string username, std::string password)
{
    UserPtr u_ptr;
    switch(role) {
        case LoginAction::UserRole::ADMIN:
        u_ptr = std::make_shared<Administrator>(username, password);
        u_ptr->setRole("admin");
        break;
        case LoginAction::UserRole::PASSENGER:
        u_ptr = std::make_shared<Passenger>(username, password);
        u_ptr->setRole("passenger");
        break;
        case LoginAction::UserRole::BOOKING_AGENT:
        u_ptr = std::make_shared<BookingAgent>(username, password);
        u_ptr->setRole("booking agent");
        break;
        default:
        throw Undefined_role_exception("This role doesn't exist");
    }
    if(role == LoginAction::UserRole::ADMIN ||
       role == LoginAction::UserRole::PASSENGER ||
       role == LoginAction::UserRole::BOOKING_AGENT) {
        u_ptr->setLoginStatus(false);
        std::cout<<"Enter Name: ";
        std::string name;
        std::cin.ignore();
        std::getline(std::cin, name);
        u_ptr->setName(name);
        std::cout<<"Enter ID: ";
        std::string id;
        std::getline(std::cin, id);
        u_ptr->setID(id);
    }
    return std::move(u_ptr);
}