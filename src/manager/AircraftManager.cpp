#include "../../header/manager/AircraftManager.hpp"
#include "../../header/utils/IOStreamHelper.hpp"
#include <iostream>

void AircraftManager::create() {
    std::cout << "--- Create New Aircraft ---\n";
    auto aircraft = std::make_shared<Aircraft>();

    std::string id, model, manufacturer;
    int seatingCapacity;
    double range;

    std::cout << "Enter Aircraft ID: ";
    std::cin >> id;
    aircraft->setID(id);

    std::cout << "Enter Model: ";
    std::cin.ignore();
    std::getline(std::cin, model);
    aircraft->setModel(model);

    std::cout << "Enter Manufacturer: ";
    std::getline(std::cin, manufacturer);
    aircraft->setManufacturer(manufacturer);

    std::cout << "Enter Seating Capacity: ";
    seatingCapacity = IOStreamHelper::InputNumeric();
    aircraft->setSeatingCapacity(seatingCapacity);

    std::cout << "Enter Range (km): ";
    std::cin >> range;
    aircraft->setRange(range);

    if (exist<Aircraft>(*aircraft, file_access_ptr) != -1) {
        std::cout << "Aircraft ID already exists.\n";
        return;
    }

    file_access_ptr->append(*aircraft);
    std::cout << "Aircraft created successfully.\n";
}

void AircraftManager::update() {
    std::cout << "--- Update Aircraft ---\n";
    std::cout << "Enter Aircraft ID to update: ";
    std::string id;
    std::cin >> id;

    auto aircraft = std::make_shared<Aircraft>();
    aircraft->setID(id);
    int index = exist<Aircraft>(*aircraft, file_access_ptr);
    if (index == -1) {
        std::cout << "Aircraft not found.\n";
        return;
    }

    *aircraft = file_access_ptr->read<Aircraft>(index);

    int option = 0;
    std::cout << "\nCurrent Aircraft Data:\n" << *aircraft << "\n";
    std::cout << "Select field to update:\n";
    std::cout << "1. Model\n";
    std::cout << "2. Manufacturer\n";
    std::cout << "3. Seating Capacity\n";
    std::cout << "4. Range\n";
    std::cout << "5. Maintenance History (append)\n";
    std::cout << "6. Last Maintenance Date\n";
    std::cout << "7. Next Maintenance Date\n";
    std::cout << "8. Add a new Maintenance Date\n";
    std::cout << "9. Back to Previous Menu\n";
    std::cout << "Enter choice: ";
    option = IOStreamHelper::InputNumeric();

    switch(option) {
        case 1: {
            std::cout << "Enter new Model: ";
            std::cin.ignore();
            std::string model;
            std::getline(std::cin, model);
            aircraft->setModel(model);
            break;
        }
        case 2: {
            std::cout << "Enter new Manufacturer: ";
            std::cin.ignore();
            std::string manufacturer;
            std::getline(std::cin, manufacturer);
            aircraft->setManufacturer(manufacturer);
            break;
        }
        case 3: {
            std::cout << "Enter new Seating Capacity: ";
            int seatingCapacity = IOStreamHelper::InputNumeric();
            aircraft->setSeatingCapacity(seatingCapacity);
            break;
        }
        case 4: {
            std::cout << "Enter new Range (km): ";
            double range;
            std::cin >> range;
            aircraft->setRange(range);
            break;
        }
        case 5: {
            char breakChar;
            do{
                std::cout << "Enter maintenance history entry to append: ";
                std::cin.ignore();
                std::string entry;
                std::getline(std::cin, entry);
                aircraft->appendMaintenanceHistory(entry);
                std::cout<< "Do you want to add another entry? (y/n): ";
                std::cin >> breakChar;
            }while(breakChar == 'y');
            break;
        }
        case 6: {
            std::cout << "Enter last maintenance date (YYYY-MM-DD): ";
            std::cin.ignore();
            std::string dateStr;
            std::getline(std::cin, dateStr);
            auto date = std::make_shared<Date>();
            date->from_string(dateStr);
            aircraft->setLastMaintenanceDate(date);
            break;
        }
        case 7: {
            std::cout << "Enter next maintenance date (YYYY-MM-DD): ";
            std::cin.ignore();
            std::string dateStr;
            std::getline(std::cin, dateStr);
            auto date = std::make_shared<Date>();
            date->from_string(dateStr);
            aircraft->setNextMaintenanceDate(date);
            break;
        }
        
        case 8: {
            std::cout << "Enter new Maintenance Date (YYYY-MM-DD): ";
            std::cin.ignore();
            std::string dateStr;
            std::getline(std::cin, dateStr);
            auto date = std::make_shared<Date>();
            date->from_string(dateStr);
            auto oldDate = aircraft->getNextMaintenanceDate();
            if (oldDate) {
                std::string maintanenceReason;
                std::cout << "Enter maintenance reason: ";
                std::getline(std::cin, maintanenceReason);
                aircraft->appendMaintenanceHistory("Maintenance Date changed from " + oldDate->to_string() + " to " + dateStr + ". Reason: " + maintanenceReason);
                aircraft->setLastMaintenanceDate(oldDate);
            }
            aircraft->setNextMaintenanceDate(date);
            break;
        }
        
        case 9:
            std::cout << "Finished updating.\n";
            break;
        default:
            std::cout << "Invalid option.\n";
    }

    file_access_ptr->update(index, *aircraft);
    std::cout << "Aircraft updated successfully.\n";
}

void AircraftManager::_delete() {
    std::cout << "--- Delete Aircraft ---\n";
    std::cout << "Enter Aircraft ID to delete: ";
    std::string id;
    std::cin >> id;

    auto aircraft = std::make_shared<Aircraft>();
    aircraft->setID(id);
    int index = exist<Aircraft>(*aircraft, file_access_ptr);
    if (index == -1) {
        std::cout << "Aircraft not found.\n";
        return;
    }

    file_access_ptr->erase(index);
    std::cout << "Aircraft deleted successfully.\n";
}

void AircraftManager::view() {
    std::cout << "--- View All Aircraft ---\n";
    auto aircraftList = file_access_ptr->getArray<Aircraft>();
    if (aircraftList.empty()) {
        std::cout << "No aircraft found.\n";
        return;
    }
    for (const auto& aircraft : aircraftList) {
        std::cout << aircraft << std::endl;
    }
}

int AircraftManager::viewMenu() {
    int choice;
    std::cout<<"--- Manage Aircraft ---\n"
                "1. Add Aircraft\n"
                "2. Update Aircraft\n"
                "3. Delete Aircraft\n"
                "4. View Aircraft\n"
                "5. Back to Main Menu\n"
                "Enter choice: ";
    choice = IOStreamHelper::InputNumeric();
    return choice;
}