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
                {"price", flight.getPrice()},
                {"available seats", flight.getNumOfAvailableSeats()},
                {"FA id", flight.getFlighAttendant()->getID()},
                {"PL id", flight.getPilot()->getID()}
            };
        }

        static void from_json(const json &j, Flight &flight)
        {
            try{
                flight.setFlightNumber(j.at("flight number").get<std::string>());
                flight.setOrigin(j.at("origin").get<std::string>());
                flight.setDestination(j.at("destination").get<std::string>());

                DatePtr dept_ptr = std::make_shared<Date>();
                dept_ptr->from_string(j.at("departure time").get<std::string>());
                flight.setDeptTime(dept_ptr);

                DatePtr arr_ptr = std::make_shared<Date>();
                arr_ptr->from_string(j.at("arrival time").get<std::string>());
                flight.setArrivalTime(arr_ptr);

                flight.setAircraftType(j.at("aircraft type").get<std::string>());
                flight.setNumOfSeats(j.at("total seats").get<int>());
                flight.setStatus(j.at("status").get<std::string>());
                flight.setPrice(j.at("price").get<double>());

                PilotPtr pilot_ptr = std::make_shared<Pilot>();
                pilot_ptr->setID(j.at("PL id").get<std::string>());
                flight.setPilot(pilot_ptr);

                FAPtr fa_ptr = std::make_shared<FlightAttendant>();
                fa_ptr->setID(j.at("FA id").get<std::string>());
                flight.setFlightAttendant(fa_ptr);
                flight.setNumOfAvailableSeats(j.at("available seats").get<int>());
            }catch(const std::exception &e) {
                std::cerr<<"Invalid json input data\n";
            }
        }
    };
}