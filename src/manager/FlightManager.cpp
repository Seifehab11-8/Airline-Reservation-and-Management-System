#include "../../header/manager/FlightManager.hpp"
#include "../../header/person/Pilot.hpp"
#include "../../header/person/FlightAttendant.hpp"
#include "../../header/flight/Flight.hpp"
#include "../../header/utils/IOStreamHelper.hpp"
#include "../../header/flight/Reservation.hpp"
#include <vector>

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
                std::cout<<*flightPtr<<std::endl;
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
void FlightManager::_delete()
{
    std::string flight_id;
    std::cin.ignore();
    std::cout << "--- Delete Flight ---\n"
              << "Enter Flight Number to Delete eg.(AAxxx): ";
    std::getline(std::cin, flight_id);

    FLightPtr flightPtr = std::make_shared<Flight>();
    flightPtr->setFlightNumber(flight_id);
    const int index = exist<Flight>(*flightPtr, file_access_ptr);

    if (index == -1) {
        std::cout << "Flight Doesn't Exist" << std::endl;
        return;
    }

    // Read the full flight object
    flightPtr = std::make_shared<Flight>(file_access_ptr->read<Flight>(index));

    // Unassign pilot and flight attendant if assigned
    auto pilot = flightPtr->getPilot();
    int flightTime = flightPtr->getArrivalTime()->differenceHoursMin(*flightPtr->getDeptTime());;
    if (pilot) {
        int pilot_index = exist<Pilot>(*pilot, pilot_file_access_ptr);
        pilot = std::make_shared<Pilot>(pilot_file_access_ptr->read<Pilot>(pilot_index));
        if (pilot_index != -1) {
            pilot->setOccupation(false);
            pilot->setFlyingHours(pilot->getFlyingHours() - flightTime);
            pilot_file_access_ptr->update(pilot_index, *pilot);
        }
    }

    auto flight_attendant = flightPtr->getFlightAttendant();
    if (flight_attendant) {
        int fa_index = exist<FlightAttendant>(*flight_attendant, flightAttendant_file_access_ptr);
        if (fa_index != -1) {
            flight_attendant->setOccupation(false);
            flightAttendant_file_access_ptr->update(fa_index, *flight_attendant);
        }
    }

    // Remove the flight
    file_access_ptr->erase(index);
    std::cout << "Flight " << flightPtr->getFlightNumber()
              << " has been successfully deleted from the schedule." << std::endl;
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
                    <<"8. Gate Number\n"
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
        case 8: {
            std::cout<<"Enter Gate Number: ";
            std::cin.ignore();
            std::string gateNumber;
            std::getline(std::cin, gateNumber);
            flightPtr->setGateNumber(gateNumber);
            break;
        }
        default:
            break;
    }
}

void FlightManager::editCrewAssignment(FLightPtr flightPtr)
{
    auto pilots = pilot_file_access_ptr->getArray<Pilot>();
    auto flightAttendants = flightAttendant_file_access_ptr->getArray<FlightAttendant>();

    double flightHours = 0.0;
    if (flightPtr->getArrivalTime() && flightPtr->getDeptTime()) {
        flightHours = flightPtr->getArrivalTime()->differenceHoursMin(*flightPtr->getDeptTime());
    }

    // --- Pilot Selection ---
    std::cout << "--- Crew Assignment ---\nAvailable Pilots:\n";
    for (const auto& it : pilots) {
        if (!it.getOccupation()) {
            std::cout << it << std::endl;
        }
    }
    std::cout << "Select Pilot by ID: ";
    std::string pilot_id;
    std::cin.ignore();
    std::getline(std::cin, pilot_id);

    int pilotIndex = -1;
    for (size_t i = 0; i < pilots.size(); ++i) {
        if (pilots[i].getID() == pilot_id) {
            pilotIndex = static_cast<int>(i);
            break;
        }
    }
    if (pilotIndex == -1) {
        std::cout << "Pilot ID not found\n";
        return;
    }

    auto prevPilotPtr = flightPtr->getPilot();
    if (prevPilotPtr) {
        int prevIndex = exist<Pilot>(*prevPilotPtr, pilot_file_access_ptr);
        if (prevIndex != -1) {
            pilots[prevIndex].setFlyingHours(pilots[prevIndex].getFlyingHours() - flightHours);
            pilots[prevIndex].setOccupation(false);
            pilots[prevIndex].setName(pilots[prevIndex].getName()); // make sure the pointer has the name
            pilot_file_access_ptr->update(prevIndex, pilots[prevIndex]);
        }
    }

    // Assign new pilot and add flight hours
    auto pilotPtr = std::make_shared<Pilot>(pilots[pilotIndex]);
    flightPtr->setPilot(pilotPtr);
    pilotPtr->setOccupation(true);
    pilotPtr->setFlyingHours(pilotPtr->getFlyingHours() + flightHours);

    pilot_file_access_ptr->update(pilotIndex, *pilotPtr);

    // --- Flight Attendant Selection ---
    std::cout << "Available Flight Attendants:\n";
    for (const auto& it : flightAttendants) {
        if (!it.getOccupation()) {
            std::cout << it << std::endl;
        }
    }
    std::cout << "Select Flight Attendant by ID: ";
    std::string fa_id;
    std::getline(std::cin, fa_id);

    int faIndex = -1;
    for (size_t i = 0; i < flightAttendants.size(); ++i) {
        if (flightAttendants[i].getID() == fa_id) {
            faIndex = static_cast<int>(i);
            break;
        }
    }
    if (faIndex == -1) {
        std::cout << "Flight Attendant ID not found\n";
        return;
    }

    auto prevFAPtr = flightPtr->getFlightAttendant();
    if (prevFAPtr) {
        int prevIndex = exist<FlightAttendant>(*prevFAPtr, flightAttendant_file_access_ptr);
        if (prevIndex != -1) {
            flightAttendants[prevIndex].setFlyingHours(flightAttendants[prevIndex].getFlyingHours() - flightHours);
            flightAttendants[prevIndex].setOccupation(false);
            flightAttendant_file_access_ptr->update(prevIndex, flightAttendants[prevIndex]);
        }
    }

    // Assign new flight attendant and add flight hours
    auto faPtr = std::make_shared<FlightAttendant>(flightAttendants[faIndex]);
    faPtr->setName(flightAttendants[faIndex].getName()); // make sure the pointer has the name
    flightPtr->setFlightAttendant(faPtr);

    faPtr->setOccupation(true);
    faPtr->setFlyingHours(faPtr->getFlyingHours() + flightHours);

    flightAttendant_file_access_ptr->update(faIndex, *faPtr);

    std::cout << "Crew assigned successfully to Flight " << flightPtr->getFlightNumber() << std::endl;
}

void FlightManager::editStatus(FLightPtr flightPtr)
{
    std::cin.ignore();
    std::cout<<"Enter Status (Scheduled/Delayed/Canceled): ";
    std::string status;
    std::getline(std::cin, status);
    flightPtr->setStatus(status);
    if(status == "Delayed") {
        std::cout<<"Enter new Departure Time: ";
        DatePtr deptTime = std::make_shared<Date>();
        std::cin>>*(deptTime);
        flightPtr->setDeptTime(deptTime);
        std::cout<<"Enter new Arrival Time: ";
        DatePtr arrivalTime = std::make_shared<Date>();
        std::cin>>*(arrivalTime);
        flightPtr->setArrivalTime(arrivalTime);
    }
    std::vector<Reservation> reservationList = reservation_file_access_ptr->getArray<Reservation>();
    std::vector<Passenger> passengerList = passenger_file_access_ptr->getArray<Passenger>();
    for (auto& reservation : reservationList) {
        if (reservation.getFlightNumber() == flightPtr->getFlightNumber()) {
            for (auto& passenger : passengerList) {
                if (passenger.getUsername() == reservation.getPassengerUsername()) {
                    if(status == "Delayed"){
                        passenger.appendNotification("Your flight " + flightPtr->getFlightNumber() 
                                    + " has been " + status+ " to " + flightPtr->getDeptTime()->to_string());
                    }
                    else if(status == "Canceled") {
                        std::string note = "Your flight " + flightPtr->getFlightNumber() 
                        + " has been " + status + " and your payment $" + std::to_string(reservation.getPricePaid()) + " has been refunded. to ";
                        reservation.setStatus("Canceled");
                        if(auto payment = std::dynamic_pointer_cast<CreditCard>(reservation.getPaymentMethod())) {
                            note+= ("Credit Card Number: "+ payment->getCardNumber());
                        }
                        else if(auto payment = std::dynamic_pointer_cast<Paypal>(reservation.getPaymentMethod())) {
                            note+= ("Paypal Email: "+ payment->getEmail());
                        }
                        else {
                            note+= ("your wallet");
                        }
                        passenger.appendNotification(note);
                        passenger.setBalance(passenger.getBalance() + reservation.getPricePaid());
                    }
                    passenger_file_access_ptr->update(exist<Passenger>(passenger, passenger_file_access_ptr), passenger);
                    reservation_file_access_ptr->update(exist<Reservation>(reservation, reservation_file_access_ptr), reservation);
                }
            }
        }
    }
    
    std::cout<<"Flight status has been updated to: "<<status<<std::endl;
}

int FlightManager::viewMenu()
{
    int choice;
    std::cout<<"--- Manage Flights ---\n"
                "1. Add Flight\n"
                "2. Update Flight\n"
                "3. Delete Flight\n"
                "4. View Flights\n"
                "5. Back to Main Menu\n"
                "Enter choice: ";
    choice = IOStreamHelper::InputNumeric();
    return choice;
}