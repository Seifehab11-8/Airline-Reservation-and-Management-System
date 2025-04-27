#ifndef _ADMINISTRATOR_HPP
#define _ADMINISTRATOR_HPP
#include "User.hpp"

class Administrator : public User{
    public:
    Administrator() = delete;
    Administrator(const Administrator& other) = default;
    Administrator(Administrator&&other) = default;
    Administrator(std::string username, std::string password);
    MainMenuOption viewMainMenu();
};

#endif 