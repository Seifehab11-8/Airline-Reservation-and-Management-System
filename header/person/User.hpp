#ifndef _USER_HPP
#define _USER_HPP
#include "Person.hpp"
#include "../utils/Configs.hpp"
#include <string>
class User : public Person{
    protected:
    std::string username;
    std::string password;
    bool loginStatus;
    public:
    User() = delete;
    User(const User&other) = default;
    User(User&&other) =default;
    User(std::string username, std::string password);
    void setUsername(std::string username);
    bool setPassword(std::string password, std::string oldPassword);
    std::string getUsername() const;
    std::string getPassword() const;
    virtual void viewMainMenu() = 0;
};
#endif