#include "../../header/person/Person.hpp"
#include <string>

void Person::setName(std::string name) 
{
    this->name = name;
}
void Person::setID(std::string id)
{
    this->id =id;
}

void Person::setRole(std::string role)
{
    this->role = role;
}

std::string Person::getName() const
{
    return name;
}

std::string Person::getID() const
{
    return id;
}

std::string Person::getRole() const
{
    return role;
}
