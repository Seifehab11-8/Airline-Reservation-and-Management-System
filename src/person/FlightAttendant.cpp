#include "../../header/person/FlightAttendant.hpp"
#include <iostream>

std::istream& operator >> (std::istream & is, FlightAttendant& attendant){
    is.ignore();
    std::cout<<"Enter Attendant's name: ";
    std::getline(is, attendant.name);
    std::cout<<"Enter Attendant's ID eg.(FAxxx): ";
    std::getline(is,attendant.id);
}
std::ostream& operator <<(std::ostream & os, const FlightAttendant& attendant){
    std::cout<<attendant.id
                <<" - "
                <<attendant.name
                <<std::endl;
}