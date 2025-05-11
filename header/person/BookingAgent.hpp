#ifndef _BOOKING_AGENT_HPP
#define _BOOKING_AGENT_HPP
#include "User.hpp"
#include <string>
class BookingAgent : public User{
    private:
    friend std::ostream& operator<<(std::ostream& os, const BookingAgent& bookingAgent);
    public:
    BookingAgent() = default;
    BookingAgent(const BookingAgent& other) = default;
    BookingAgent(BookingAgent&&other) = default;
    BookingAgent(std::string username, std::string password);
    void viewMainMenu() override;
    bool operator==(const BookingAgent& other) const;
};
std::ostream& operator<<(std::ostream& os, const BookingAgent& bookingAgent);
#endif