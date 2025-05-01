#ifndef _ADMINISTRATOR_HPP
#define _ADMINISTRATOR_HPP
#include "User.hpp"
#include <string>
class Administrator : public User{
    private:
    //pointer to manager type to use or own a manager pointer
    public:
    Administrator() = default;
    Administrator(const Administrator& other) = default;
    Administrator(Administrator&&other) = default;
    Administrator(std::string username, std::string password);
    void viewMainMenu() override;
};

#endif 