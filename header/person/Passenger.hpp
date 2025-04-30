#ifndef _PASSENGER_HPP
#define _PASSENGER_HPP
#include "User.hpp"
#include <vector>
#include <string>
class Passenger : public User{
    private:
    std::string contactDetails;
    std::vector<std::string> preference;
    std::vector<std::string> flightHistory;
    std::vector<std::string> notifications;

    public:
    Passenger() = delete;
    Passenger(std::string username, std::string password);
    Passenger(const Passenger&other) = default;
    Passenger(Passenger&&other) = default;
    void viewMainMenu() override;
};

#endif