#include "../../header/factory/ConcreteUserFactory.hpp"
#include "../../header/person/Administrator.hpp"
#include "../../header/person/BookingAgent.hpp"
#include "../../header/person/Passenger.hpp"
#include "../../header/utils/exceptions/Undefined_role_exception.hpp"

UserPtr ConcreteUserFactory::create(LoginAction::UserRole role, std::string username, std::string password)
{
    switch(role) {
        case LoginAction::UserRole::ADMIN:
            return std::make_shared<Administrator>(username, password);
            break;
        case LoginAction::UserRole::PASSENGER:
            return std::make_shared<Passenger>(username, password);
            break;
        case LoginAction::UserRole::BOOKING_AGENT:
            return std::make_shared<BookingAgent>(username, password);
            break;
        default:
            throw Undefined_role_exception("This role doesn't exist");
    }
}