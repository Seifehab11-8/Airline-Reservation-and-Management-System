#ifndef _BOOKING_AGENT_HPP
#define _BOOKING_AGENT_HPP
#include "User.hpp"
#include <string>
class BookingAgent : public User{
    public:
    BookingAgent() = delete;
    BookingAgent(const BookingAgent& other) = default;
    BookingAgent(BookingAgent&&other) = default;
    BookingAgent(std::string username, std::string password);
    void viewMainMenu() override;
};

#endif