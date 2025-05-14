#ifndef _CONFIGS_HPP
#define _CONFIGS_HPP
namespace LoginAction {
    enum class UserRole {
        ADMIN = 1,
        PASSENGER = 2,
        BOOKING_AGENT = 3
    };
}

namespace AdminAction {
    enum class AdminMenuOption {
        MANAGE_FLIGHTS = 1,
        MANAGE_AIRCRAFT,
        MANAGE_USERS,
        GENERATE_REPORTS,
        LOGOUT
    };
}

namespace PassengerAction{
    enum class PassengerMenuOption {
        SEARCH_FLIGHTS = 1,
        VIEW_RESERVATIONS,
        VIEW_BOOKINGS,
        CHECK_IN,
        LOGOUT
    };
}

namespace BookingAgentAction {
    enum class BookingAgentMenuOption {
        SEARCH_FLIGHTS = 1,
        BOOK_TICKET,
        MODIFY_RESERVATION,
        CANCEL_RESERVATION,
        LOGOUT
    };
}

#endif