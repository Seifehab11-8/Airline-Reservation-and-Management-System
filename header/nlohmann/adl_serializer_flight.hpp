#include <stdexcept>
#include <iostream>
#include "json.hpp"
#include "../flight/Flight.hpp"
namespace nlohmann 
{
    template<>
    struct adl_serializer<Flight>
    {
        static void to_json(json &j, const Flight &flight)
        {
            j = json {
                {"flight number", flight.getFlightNumber()},
                {"origin", flight.getOrigin()},
                {"destination", flight.getDestination()},
                {"departure time", (*(flight.getDeptTime())).to_string()},
                {"arrival time", (*(flight.getArrivalTime())).to_string()},
                {"aircraft type", flight.getAircraftType()},
                {"total seats", flight.getNumOfSeats()},
                {"status", flight.getStatus()},
            };
        }

        static void from_json(const json &j, Flight &flight)
        {
            try{
                flight.setFlightNumber(j.at("flight number").get<std::string>());
                flight.setOrigin(j.at("origin").get<std::string>());
                flight.setDestination(j.at("destination").get<std::string>());

                DatePtr d_ptr;
                d_ptr->from_string(j.at("departure time").get<std::string>());
                flight.setDeptTime(d_ptr);
                d_ptr->from_string(j.at("arrival time").get<std::string>());
                flight.setArrivalTime(d_ptr);

                flight.setAircraftType(j.at("aircraft type").get<std::string>());
                flight.setNumOfSeats(j.at("total seats").get<int>());
                flight.setStatus(j.at("status").get<std::string>());
            }catch(const std::exception &e) {
                std::cerr<<"Invalid json input data\n";
            }
        }
    };
}