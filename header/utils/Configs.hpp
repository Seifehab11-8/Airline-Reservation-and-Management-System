#ifndef _CONFIGS_HPP
#define _CONFIGS_HPP

enum UserRole {
    ADMIN = 1,
    PASSENGER = 2,
    BOOKING_AGENT = 3
};

enum AdminMenuOption {
    MANAGE_FLIGHTS = 1,
    MANAGE_USERS,
    MANAGE_AIRCRAFT,
    GENERATE_REPORTS,
    LOGOUT
};

enum PassengerMenuOption {
    SEARCH_FLIGHTS = 1,
    BOOK_TICKET,
    VIEW_BOOKINGS,
    CHECK_IN,
    LOGOUT
};

enum BookingAgentMenuOption {
    SEARCH_FLIGHTS = 1,
    BOOK_TICKET,
    MODIFY_RESERVATION,
    CANCEL_RESERVATION,
    LOGOUT
};

enum MainMenuOption {
    OP1 = 1,
    OP2,
    OP3,
    OP4,
    OP5
};


#endif