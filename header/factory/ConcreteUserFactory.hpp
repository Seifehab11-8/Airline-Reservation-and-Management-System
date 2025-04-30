#ifndef _CONCRETE_USER_FACTORY_HPP
#define _CONCRETE_USER_FACTORY_HPP

#include "UserFactory.hpp"
#include <string>
class ConcreteUserFactory : public UserFactory {
    public:
    ConcreteUserFactory() = default;
    ConcreteUserFactory(const ConcreteUserFactory&other) =default;
    ConcreteUserFactory(ConcreteUserFactory&&other) =default;
    UserPtr create(LoginAction::UserRole role, std::string username, std::string password) override;
};

#endif
