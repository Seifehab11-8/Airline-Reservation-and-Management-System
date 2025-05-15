#ifndef _FLIGHT_MANAGER_HPP
#define _FLIGHT_MANAGER_HPP

#include "../manager/IManager.hpp"
#include "../utils/Constants.hpp"
#include <iostream>
#include <string>

class Flight;


class FlightManager : public IManager{
    private:
    Json_file_ptr file_access_ptr = std::make_shared<JSONFileManager>(FLIGHT_FILE_PATH);
    Json_file_ptr pilot_file_access_ptr = std::make_shared<JSONFileManager>(FLIGHT_PILOT_FILE_PATH);
    Json_file_ptr flightAttendant_file_access_ptr = std::make_shared<JSONFileManager>(FLIGHT_ATTENDANT_FILE_PATH);
    Json_file_ptr passenger_file_access_ptr = std::make_shared<JSONFileManager>(PASSENGER_FILE_PATH);
    Json_file_ptr reservation_file_access_ptr = std::make_shared<JSONFileManager>(RESERVATION_FILE_PATH);
    public:
    FlightManager() = default;
    FlightManager(const FlightManager &other) = default;
    FlightManager(FlightManager && other) = default;
    void create() override;
    void update() override;
    void _delete() override;
    void view() override;
    int viewMenu() override;
    void editFlightDetails(FLightPtr flightPtr);
    void editCrewAssignment(FLightPtr flightPtr);
    void editStatus(FLightPtr flightPtr);
};

enum class Update_Flight_Options{
    FLIGHT_DETAIL = 1,
    CREW_ASSIGNMENT,
    STATUS,
    BACK_TO_MANAGE_FLIGHT
};

#endif
