#include "../../header/manager/FlightManager.hpp"
#include <vector>

FlightManager::FlightManager() 
{
    file_access_ptr = std::make_shared<JSONFileManager>(FLIGHT_FILE_PATH);
}

void FlightManager:: create() 
{
    const std::vector<Flight>& flightArray = file_access_ptr->getArray<Flight>();
    FLightPtr f_ptr;
    std::cout<<"--- Add New Flight ---"<<std::endl;
    std::cin>>*(f_ptr);
    for(auto &flight: flightArray) {
        if(flight.getFlightNumber() == f_ptr->getFlightNumber()) {
            std::cout<<"Flight ID duplication your flight must have a unique ID"
                        <<std::endl;
            return;
        }
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

}
void FlightManager:: _delete()
{

}
void FlightManager:: view()
{
    
} 