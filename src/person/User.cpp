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

void User::setPassword(std::string password)
{
    this->password = password;
}

void User::setLoginStatus(bool state)
{
    loginStatus = state;
}

bool User::getLoginStatus() const
{
    return loginStatus;
}

std::string User::getUsername() const
{
    return username;
}

std::string User::getPassword() const
{
    return password;
}
