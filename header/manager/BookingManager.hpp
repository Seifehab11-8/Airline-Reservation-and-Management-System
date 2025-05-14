#ifndef BOOKING_MANAGER_HPP
#define BOOKING_MANAGER_HPP
#include "../utils/Constants.hpp"
#include "../utils/JSONFileManager.hpp"
#include <string>
#include <vector>
#include <memory>
class Passenger;
class Flight;
class Reservation;
constexpr int NUM_OF_SEATS_PER_ROW = 6;
class BookingManager {
    private:
    Json_file_ptr flightPtr = std::make_shared<JSONFileManager>(FLIGHT_FILE_PATH);
    Json_file_ptr reservationPtr = std::make_shared<JSONFileManager>(RESERVATION_FILE_PATH);
    Json_file_ptr passengerPtr = std::make_shared<JSONFileManager>(PASSENGER_FILE_PATH);
    public:
    BookingManager() = default;
    BookingManager(const BookingManager& other) = default;
    BookingManager(BookingManager&& other) = default;
    BookingManager& operator=(const BookingManager& other) = default;
    ~BookingManager() = default;
    std::shared_ptr<Reservation> book(Passenger& passenger, Flight& flight);
    Json_file_ptr getFlightPtr() const;
    Json_file_ptr getReservationPtr() const;
    Json_file_ptr getPassengerPtr() const;
};
#endif