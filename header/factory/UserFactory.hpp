#ifndef _USER_FACTORY_HPP
#define _USER_FACTORY_HPP


#include <memory>
#include "../person/Passenger.hpp"
#include "../utils/Configs.hpp"

using UserPtr = std::shared_ptr<User>;
class UserFactory {
    public:
    UserFactory() = default;
    virtual UserPtr create(OptionSelect option) = 0;
    virtual ~UserFactory() = default;
};

#endif
