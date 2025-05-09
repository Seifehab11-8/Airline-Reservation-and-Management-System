#ifndef _FLIGHT_MANAGER_HPP
#define _FLIGHT_MANAGER_HPP

#include "../manager/IManager.hpp"
#include <iostream>
#include <string>

class Flight;
constexpr const char* FLIGHT_FILE_PATH = "../../../storage/flights001.json";
constexpr const char* FLIGHT_CREW_FILE_PATH = "../../../storage/crew.json";
class FlightManager : public IManager{
    private:
    Json_file_ptr crew_file_access_ptr;
    public:
    FlightManager();
    FlightManager(const FlightManager &other) = default;
    FlightManager(FlightManager && other) = default;
    void create() override;
    void update() override;
    void _delete() override;
    void view() override;
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
