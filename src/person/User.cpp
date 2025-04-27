#include "../../header/person/User.hpp"
#include <string>

User::User(std::string username, std::string password) : username(username), password(password) {}
void User::setUsername(std::string username)
{
    this->username = username;
}

bool User::setPassword(std::string password, std::string oldPassword)
{
    if(oldPassword == this->password) {
        this->password = password;
        return true;
    }
    return false;
}

std::string User::getUsername() const
{
    return username;
}

std::string User::getPassword() const
{
    return password;
}
