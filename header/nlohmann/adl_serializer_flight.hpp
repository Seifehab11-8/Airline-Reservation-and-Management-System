#pragma once
#include <stdexcept>
#include <iostream>
#include "json.hpp"
#include "../flight/Flight.hpp"
#include "../utils/Date.hpp"
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
                {"FA id", flight.getFlighAttendant() ? flight.getFlighAttendant()->getID() : ""},
                {"PL id", flight.getPilot() ? flight.getPilot()->getID() : ""}
            };
        }

        static void from_json(const json &j, Flight &flight)
        {
            try {
                flight.setFlightNumber(j.value("flight number", ""));
                flight.setOrigin(j.value("origin", ""));
                flight.setDestination(j.value("destination", ""));

                auto dept_time_str = j.value("departure time", "");
                if (!dept_time_str.empty()) {
                    auto dept_ptr = std::make_shared<Date>();
                    dept_ptr->from_string(dept_time_str);
                    flight.setDeptTime(dept_ptr);
                }

                auto arr_time_str = j.value("arrival time", "");
                if (!arr_time_str.empty()) {
                    auto arr_ptr = std::make_shared<Date>();
                    arr_ptr->from_string(arr_time_str);
                    flight.setArrivalTime(arr_ptr);
                }

                flight.setAircraftType(j.value("aircraft type", ""));
                flight.setNumOfSeats(j.value("total seats", 0));
                flight.setStatus(j.value("status", ""));
                flight.setPrice(j.value("price", 0.0));
                flight.setNumOfAvailableSeats(j.value("available seats", 0));

                // Only set pilot if ID is not empty
                auto pl_id = j.value("PL id", "");
                if (!pl_id.empty()) {
                    PilotPtr pilot_ptr = std::make_shared<Pilot>();
                    pilot_ptr->setID(pl_id);
                    flight.setPilot(pilot_ptr);
                }

                // Only set flight attendant if ID is not empty
                auto fa_id = j.value("FA id", "");
                if (!fa_id.empty()) {
                    FAPtr fa_ptr = std::make_shared<FlightAttendant>();
                    fa_ptr->setID(fa_id);
                    flight.setFlightAttendant(fa_ptr);
                }
            } catch(const std::exception &e) {
                std::cerr << "Invalid json input data\n" << e.what() << std::endl;
            }
        }
    };
}