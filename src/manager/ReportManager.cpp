#include "../../header/manager/ReportManager.hpp"
#include "../../header/person/Passenger.hpp"
#include "../../header/flight/Flight.hpp"
#include "../../header/flight/Aircraft.hpp"
#include "../../header/flight/Reservation.hpp"
#include "../../header/utils/IOStreamHelper.hpp"
#include "../../header/utils/Date.hpp"
#include <tuple>
#include <iomanip> // For std::setw, std::left, std::right, etc.

void ReportManager::viewReportMenu() {
    std::cout << "--- Report Menu ---\n"
              << "1. Operational Report\n"
              << "2. Maintenance Report\n"
              << "3. User Activity Report\n"
              << "4. Back to Main Menu\n"
              << "Enter your choice: ";
    int choice = IOStreamHelper::InputNumeric();
    std::string date;

    switch (choice) {
        case 1:
            std::cout<<"--- Operational Reports ---\n";
            std::cout << "Enter date (MM-YYYY): ";
            std::cin >> date;
            generateOperationalReport(date);
            break;
        case 2:
            std::cout<<"--- Maintenance Reports ---\n";
            std::cout << "Enter date (MM-YYYY): ";
            std::cin >> date;
            generateMaintenanceReport(date);
            break;
        case 3:
            std::cout<<"--- User Activity Reports ---\n";
            std::cout << "Enter date (MM-YYYY): ";
            std::cin >> date;
            generateUserActivityReport(date);
            break;
        case 4:
            std::cout << "Returning to Main Menu...\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            viewReportMenu();
            break;
    }
}

void ReportManager::generateOperationalReport(const std::string& date)
{
    auto reservations = reservationPtr->getArray<Reservation>();
    auto flights = flightPtr->getArray<Flight>();
    auto datePtr = Date::processMonthYearFormat(date);
    std::string monthStr = Date::monthToText(datePtr->getMonth());
    //flight id, status of flight, no of reservation per flight, total profit of the flight
    std::vector<std::tuple<std::string, std::string, int, double>> flightPerformance;
    if(monthStr == "") {   
        std::cerr << "Invalid month format. Please enter a valid month (1-12).\n";
        return;
    }
    int totalFlightsScheduled = 0;
    int totalFlightsCancelled = 0;
    int totalFlightsCompleted = 0;
    int totalFlightsDelayed = 0;
    int totalReservationsMade = 0;
    double totalRevenue = 0;
    for(auto &flight: flights) {
        if(flight.getDeptTime()->getYear() == datePtr->getYear() && flight.getDeptTime()->getMonth() == datePtr->getMonth()) {
            totalFlightsScheduled++;
            totalReservationsMade += flight.getNumOfSeats() - flight.getNumOfAvailableSeats();
            double profitPerFlight = 0;
            for(auto &reservation: reservations) {
                if(reservation.getFlightNumber() == flight.getFlightNumber() && reservation.getStatus() != "Canceled") {
                    //totalReservationsMade++;
                    profitPerFlight += reservation.getPricePaid();
                    totalRevenue += reservation.getPricePaid();
                }
            }
            if(flight.getStatus() == "Cancelled") {
                totalFlightsCancelled++;
            }
            else if(flight.getStatus() == "Scheduled") {
                totalFlightsCompleted++;
            }
            else if(flight.getStatus() == "Delayed") {
                totalFlightsDelayed++;
            }
            flightPerformance.push_back(std::make_tuple(
                        flight.getFlightNumber(),
                        flight.getStatus(),
                        flight.getNumOfSeats() - flight.getNumOfAvailableSeats(),
                        profitPerFlight
                        
                    ));
        }
    }

    std::cout << "Generating Operational Report for " << monthStr 
              << " " << datePtr->getYear() << "...\n\n";
    std::cout << "Report Summary: \n";
    std::cout << "Total Flights Scheduled: " << totalFlightsScheduled << "\n";
    std::cout << "Total Flights Cancelled: " << totalFlightsCancelled << "\n";
    std::cout << "Total Flights Completed: " << totalFlightsCompleted << "\n";
    std::cout << "Total Flights Delayed: " << totalFlightsDelayed << "\n";
    std::cout << "Total Reservations Made: " << totalReservationsMade << "\n";
    std::cout << "Total Revenue: $" << totalRevenue << "\n\n";
    std::cout << "Detailed Flight Performance:\n";

    int counter = 1;
    // format: 1. Flight AA123: On Time (120 Bookings, $42,000)
    for (auto &flightItem : flightPerformance)
    {
        // Convert "Scheduled" to "On Time" for display (optional)
        std::string flightStatus = (std::get<1>(flightItem) == "Scheduled") 
                                     ? "On Time" 
                                     : std::get<1>(flightItem);

        // Use std::setw for spacing:
        std::cout 
            << std::setw(2) << counter++ << ". " 
            << "Flight " 
            << std::setw(8) << std::left << std::get<0>(flightItem)
            << ": " 
            << std::setw(8) << std::left << flightStatus
            << "(" 
            << std::setw(4) << std::left << std::get<2>(flightItem)
            << " Bookings, $" 
            << std::setw(6) << std::right << std::get<3>(flightItem)
            << ")\n";
    }

    // ...existing code continues...
}

void ReportManager::generateMaintenanceReport(const std::string& date) {
    auto aircrafts = aircraftPtr->getArray<Aircraft>();
    auto datePtr = Date::processMonthYearFormat(date);
    std::string monthStr = Date::monthToText(datePtr->getMonth());
    if(monthStr == "") {   
        std::cerr << "Invalid month format. Please enter a valid month (1-12).\n";
        return;
    }
    std::cout << "Generating Maintenance Report for " << monthStr << " " << datePtr->getYear() << "...\n\n";
    std::cout << "Aircraft Maintenance Report:\n";
    std::cout << "-----------------------------------\n";
    std::cout << "Total Aircrafts: " << aircrafts.size() << "\n\n";

    std::cout<< "Detailed Maintenance Performance:\n";
    int counter = 1;
    for(const auto& aircraft: aircrafts) {
        if((aircraft.getLastMaintenanceDate()->getYear() != datePtr->getYear() 
            || aircraft.getLastMaintenanceDate()->getMonth() != datePtr->getMonth())
                && (aircraft.getNextMaintenanceDate()->getYear() != datePtr->getYear()
                || aircraft.getNextMaintenanceDate()->getMonth() != datePtr->getMonth())) continue;

        std::cout<<counter<<". Aircraft "
                <<aircraft.getID()<<": "
                <<aircraft.getModel()<<" ("
                <<aircraft.getManufacturer()<<")\n";
        std::cout<<"Seating Capacity: "<<aircraft.getSeatingCapacity()<<"\n";
        std::cout<<"--- Maintenance History ---\n";
        for(const auto& history: aircraft.getMaintenanceHistory()) {
            std::cout<<history<<", ";
        }
        std::cout<<"\nLast Maintenance Date: "<<aircraft.getLastMaintenanceDate()->to_string()<<"\n";
        std::cout<<"Next Maintenance Date: "<<aircraft.getNextMaintenanceDate()->to_string()<<"\n";
        std::cout<<"-----------------------------------\n";
        counter++;
    }  
    
} 

void ReportManager::generateUserActivityReport(const std::string& date) {
    auto reservations = reservationPtr->getArray<Reservation>();
    auto passengers = passengerPtr->getArray<Passenger>();
    auto datePtr = Date::processMonthYearFormat(date);
    // username and id, no of reservations done in these month, and number of canceled reservations if any
    std::vector<std::tuple<std::string, std::string, int, int>> userActivity;
    std::string monthStr = Date::monthToText(datePtr->getMonth());
    if(monthStr == "") {   
        std::cerr << "Invalid month format. Please enter a valid month (1-12).\n";
        return;
    }
    std::cout << "Generating User Activity Report for " << monthStr << " " << datePtr->getYear() << "...\n\n";
    std::cout << "User Activity Report:\n";
    std::cout << "-----------------------------------\n";
    

    std::cout<< "Detailed User Activity Performance:\n";
    int counter = 1;
    for(auto &passenger: passengers) {
        int totalReservations = 0;
        int totalCanceled = 0;
        for(auto &reservation: reservations) {
            if(reservation.getPassengerUsername() == passenger.getUsername()) {
                if(reservation.getStatus() == "Canceled") {
                    totalCanceled++;
                }
                else {
                    totalReservations++;
                }
            }
        }
        if(totalReservations == 0 && totalCanceled == 0) continue;
        userActivity.push_back(std::make_tuple(
                    passenger.getUsername(),
                    passenger.getID(),
                    totalReservations,
                    totalCanceled
                ));
    }
    std::cout << "Total Users: " << userActivity.size() << "\n\n";
    std::cout << "Detailed User Activity Performance:\n";
    counter = 1;
    for(auto &user: userActivity) {
        std::cout<<counter<<". User :"
                <<std::get<0>(user)<<" ID: "
                <<std::get<1>(user)<<"\n";
        std::cout<<"Total Reservations: "<<std::get<2>(user)<<"\n";
        std::cout<<"Total Canceled Reservations: "<<std::get<3>(user)<<"\n";
        std::cout<<"-----------------------------------\n";
        counter++;
    }
}