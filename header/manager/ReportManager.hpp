#ifndef REPORT_MANAGER_HPP
#define REPORT_MANAGER_HPP

#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include "../utils/Constants.hpp"
#include "../utils/JSONFileManager.hpp"
class ReportManager {
    private:
    Json_file_ptr reservationPtr = std::make_shared<JSONFileManager>(RESERVATION_FILE_PATH);
    Json_file_ptr flightPtr = std::make_shared<JSONFileManager>(FLIGHT_FILE_PATH);
    Json_file_ptr passengerPtr = std::make_shared<JSONFileManager>(PASSENGER_FILE_PATH);
    Json_file_ptr aircraftPtr = std::make_shared<JSONFileManager>(aircraft_file_path);
    public:
    ReportManager() = default;
    ReportManager(const ReportManager&) = default;
    ReportManager& operator=(const ReportManager&) = default;
    ReportManager(ReportManager&&) = default;
    ReportManager& operator=(ReportManager&&) = default;
    ~ReportManager() = default;
    void viewReportMenu();
    void generateOperationalReport(const std::string& date);
    void generateMaintenanceReport(const std::string& date);
    void generateUserActivityReport(const std::string& date);
};
#endif // REPORT_MANAGER_HPP