#ifndef _FLIGHT_MANAGER_HPP
#define _FLIGHT_MANAGER_HPP

#include "../manager/IManager.hpp"
#include "../flight/Flight.hpp"
#include "../nlohmann/adl_serializer_flight.hpp"
#include <iostream>
#include <string>

constexpr const char* FLIGHT_FILE_PATH = "../storage/flights001.json";
class FlightManager : public IManager{
    public:
    FlightManager();
    FlightManager(const FlightManager &other) = default;
    FlightManager(FlightManager && other) = default;
    void create() override;
    void update() override;
    void _delete() override;
    void view() override;
};

#endif