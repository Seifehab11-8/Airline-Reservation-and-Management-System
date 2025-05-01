#ifndef _USER_FACTORY_HPP
#define _USER_FACTORY_HPP


#include <memory>
#include "../person/Passenger.hpp"
#include "../utils/Configs.hpp"
#include <string>

using UserPtr = std::shared_ptr<User>;
class UserFactory {
    protected:
    UserPtr u_ptr;
    public:
    UserFactory() = default;
    UserFactory(const UserFactory&other) = default;
    UserFactory(UserFactory &&other) = default;
    virtual UserPtr create(LoginAction::UserRole role, std::string username, std::string password) = 0;
    virtual ~UserFactory() = default;
};

#endif
