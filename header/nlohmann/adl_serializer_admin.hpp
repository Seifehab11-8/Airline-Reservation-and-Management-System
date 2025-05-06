#include <stdexcept>
#include <iostream>
#include "json.hpp"
#include "../person/Administrator.hpp"
namespace nlohmann 
{
    template<>
    struct adl_serializer<Administrator>
    {
        static void to_json(json &j, const Administrator &admin)
        {
            j = json {
                {"name", admin.getName()},
                {"id", admin.getID()},
                {"username", admin.getUsername()},
                {"password", admin.getPassword()},
                {"role", admin.getRole()},
                {"login status", admin.getLoginStatus()},
            };
        }

        static void from_json(const json &j, Administrator &admin)
        {
            try{
                admin.setName(j.at("name").get<std::string>());
                admin.setID(j.at("id").get<std::string>());
                admin.setUsername(j.at("username").get<std::string>());
                admin.setPassword(j.at("password").get<std::string>());
                admin.setRole(j.at("role").get<std::string>());
                admin.setLoginStatus(j.at("login status").get<bool>());
            }catch(const std::exception &e) {
                std::cerr<<"Invalid json input data\n";
            }
        }
    };
}