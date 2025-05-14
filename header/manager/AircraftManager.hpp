#ifndef AIRCRAFTMANAGER_HPP
#define AIRCRAFTMANAGER_HPP
#include <string>
#include <iostream>
#include <memory>
#include "../flight/Aircraft.hpp"
#include "../utils/IOStreamHelper.hpp"
#include "../utils/JSONFileManager.hpp"
#include "../utils/Constants.hpp"
#include "IManager.hpp"


class AircraftManager : public IManager {
    private:
    Json_file_ptr file_access_ptr = std::make_shared<JSONFileManager>(aircraft_file_path);
    public:
    AircraftManager() = default;
    AircraftManager(const AircraftManager &other) = default;
    AircraftManager(AircraftManager &&other) = default;
    ~AircraftManager() = default;
    void create() override;
    void update() override;
    void _delete() override;
    void view() override;
    int viewMenu() override;
};
#endif