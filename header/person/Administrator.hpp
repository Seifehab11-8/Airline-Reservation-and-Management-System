#ifndef _ADMINISTRATOR_HPP
#define _ADMINISTRATOR_HPP
#include "User.hpp"
#include <string>
#include <memory>   
class FlightManager;   
class UserManager;              
class Administrator : public User{
    private:
    std::shared_ptr<UserManager> userManagerPtr;
    std::shared_ptr<FlightManager> flightManagerPtr;
    friend std::ostream& operator<<(std::ostream& os, const Administrator& admin);
    public:
    Administrator();
    Administrator(const Administrator& other) = default;
    Administrator(Administrator&&other) = default;
    Administrator(std::string username, std::string password);
    void viewMainMenu() override;
    bool operator==(const Administrator& other) const;
};
std::ostream& operator<<(std::ostream& os, const Administrator& admin);
#endif 