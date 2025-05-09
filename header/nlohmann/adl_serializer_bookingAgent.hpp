#pragma once
#include <stdexcept>
#include <iostream>
#include "json.hpp"
#include "../person/BookingAgent.hpp"
namespace nlohmann 
{
    template<>
    struct adl_serializer<BookingAgent>
    {
        static void to_json(json &j, const BookingAgent &bookingAgent)
        {
            j = json {
                {"name", bookingAgent.getName()},
                {"id", bookingAgent.getID()},
                {"username", bookingAgent.getUsername()},
                {"password", bookingAgent.getPassword()},
                {"role", bookingAgent.getRole()},
                {"login status", bookingAgent.getLoginStatus()},
            };
        }

        static void from_json(const json &j, BookingAgent &bookingAgent)
        {
            try{
                bookingAgent.setName(j.at("name").get<std::string>());
                bookingAgent.setID(j.at("id").get<std::string>());
                bookingAgent.setUsername(j.at("username").get<std::string>());
                bookingAgent.setPassword(j.at("password").get<std::string>());
                bookingAgent.setRole(j.at("role").get<std::string>());
                bookingAgent.setLoginStatus(j.at("login status").get<bool>());
            }catch(const std::exception &e) {
                std::cerr<<"Invalid json input data\n";
            }
        }
    };
}