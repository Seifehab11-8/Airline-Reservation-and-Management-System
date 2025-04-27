#include "../../header/factory/ConcreteUserFactory.hpp"
#include "../../header/person/Administrator.hpp"
#include "../../header/person/BookingAgent.hpp"
#include "../../header/person/Passenger.hpp"

#include "../../header/utils/exceptions/Undefined_role_exception.hpp"

UserPtr ConcreteUserFactory::create(UserRole role) {
    switch(role) {
        case ADMIN:
            return std::make_shared<Administrator>();
            break;
        case PASSENGER:
            return std::make_shared<Passenger>();
            break;
        case BOOKING_AGENT:
            return std::make_shared<BookingAgent>();
            break;
        default:
            throw Undefined_role_exception("This role doesn't exist");
    }
}
