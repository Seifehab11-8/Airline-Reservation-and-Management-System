#include "../../header/manager/FlightManager.hpp"
#include "../../header/person/Pilot.hpp"
#include "../../header/person/FlightAttendant.hpp"
#include "../../header/flight/Flight.hpp"
#include "../../header/utils/IOStreamHelper.hpp"
#include <vector>

FlightManager::FlightManager() 
{
    file_access_ptr = std::make_shared<JSONFileManager>(FLIGHT_FILE_PATH);
    crew_file_access_ptr = std::make_shared<JSONFileManager>(FLIGHT_CREW_FILE_PATH);
}

void FlightManager:: create() 
{
    FLightPtr f_ptr = std::make_shared<Flight>();
    std::cin.ignore();
    std::cout<<"--- Add New Flight ---"<<std::endl;
    std::cin>>*(f_ptr);
    if(exist<Flight>(*f_ptr, file_access_ptr) != -1) {
        std::cout<<"Flight ID duplication your flight must have a unique ID"
                        <<std::endl;
        return;
    }

    file_access_ptr->append(*(f_ptr));
    std::cout<<std::endl;
    std::cout<<"Flight "
            <<f_ptr->getFlightNumber()
            <<" has been successfully added to the schedule."
            <<std::endl;
}
void FlightManager:: update() 
{
    FLightPtr flightPtr = nullptr;
    std::string flight_id;
    std::cin.ignore();
    std::cout<<"--- Update Existing Flight ---\n"
                <<"Enter Flight Number to Update eg.(AAxxx): ";
    std::getline(std::cin, flight_id);
    flightPtr = std::make_shared<Flight>();
    flightPtr->setFlightNumber(flight_id);
    const int index = exist<Flight>(*flightPtr, file_access_ptr);
    if(index != -1) {
        int option = 0;
        flightPtr = std::make_shared<Flight>(file_access_ptr->read<Flight>(index));
        std::cout<<"Select information to update:\n"
                    <<"1. Flight Details\n"
                    <<"2. Crew Assignments\n"
                    <<"3. Status\n"
                    <<"4. Back to Manage Flights\n"
                    <<"Enter choice: ";
        option = IOStreamHelper::InputNumeric();
        Update_Flight_Options enum_option = static_cast<Update_Flight_Options>(option);
        switch(enum_option) {
            case Update_Flight_Options::FLIGHT_DETAIL:
                editFlightDetails(flightPtr);
                file_access_ptr->update(index, *flightPtr);
                break;
            case Update_Flight_Options::CREW_ASSIGNMENT:
                editCrewAssignment(flightPtr);
                file_access_ptr->update(index, *flightPtr);
                break;
            case Update_Flight_Options::STATUS:
                editStatus(flightPtr);
                file_access_ptr->update(index, *flightPtr);
                break;
            default:
                break;
        }
    }
    else {
        std::cout<<"Flight Doesn't Exist"<<std::endl;
    }
}
void FlightManager:: _delete()
{
    std::string flight_id;
    std::cin.ignore();
    std::cout<<"--- Delete Flight ---"
                <<"Enter Flight Number to Delete eg.(AAxxx): ";
    std::getline(std::cin, flight_id);
    FLightPtr flightPtr = std::make_shared<Flight>();
    flightPtr->setFlightNumber(flight_id);
    const int index = exist<Flight>(*flightPtr, file_access_ptr);
    if(index != -1) {
        file_access_ptr->erase(index);
        std::cout<<"Flight "
                <<flightPtr->getFlightNumber()
                <<" has been successfully deleted from the schedule."
                <<std::endl;
    }
    else {
        std::cout<<"Flight Doesn't Exist"<<std::endl;
    }
}
void FlightManager:: view()
{
    std::cout<<"--- View Flight ---"<<std::endl;
    std::vector<Flight> flightList = file_access_ptr->getArray<Flight>();
    if(flightList.empty()) {
        std::cout<<"No flights available."<<std::endl;
        return;
    }
    for(const auto& it: flightList) {
        std::cout<<it<<std::endl;
    }
}

void FlightManager::editFlightDetails(FLightPtr flightPtr)
{
    std::cin.ignore();
    std::cout<<"Select information to update:\n"
                    <<"1. FlightNumber\n"
                    <<"2. Origin\n"
                    <<"3. Destination\n"
                    <<"4. Departure time\n"
                    <<"5. Arrival time\n"
                    <<"6. Aircraft\n"
                    <<"7. Number of seats\n"
                    <<"Enter choice: ";
    int option;
    std::cin>>option;
    //!Block Scope issue with switch case 
    // switch(option) {
    //     case 1:
    //         int x = 5; // Error: jump to case label crosses initialization of 'int x'
    //         // ...
    //         break;
    //     case 2:
    //         // ...
    //         break;
    // }
    // If the user enters option == 2, the code jumps directly to case 2: 
    // and skips the initialization of x.
    // But x is still in scope for the rest of the switch, 
    // which is unsafe.
    switch(option) {
        case 1: {
            std::cout<<"Enter Flight Number: ";
            std::cin.ignore();
            std::string flightNumber;
            std::getline(std::cin, flightNumber);
            std::string currentFlightNumber = flightPtr->getFlightNumber();
            flightPtr->setFlightNumber(flightNumber);
            if(exist<Flight>(*flightPtr, file_access_ptr) != -1) {
                std::cout<<"Flight ID duplication your flight must have a unique ID"
                        <<std::endl;
                flightPtr->setFlightNumber(currentFlightNumber);
                return;
            }
            break;
        }
        case 2: {
            std::cout<<"Enter Origin: ";
            std::cin.ignore();
            std::string origin;
            std::getline(std::cin, origin);
            flightPtr->setOrigin(origin);
            break;
        }
        case 3: {
            std::cout<<"Enter Destination: ";
            std::cin.ignore();
            std::string destination;
            std::getline(std::cin, destination);
            flightPtr->setDestination(destination);
            break;
        }
        case 4: {
            std::cout<<"Enter Departure Time: ";
            DatePtr deptTime = std::make_shared<Date>();
            std::cin>>*(deptTime);
            flightPtr->setDeptTime(deptTime);
            break;
        }
        case 5: {
            std::cout<<"Enter Arrival Time: ";
            DatePtr arrivalTime = std::make_shared<Date>();
            std::cin>>*(arrivalTime);
            flightPtr->setArrivalTime(arrivalTime);
            break;
        }
        case 6: {
            std::cout<<"Enter Aircraft Type: ";
            std::cin.ignore();
            std::string aircraftType;
            std::getline(std::cin, aircraftType);
            flightPtr->setAircraftType(aircraftType);
            break;
        }
        case 7: {
            int numOfSeats;
            std::cout<<"Enter Number of Seats: ";
            std::cin>>numOfSeats;
            flightPtr->setNumOfSeats(numOfSeats);
            break;
        }
        default:
            break;
    }
}

void FlightManager::editCrewAssignment(FLightPtr flightPtr)
{
    std::vector<CrewAttendant> crewList = crew_file_access_ptr->getArray<CrewAttendant>();
    std::cout<<"--- Crew Assignment ---"<<std::endl;
    std::cout<<"Available Pilots:\n";
    for(const auto& it: crewList) {
        if(it.getRole() == "Pilot" && it.getOccupation() == false) {
            std::cout<<static_cast<const Pilot&>(it)<<std::endl;
        }
    }
    std::cout<<"Select Pilot by ID: ";
    std::string pilot_id;
    std::cin.ignore();
    std::getline(std::cin, pilot_id);
    auto pilotPtr = std::make_shared<CrewAttendant>();
    pilotPtr->setID(pilot_id);
    //echo for debug purposes
    std::cout<<"Pilot ID: "<<pilotPtr->getID()<<std::endl;
    int pilotIndex = exist<CrewAttendant>(*pilotPtr, crew_file_access_ptr);
    if(pilotIndex != -1) {
        auto it = std::make_shared<CrewAttendant>(crewList.at(pilotIndex));
        auto pilot = std::dynamic_pointer_cast<Pilot>(it);
        flightPtr->setPilot(pilot);
        crewList.at(pilotIndex).setOccupation(true);
        crew_file_access_ptr->update(pilotIndex, crewList.at(pilotIndex));
    }
    else {
        std::cout<<"Pilot ID not found\n";
        return;
    }
    std::cout<<"Available Flight Attendants:\n";
    for(const auto& it: crewList) {
        if(it.getRole() == "Flight Attendant" && it.getOccupation() == false) {
            std::cout<<static_cast<const FlightAttendant&>(it)<<std::endl;
        }
    }
    std::cout<<"Select Flight Attendant by ID: ";
    std::string fa_id;
    std::getline(std::cin, fa_id);
    auto flightAttendantPtr = std::make_shared<FlightAttendant>();
    flightAttendantPtr->setID(fa_id);
    int flightAttendantIndex = exist<CrewAttendant>(*flightAttendantPtr, crew_file_access_ptr);
    if(flightAttendantIndex != -1) {
        auto it = std::make_shared<CrewAttendant>(crewList.at(flightAttendantIndex));
        auto flightAttendant = std::dynamic_pointer_cast<FlightAttendant>(it);
        flightPtr->setFlightAttendant(flightAttendant);
        crewList.at(flightAttendantIndex).setOccupation(true);
        crew_file_access_ptr->update(flightAttendantIndex, crewList.at(flightAttendantIndex));
    }
    else {
        std::cout<<"Flight Attendant ID not found\n";
        return;
    }
    std::cout<<"Crew assigned successfully to Flight "
            <<flightPtr->getFlightNumber()
            <<std::endl;
    
}

void FlightManager::editStatus(FLightPtr flightPtr)
{
    std::cin.ignore();
    std::cout<<"Enter Status (Scheduled/Delayed/Canceled): ";
    std::string status;
    std::getline(std::cin, status);
    flightPtr->setStatus(status);
    std::cout<<"Flight status has been updated to: "<<status<<std::endl;
}