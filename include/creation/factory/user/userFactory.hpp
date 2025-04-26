#ifndef _USER_FACTORY_HPP
#define _USER_FACTORY_HPP

#include "../../person/user/Administrator.hpp"
#include "../../person/user/BookingAgent.hpp"
#include "../../person/user/Passenger.hpp"
#include "../../utils/Configs.hpp"
#include <memory>

using UserPtr = std::shared_ptr<User>;
class UserFactory {
    public:
    virtual UserPtr create(OptionSelect option) = 0;
    virtual ~UserFactory() = default;
};

#endif