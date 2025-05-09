#pragma once
#include <stdexcept>
#include <iostream>
#include "json.hpp"
#include "../person/Passenger.hpp"
namespace nlohmann 
{
    template<>
    struct adl_serializer<Passenger>
    {
        static void to_json(json &j, const Passenger &passenger)
        {
            j = json {
                {"name", passenger.getName()},
                {"id", passenger.getID()},
                {"username", passenger.getUsername()},
                {"password", passenger.getPassword()},
                {"role", passenger.getRole()},
                {"login status", passenger.getLoginStatus()},
                {"contact", passenger.getContact()},
                {"preference", passenger.getPreference()},
                {"flight history", passenger.getFlightHistory()},
                {"notification", passenger.getNotifications()},
            };
        }

        static void from_json(const json &j, Passenger &passenger)
        {
            try{
                passenger.setName(j.at("name").get<std::string>());
                passenger.setID(j.at("id").get<std::string>());
                passenger.setUsername(j.at("username").get<std::string>());
                passenger.setPassword(j.at("password").get<std::string>());
                passenger.setRole(j.at("role").get<std::string>());
                passenger.setLoginStatus(j.at("login status").get<bool>());
                passenger.setContact(j.at("contact").get<std::string>());
                passenger.setPerference(j.at("preference").get<std::vector<std::string>>());
                passenger.setFlightHistory(j.at("flight history").get<std::vector<std::string>>());
                passenger.setNotifications(j.at("notification").get<std::vector<std::string>>());
            }catch(const std::exception &e) {
                std::cerr<<"Invalid JSON input data\n";
            }
        }
    };
}