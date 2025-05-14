#include "../../header/flight/Aircraft.hpp"

void Aircraft::setID(const std::string& id) {
    ID = id;
}   
void Aircraft::setModel(const std::string& model) {
    this->model = model;
}
void Aircraft::setManufacturer(const std::string& manufacturer) {
    this->manufacturer = manufacturer;
}
void Aircraft::setSeatingCapacity(int capacity) {
    seatingCapacity = capacity;
}   
void Aircraft::setRange(double range) {
    this->range = range;
}
void Aircraft::setMaintenanceHistory(const std::vector<std::string>& history) {
    maintenanceHistory = history;
}
void Aircraft::setLastMaintenanceDate(const std::shared_ptr<Date>& date) {
    lastMaintenanceDate = date;
}
void Aircraft::setNextMaintenanceDate(const std::shared_ptr<Date>& date) {
    nextMaintenanceDate = date;
}
void Aircraft::appendMaintenanceHistory(const std::string& entry) {
    maintenanceHistory.push_back(entry);
}
std::string Aircraft::getID() const {
    return ID;
}
std::string Aircraft::getModel() const {
    return model;
}
std::string Aircraft::getManufacturer() const {
    return manufacturer;
}
int Aircraft::getSeatingCapacity() const {
    return seatingCapacity;
}
double Aircraft::getRange() const {
    return range;
}
std::vector<std::string> Aircraft::getMaintenanceHistory() const {
    return maintenanceHistory;
}
std::shared_ptr<Date> Aircraft::getLastMaintenanceDate() const {
    return lastMaintenanceDate;
}
std::shared_ptr<Date> Aircraft::getNextMaintenanceDate() const {
    return nextMaintenanceDate;
}
bool Aircraft::operator==(const Aircraft& other) const {
    return ID == other.ID;
}
std::ostream& operator<<(std::ostream& os, const Aircraft& aircraft) {
    os << "Aircraft ID: " << aircraft.ID << "\n"
       << "Model: " << aircraft.model << "\n"
       << "Manufacturer: " << aircraft.manufacturer << "\n"
       << "Seating Capacity: " << aircraft.seatingCapacity << "\n"
       << "Range: " << aircraft.range << "\n"
       << "Maintenance History: ";
    for (const auto& entry : aircraft.maintenanceHistory) {
        os << entry << ", ";
    }
    os << "\nLast Maintenance Date: ";
    if (aircraft.lastMaintenanceDate) {
        os << *(aircraft.lastMaintenanceDate);
    } else {
        os << "N/A";
    }
    os << "\nNext Maintenance Date: ";
    if (aircraft.nextMaintenanceDate) {
        os << *(aircraft.nextMaintenanceDate);
    } else {
        os << "N/A";
    }
    return os;
}
