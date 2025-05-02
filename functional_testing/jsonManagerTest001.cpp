#include "../header/utils/JSONFileManager.hpp"
#include "../header/person/Passenger.hpp"
int main() {
    JSONFileManager j_manager("/Users/seifehab/Documents/GitHub/Airline-Reservation-and-Management-System/functional_testing/jsonTest001.json");
    Passenger p1;
    p1.appendFlight("AA123");
    p1.appendNotification("Flight AA123 is delayed");
    p1.appendPreference("Window seat");
    p1.setContact("0100023445");
    p1.setID(1);
    p1.setName("seif Doe");
    p1.setRole("Passenger");
    p1.setUsername("seif");
    p1.setPassword("password123");
    p1.setLoginStatus(true);
    // try{
    //     std::cout<<j_manager.read<Passenger>(0).getName()<<std::endl;
    // }
    // catch(const std::exception &e) {
    //     std::cerr<<"Error: "<<e.what()<<std::endl;
    // }
    std::cout<<j_manager.append(p1);
}

// compliation command
// g++ -std=c++17 -I /Users/seifehab/Documents/GitHub/Airline-Reservation-and-Management-System/header -o jsonManagerTest001 jsonManagerTest001.cpp /Users/seifehab/Documents/GitHub/Airline-Reservation-and-Management-System/src/utils/FileManager.cpp /Users/seifehab/Documents/GitHub/Airline-Reservation-and-Management-System/src/utils/JSONFileManager.cpp /Users/seifehab/Documents/GitHub/Airline-Reservation-and-Management-System/src/person/Passenger.cpp /Users/seifehab/Documents/GitHub/Airline-Reservation-and-Management-System/src/person/Administrator.cpp /Users/seifehab/Documents/GitHub/Airline-Reservation-and-Management-System/src/person/User.cpp /Users/seifehab/Documents/GitHub/Airline-Reservation-and-Management-System/src/person/Person.cpp /Users/seifehab/Documents/GitHub/Airline-Reservation-and-Management-System/src/utils/IOStreamHelper.cpp