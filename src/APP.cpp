#include "../header/APP.hpp"
#include "../header/person/User.hpp"
#include "../header/factory/ConcreteUserFactory.hpp"
#include <iostream>
#include "../header/utils/IOStreamHelper.hpp"
#include "../header/utils/Configs.hpp"
#include "../header/utils/exceptions/Undefined_role_exception.hpp"
#include "../header/manager/UserManager.hpp"
#include "../header/utils/exceptions/non_existing_user_exception.hpp"
#include "../header/utils/exceptions/wrong_password_exception.hpp"

using CreatorPtr = std::shared_ptr<ConcreteUserFactory>;

void APP::start() 
{
    auto userManagerPtr = std::make_shared<UserManager>();
    int choice;
    std::string username, password;
    while(true) {
        std::cout<<"----------------------------------------\n";
        std::cout<<"Welcome to Airline Reservation and Management System\n";
        std::cout<<"1. Register\n"
                 <<"2. Login\n"
                 <<"3. Exit\n"
                 <<"Enter Choice: ";
        choice = IOStreamHelper::InputNumeric();
        if(choice == 3) {
            std::cout<<"Exiting the application...\n";
            return;
        }

        
        if(choice == 1) {
            userManagerPtr->create();
        }
        else if (choice == 2){
            try{
                std::cout<<"Please select your role\n"
                "1. Administrator\n"
                "2. Booking Agent\n"
                "3. Passenger\n"
                "Enter choice: ";
                choice = IOStreamHelper::InputNumeric();
                LoginAction::UserRole ur = static_cast<LoginAction::UserRole>(choice);
                if (ur != LoginAction::UserRole::ADMIN 
                    && ur != LoginAction::UserRole::PASSENGER 
                    && ur != LoginAction::UserRole::BOOKING_AGENT) {
                    throw Undefined_role_exception("Invalid role selected.");
                }
                std::cin.ignore();//to free the buffer
                std::cout<<"---- Login ----"<<std::endl;
                std::cout<<"Username : ";
                std::getline(std::cin, username);
                std::cout<<"Password : ";
                //get(c) to capture white spaces
                for(char c; std::cin.get(c) && c != '\n';) {
                    password += c;
                    std::cout << '*';
                }
                std::cout << std::endl;

                UserPtr u_ptr = userManagerPtr->login(username, password, ur);
                u_ptr->viewMainMenu();
            }
            catch(const Undefined_role_exception& e) {
                std::cerr<<e.what()<<std::endl;
                return;
            }
            catch(const NonExistingUserException& e) {
                std::cerr<<e.what()<<std::endl;
            }
            catch(const WrongPasswordException& e) {
                std::cerr<<e.what()<<std::endl;
            }
            catch(const std::exception& e) {
                std::cerr<<"An error occurred: "<<e.what()<<std::endl;
            }
        }
        else {
            std::cout<<"Invalid choice. Please try again.\n";
        }
    }
}