#pragma once
#include "json.hpp"

#include "../person/Pilot.hpp"
#include "../person/FlightAttendant.hpp"
#include "../person/CrewAttendant.hpp"

namespace nlohmann 
{
    template<>
    struct adl_serializer<Pilot>
    {
        static void to_json(json &j, const Pilot &crewAttendant)
        {
            j = json {
                {"name", crewAttendant.getName()},
                {"id", crewAttendant.getID()},
                {"flying hours", crewAttendant.getFlyingHours()},
                {"role", crewAttendant.getRole()},
                {"occupation", crewAttendant.getOccupation()}
            };
        }

        static void from_json(const json &j, Pilot &crewAttendant)
        {
            try{
                crewAttendant.setName(j.at("name").get<std::string>());
                crewAttendant.setID(j.at("id").get<std::string>());
                crewAttendant.setFlyingHours(j.at("flying hours").get<double>());
                crewAttendant.setRole(j.at("role").get<std::string>());
                crewAttendant.setOccupation(j.at("occupation").get<bool>());
            }catch(const std::exception &e) {
                std::cerr<<"Invalid json input data\n";
            }
        }
    };

    template<>
    struct adl_serializer<FlightAttendant>
    {
        static void to_json(json &j, const FlightAttendant &flightAttendant)
        {
            j = json {
                {"name", flightAttendant.getName()},
                {"id", flightAttendant.getID()},
                {"flying hours", flightAttendant.getFlyingHours()},
                {"role", flightAttendant.getRole()},
                {"occupation", flightAttendant.getOccupation()}
            };
        }

        static void from_json(const json &j, FlightAttendant &flightAttendant)
        {
            try{
                flightAttendant.setName(j.at("name").get<std::string>());
                flightAttendant.setID(j.at("id").get<std::string>());
                flightAttendant.setFlyingHours(j.at("flying hours").get<double>());
                flightAttendant.setRole(j.at("role").get<std::string>());
                flightAttendant.setOccupation(j.at("occupation").get<bool>());
            }catch(const std::exception &e) {
                std::cerr<<"Invalid json input data\n";
            }
        }
    };
}
