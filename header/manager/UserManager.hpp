#ifndef _USER_MANAGER_HPP_
#define _USER_MANAGER_HPP_
#include <iostream>
#include <string>
#include <memory>
#include "IManager.hpp"
#include "../utils/Constants.hpp"

class UserManager : public IManager {
    private:
        Json_file_ptr admin_file_access_ptr = std::make_shared<JSONFileManager>(ADMIN_FILE_PATH);
        Json_file_ptr passenger_file_access_ptr = std::make_shared<JSONFileManager>(PASSENGER_FILE_PATH);
        Json_file_ptr bookingAgent_file_access_ptr = std::make_shared<JSONFileManager>(BOOKINGAGENT_FILE_PATH);
    public:
        UserManager() = default;
        UserManager(const UserManager &other) = default;
        UserManager(UserManager && other) = default;
        void create() override;
        void update() override;
        void _delete() override;
        void view() override;
        int viewMenu() override;
        UserPtr login(std::string username, std::string password, LoginAction::UserRole role);
};
#endif