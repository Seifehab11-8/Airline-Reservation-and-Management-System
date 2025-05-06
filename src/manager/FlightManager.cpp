#include "../../header/manager/FlightManager.hpp"
#include <vector>

FlightManager::FlightManager() 
{
    file_access_ptr = std::make_shared<JSONFileManager>(FLIGHT_FILE_PATH);
    crew_file_access_ptr = std::make_shared<JSONFileManager>(FLIGHT_CREW_FILE_PATH);
}

void FlightManager:: create() 
{
    FLightPtr f_ptr;
    std::cout<<"--- Add New Flight ---"<<std::endl;
    std::cin>>*(f_ptr);
    if(exist<Flight>(*f_ptr) != -1) {
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
    FLightPtr flightPtr;
    std::string flight_id;
    std::cin.ignore();
    std::cout<<"--- Update Existing Flight ---"
                <<"Enter Flight Number to Update eg.(AAxxx): ";
    std::getline(std::cin, flight_id);
    flightPtr = std::make_shared<Flight>();
    flightPtr->setFlightNumber(flight_id);
    const int index = exist<Flight>(*flightPtr);
    if(index != -1) {
        int option = 0;
        flightPtr = std::make_shared<Flight>(file_access_ptr->read<Flight>(index));
        std::cout<<"Select information to update:\n"
                    <<"1. Flight Details\n"
                    <<"2. Crew Assignments\n"
                    <<"3. Status\n"
                    <<"4. Back to Manage Flights\n"
                    <<"Enter choice: ";
        std::cin>>option;
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

}
void FlightManager:: view()
{
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
            if(exist<Flight>(*flightPtr) != -1) {
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