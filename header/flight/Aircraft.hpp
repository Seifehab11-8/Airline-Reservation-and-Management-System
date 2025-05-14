#ifndef AIRCRAFT_HPP
#define AIRCRAFT_HPP
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "../utils/Date.hpp"
class Aircraft {
    private:
    std::string ID;
    std::string model;
    std::string manufacturer;
    int seatingCapacity;
    double range;
    std::vector<std::string> maintenanceHistory;
    std::shared_ptr<Date> lastMaintenanceDate;
    std::shared_ptr<Date> nextMaintenanceDate;
    friend std::ostream& operator<<(std::ostream& os, const Aircraft& aircraft);
    public:
    Aircraft() = default;
    Aircraft(const Aircraft& other) = default;
    Aircraft(Aircraft &&other) = default;
    Aircraft& operator=(const Aircraft& other) = default;
    Aircraft& operator=(Aircraft &&other) = default;
    ~Aircraft() = default;
    void setID(const std::string& id);
    void setModel(const std::string& model);
    void setManufacturer(const std::string& manufacturer);
    void setSeatingCapacity(int capacity);
    void setRange(double range);
    void setMaintenanceHistory(const std::vector<std::string>& history);
    void setLastMaintenanceDate(const std::shared_ptr<Date>& date);
    void setNextMaintenanceDate(const std::shared_ptr<Date>& date);
    void appendMaintenanceHistory(const std::string& entry);
    std::string getID() const;
    std::string getModel() const;
    std::string getManufacturer() const;
    int getSeatingCapacity() const;
    double getRange() const;
    std::vector<std::string> getMaintenanceHistory() const;
    std::shared_ptr<Date> getLastMaintenanceDate() const;
    std::shared_ptr<Date> getNextMaintenanceDate() const;
    bool operator==(const Aircraft& other) const;
};

std::ostream& operator<<(std::ostream& os, const Aircraft& aircraft);
#endif