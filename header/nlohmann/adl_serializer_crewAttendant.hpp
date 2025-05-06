#include "json.hpp"

#include "../person/Pilot.hpp"
#include "../person/FlightAttendant.hpp"
#include "../person/CrewAttendant.hpp"

namespace nlohmann 
{
    template<>
    struct adl_serializer<Pilot>
    {
        static void to_json(json &j, const CrewAttendant &crewAttendant)
        {
            j = json {
                {"name", crewAttendant.getName()},
                {"id", crewAttendant.getID()},
                {"flying hours", crewAttendant.getFlyingHours()},
                {"role", "Pilot"}
            };
        }

        static void from_json(const json &j, CrewAttendant &crewAttendant)
        {
            try{
                crewAttendant.setName(j.at("name").get<std::string>());
                crewAttendant.setID(j.at("id").get<std::string>());
                crewAttendant.setFlyingHours(j.at("flying hours").get<double>());
                crewAttendant.setRole("Pilot");
            }catch(const std::exception &e) {
                std::cerr<<"Invalid json input data\n";
            }
        }
    };

    template<>
    struct adl_serializer<FlightAttendant>
    {
        static void to_json(json &j, const CrewAttendant &crewAttendant)
        {
            j = json {
                {"name", crewAttendant.getName()},
                {"id", crewAttendant.getID()},
                {"flying hours", crewAttendant.getFlyingHours()},
                {"role", "Flight Attendant"}
            };
        }

        static void from_json(const json &j, CrewAttendant &crewAttendant)
        {
            try{
                crewAttendant.setName(j.at("name").get<std::string>());
                crewAttendant.setID(j.at("id").get<std::string>());
                crewAttendant.setFlyingHours(j.at("flying hours").get<double>());
                crewAttendant.setRole("Flight Attendant");
            }catch(const std::exception &e) {
                std::cerr<<"Invalid json input data\n";
            }
        }
    };
}
