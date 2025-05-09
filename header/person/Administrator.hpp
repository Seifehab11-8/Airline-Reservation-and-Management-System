#ifndef _ADMINISTRATOR_HPP
#define _ADMINISTRATOR_HPP
#include "User.hpp"
#include <string>
#include <memory>   
class FlightManager;                 
class Administrator : public User{
    private:
    std::shared_ptr<FlightManager> flightManagerPtr;
    public:
    Administrator();
    Administrator(const Administrator& other) = default;
    Administrator(Administrator&&other) = default;
    Administrator(std::string username, std::string password);
    void viewMainMenu() override;
    int viewManageFlightMenu();
};

#endif 