#ifndef _BOOKING_AGENT_HPP
#define _BOOKING_AGENT_HPP
#include "User.hpp"
#include <string>
#include <memory>
class BookingManager;
class BookingAgent : public User{
    private:
    std::shared_ptr<BookingManager> bookingManager;
    friend std::ostream& operator<<(std::ostream& os, const BookingAgent& bookingAgent);;
    public:
    BookingAgent();
    BookingAgent(const BookingAgent& other) = default;
    BookingAgent(BookingAgent&&other) = default;
    BookingAgent(std::string username, std::string password);
    void viewMainMenu() override;
    bool operator==(const BookingAgent& other) const;
    void searchFlight();
    void bookFlight();
    void cancelFlight();
    void modifyFlight();
};
std::ostream& operator<<(std::ostream& os, const BookingAgent& bookingAgent);
#endif