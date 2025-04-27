#ifndef _CONCRETE_USER_FACTORY_HPP
#define _CONCRETE_USER_FACTORY_HPP

#include "UserFactory.hpp"
class ConcreteUserFactory : public UserFactory {
    public:
    ConcreteUserFactory() = default;
    ConcreteUserFactory(const ConcreteUserFactory&other) =default;
    ConcreteUserFactory(ConcreteUserFactory&&other) =default;
    UserPtr create(UserRole role) override;
};

#endif
