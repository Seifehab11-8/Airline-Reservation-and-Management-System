#ifndef _PASSENGER_HPP
#define _PASSENGER_HPP
#include "User.hpp"
#include <vector>
#include <string>
class Passenger : public User{
    private:
    std::string contact;
    std::vector<std::string> preference;
    std::vector<std::string> flightHistory;
    std::vector<std::string> notifications;

    public:
    Passenger() = default;
    Passenger(std::string username, std::string password);
    Passenger(const Passenger&other) = default;
    Passenger(Passenger&&other) = default;
    void viewMainMenu() override;
    void appendPreference(std::string pref);
    void appendFlight(std::string flight);
    void appendNotification(std::string note);
    void setContact(std::string contact);
    void setPerference(std::vector<std::string> preference);
    void setFlightHistory(std::vector<std::string> flightHistory);
    void setNotifications(std::vector<std::string> notifications);
    std::string getContact() const;
    std::vector<std::string> getPreference() const;
    std::vector<std::string> getFlightHistory() const;
    std::vector<std::string> getNotifications() const;
};

#endif