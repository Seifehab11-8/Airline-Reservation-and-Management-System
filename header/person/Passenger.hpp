#ifndef _PASSENGER_HPP
#define _PASSENGER_HPP
#include "User.hpp"
#include <vector>
#include <string>
class IPayment;
class JSONFileManager;
class Passenger : public User{
    private:
    std::string contact;
    std::vector<std::string> preference;
    std::vector<std::string> flightHistory;
    std::vector<std::string> notifications;
    double balance;
    friend std::ostream& operator<<(std::ostream& os, const Passenger& passenger);
    public:
    Passenger();
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
    void setBalance(double balance);
    std::string getContact() const;
    std::vector<std::string> getPreference() const;
    std::vector<std::string> getFlightHistory() const;
    std::vector<std::string> getNotifications() const;
    double getBalance() const;
    void pay(std::shared_ptr<IPayment> payment, double amount);
    // main logic of the class
    void searchFlight();
    void viewMyReservation();
    void checkIn();
    void viewMyNotification();
    // end of class main logic
    bool operator==(const Passenger& other) const;
};
std::ostream& operator<<(std::ostream& os, const Passenger& passenger);
#endif