#include "../../header/manager/UserManager.hpp"
#include "../../header/person/User.hpp"
#include "../../header/person/Administrator.hpp"
#include "../../header/person/Passenger.hpp"
#include "../../header/person/BookingAgent.hpp"
#include "../../header/utils/JSONFileManager.hpp"
#include "../../header/utils/IOStreamHelper.hpp"
#include "../../header/factory/ConcreteUserFactory.hpp"
#include "../../header/utils/exceptions/non_existing_user_exception.hpp"
#include "../../header/utils/exceptions/wrong_password_exception.hpp"
#include <bcrypt/BCrypt.hpp>
void UserManager::create()
{
    int choice;
    std::cout << "--- Create New User ---\n"
              << "1. Administrator\n"
              << "2. Passenger\n"
              << "3. Booking Agent\n"
              << "Enter choice: ";
    choice = IOStreamHelper::InputNumeric();
    std::string username, password;
    if(choice == 1 || choice == 2 || choice == 3) {
        std::cout << "Enter Username: ";
        std::cin >> username;
        std::cout << "Enter Password: ";
        std::cin >> password;
    }

    switch (choice) {
        case 1: {
            auto userPtr = ConcreteUserFactory().create(LoginAction::UserRole::ADMIN, username, password);
            auto adminPtr = std::dynamic_pointer_cast<Administrator>(userPtr);
            if (!adminPtr) {
                std::cerr << "Failed to cast to Administrator.\n";
                return;
            }
            if (exist<Administrator>(*adminPtr, admin_file_access_ptr) != -1) {
                std::cout << "Admin Username duplication. Your Admin must have a unique Username.\n";
                return;
            }
            adminPtr->setPassword(BCrypt::generateHash(password));
            admin_file_access_ptr->append(*adminPtr);
            break;
        }

        case 2: {
            auto userPtr = ConcreteUserFactory().create(LoginAction::UserRole::PASSENGER, username, password);
            auto passengerPtr = std::dynamic_pointer_cast<Passenger>(userPtr);
            if (!passengerPtr) {
                std::cerr << "Failed to cast to Passenger.\n";
                return;
            }
            if (exist<Passenger>(*passengerPtr, passenger_file_access_ptr) != -1) {
                std::cout << "Passenger Username duplication. Your Passenger must have a unique Username.\n";
                return;
            }
            passengerPtr->setPassword(BCrypt::generateHash(password));
            std::cout << "Enter Phone Number: ";
            std::string contact;
            std::cin.ignore();
            std::getline(std::cin, contact);
            passengerPtr->setContact(contact);

            std::cout << "Enter balance: ";
            double balance;
            balance = IOStreamHelper::InputNumeric();
            passengerPtr->setBalance(balance);

            std::cout << "Enter number of Preferences: ";
            int numOfPreferences;
            numOfPreferences = IOStreamHelper::InputNumeric();
            std::cin.ignore();
            std::cout << "Enter Preferences: \n";
            for (int i = 0; i < numOfPreferences; i++) {
                std::cout << i + 1 << ". Enter Preference: ";
                std::string pref;
                std::getline(std::cin, pref);
                passengerPtr->appendPreference(pref);
            }

            std::cout << "Enter number of Old flights: ";
            int numOfOldFlights;
            numOfOldFlights = IOStreamHelper::InputNumeric();
            std::cin.ignore();
            std::cout << "Enter Old Flights in flightHistory (use Flight ID): \n";
            for (int i = 0; i < numOfOldFlights; i++) {
                std::cout << i + 1 << ". Enter Flight ID: ";
                std::string flight;
                std::getline(std::cin, flight);
                passengerPtr->appendFlight(flight);
            }
            std::cout << std::endl;
            passenger_file_access_ptr->append(*passengerPtr);
            break;
        }

        case 3: {
            auto userPtr = ConcreteUserFactory().create(LoginAction::UserRole::BOOKING_AGENT, username, password);
            auto bookingAgentPtr = std::dynamic_pointer_cast<BookingAgent>(userPtr);
            if (!bookingAgentPtr) {
                std::cerr << "Failed to cast to BookingAgent.\n";
                return;
            }
            if (exist<BookingAgent>(*bookingAgentPtr, bookingAgent_file_access_ptr) != -1) {
                std::cout << "Booking Agent Username duplication. Your Booking Agent must have a unique Username.\n";
                return;
            }
            bookingAgentPtr->setPassword(BCrypt::generateHash(password));
            bookingAgent_file_access_ptr->append(*bookingAgentPtr);
            break;
        }

        default:
            std::cout << "Invalid choice. Please try again.\n";
    }
}

void UserManager::update()
{
    int choice;
    std::cout << "--- Update User ---\n"
              << "1. Administrator\n"
              << "2. Passenger\n"
              << "3. Booking Agent\n"
              << "Enter choice: ";
    choice = IOStreamHelper::InputNumeric();
    std::string username;
    std::cout<<"Enter username of user to edit: ";
    std::cin >> username;
    UserPtr userPtr = nullptr;
    int user_index;
    switch (choice) {    
        case 1: {
            auto adminPtr = std::make_shared<Administrator>();
            adminPtr->setUsername(username);
            user_index = exist<Administrator>(*adminPtr, admin_file_access_ptr);
            if (user_index != -1) {
                userPtr = std::make_shared<Administrator>(admin_file_access_ptr->read<Administrator>(user_index));
            } else {
                userPtr = nullptr;
                std::cout << "Administrator not found.\n";
                return;
            }
            break;
        }
        case 2: {
            auto passengerPtr = std::make_shared<Passenger>();
            passengerPtr->setUsername(username);
            user_index = exist<Passenger>(*passengerPtr, passenger_file_access_ptr);
            if (user_index != -1) {
                userPtr = std::make_shared<Passenger>(passenger_file_access_ptr->read<Passenger>(user_index));
            } else {
                userPtr = nullptr;
                std::cout << "Passenger not found.\n";
                return;
            }
            break;
        }
        case 3: {
            auto bookingAgentPtr = std::make_shared<BookingAgent>();
            bookingAgentPtr->setUsername(username);
            user_index = exist<BookingAgent>(*bookingAgentPtr, bookingAgent_file_access_ptr);
            if (user_index != -1) {
                userPtr = std::make_shared<BookingAgent>(bookingAgent_file_access_ptr->read<BookingAgent>(user_index));
            } else {
                userPtr = nullptr;
                std::cout << "Booking Agent not found.\n";
                return;
            }
            break;
        }
        default:
            std::cout << "Invalid choice. Please try again.\n";
            return;
    }
    if(userPtr) {
        std::cout << "1. Enter new password \n"
                  << "2. Enter new name\n"
                  << "3. Enter new ID\n"
                  << "4. Enter new role\n";
        auto passengerPtr = std::dynamic_pointer_cast<Passenger>(userPtr);
        if (passengerPtr) {
            std::cout << "5. Enter new contact\n"
                      << "6. Enter new balance\n"
                      << "7. deposit money\n"
                      << "8. Enter new preferences\n"
                      << "9. Enter new flight history\n";
            int subChoice = IOStreamHelper::InputNumeric();
            switch (subChoice) {
                case 5: {
                    std::string newContact;
                    std::cout << "Enter new contact: ";
                    std::cin >> newContact;
                    passengerPtr->setContact(newContact);
                    break;
                }
                case 6: {
                    double newBalance;
                    std::cout << "Enter new balance: ";
                    std::cin >> newBalance;
                    passengerPtr->setBalance(newBalance);
                    break;
                }
                case 7: {
                    double deposit;
                    std::cout << "Enter amount to deposit: ";
                    std::cin >> deposit;
                    passengerPtr->setBalance(passengerPtr->getBalance() + deposit);
                    break;
                }
                case 8: {
                    std::string newPreferences;
                    std::cout << "Enter new preference: ";
                    std::cin >> newPreferences;
                    passengerPtr->appendPreference(newPreferences);
                    break;
                }
                case 9: {
                    std::string newFlightHistory;
                    std::cout << "Enter new flight history: ";
                    std::cin >> newFlightHistory;
                    passengerPtr->appendFlight(newFlightHistory);
                    break;
                }
                default:
                    std::cout << "Invalid choice.\n";
            }
        }
        switch (choice) {
            case 1: {
                std::string newPassword;
                std::cout << "Enter new password: ";
                std::cin >> newPassword;
                userPtr->setPassword(newPassword);
                break;
            }
            case 2: {
                std::string newName;
                std::cout << "Enter new name: ";
                std::cin >> newName;
                userPtr->setName(newName);
                break;
            }
            case 3: {
                std::string newID;
                std::cout << "Enter new ID: ";
                std::cin >> newID;
                userPtr->setID(newID);
                break;
            }
            case 4: {
                std::string newRole;
                std::cout << "Enter new role: ";
                std::cin >> newRole;
                userPtr->setRole(newRole);
                break;
            }
        }
        if (auto adminPtr = std::dynamic_pointer_cast<Administrator>(userPtr)) {
            admin_file_access_ptr->update(user_index, *adminPtr);
        } else if (auto passengerPtr = std::dynamic_pointer_cast<Passenger>(userPtr)) {
            passenger_file_access_ptr->update(user_index, *passengerPtr);
        } else if (auto bookingAgentPtr = std::dynamic_pointer_cast<BookingAgent>(userPtr)) {
            bookingAgent_file_access_ptr->update(user_index, *bookingAgentPtr);
        }
        std::cout << "User updated successfully.\n";
    }
}

void UserManager::_delete()
{
    int choice;
    std::cout << "--- Create New User ---\n"
              << "1. Administrator\n"
              << "2. Passenger\n"
              << "3. Booking Agent\n"
              << "Enter choice: ";
    choice = IOStreamHelper::InputNumeric();
    std::string username, password;
    if(choice == 1 || choice == 2 || choice == 3) {
        std::cout << "Enter Username: ";
        std::cin >> username;
    }
    else {
        std::cout<<"Invalid Choice\n";
        return;
    }
    int user_index = -1;
    switch(choice) {
        case 1:
        {
            auto admin_ptr = std::make_shared<Administrator>();
            admin_ptr->setUsername(username);
            user_index = exist<Administrator>(*admin_ptr, admin_file_access_ptr);
            if(user_index != -1){
                admin_file_access_ptr->erase(user_index);
                std::cout<<"Admin is Sucessfully Deleted\n";
            }
            else{
                std::cout<<"Admin not found\n";
            }
        }
        break;
        case 2:
        {
            auto passenger_ptr = std::make_shared<Passenger>();
            passenger_ptr->setUsername(username);
            user_index = exist<Passenger>(*passenger_ptr, passenger_file_access_ptr);
            if(user_index != -1){
                passenger_file_access_ptr->erase(user_index);
                std::cout<<"Passenger is Sucessfully Deleted\n";
            }
            else{
                std::cout<<"Passenger not found\n";
            }
        }
        break;
        case 3:
        {
            auto booking_agent_ptr = std::make_shared<BookingAgent>();
            booking_agent_ptr->setUsername(username);
            user_index = exist<BookingAgent>(*booking_agent_ptr, bookingAgent_file_access_ptr);
            if(user_index != -1){
                bookingAgent_file_access_ptr->erase(user_index);
                std::cout<<"Booking Agent  is Sucessfully Deleted\n";
            }
            else{
                std::cout<<"Booking Agent not found\n";
            }
        }
        break;
    }

}

void UserManager::view()
{
    int choice;
    std::cout << "--- View User ---\n"
              << "1. Administrator\n"
              << "2. Passenger\n"
              << "3. Booking Agent\n"
              << "Enter choice: ";
    choice = IOStreamHelper::InputNumeric();
    switch (choice) {
        case 1: {
            auto adminList = admin_file_access_ptr->getArray<Administrator>();
            for (const auto& admin : adminList) {
                std::cout << admin << "\n";
            }
            break;
        }
        case 2: {
            auto passengerList = passenger_file_access_ptr->getArray<Passenger>();
            for (const auto& passenger : passengerList) {
                std::cout << passenger << "\n";
            }
            break;
        }
        case 3: {
            auto bookingAgentList = bookingAgent_file_access_ptr->getArray<BookingAgent>();
            for (const auto& bookingAgent : bookingAgentList) {
                std::cout << bookingAgent << "\n";
            }
            break;
        }
        default:
            std::cout << "Invalid choice. Please try again.\n";
    }
    std::cout << "Press any key to continue...\n";
    std::cin.ignore();
    std::cin.get();
    std::cout << "\n";
    std::cout << "Returning ...\n";
    std::cout << "\n";
    std::cout << "----------------------------------------\n";
}

UserPtr UserManager::login(std::string username, std::string password, LoginAction::UserRole role)
{
    switch (role) {
        case LoginAction::UserRole::ADMIN: {
            auto adminList = admin_file_access_ptr->getArray<Administrator>();
            for (const auto& admin : adminList) {
                if (admin.getUsername() == username) {
                    if(BCrypt::validatePassword(password, admin.getPassword())){
                        std::cout << "Login successful.\n";
                        return std::make_shared<Administrator>(admin);
                    }
                    else{
                        throw WrongPasswordException("Wrong Password");
                    }
                }
            }
            break;
        }
        case LoginAction::UserRole::PASSENGER: {
            auto passengerList = passenger_file_access_ptr->getArray<Passenger>();
            for (const auto& passenger : passengerList) {
                if (passenger.getUsername() == username) {
                    if(BCrypt::validatePassword(password, passenger.getPassword())){
                        std::cout << "Login successful.\n";
                        return std::make_shared<Passenger>(passenger);
                    }
                    else{
                        throw WrongPasswordException("Wrong Password");
                    }
                }
            }
            break;
        }
        case LoginAction::UserRole::BOOKING_AGENT: {
            auto bookingAgentList = bookingAgent_file_access_ptr->getArray<BookingAgent>();
            for (const auto& bookingAgent : bookingAgentList) {
                if (bookingAgent.getUsername() == username) {
                    if(BCrypt::validatePassword(password, bookingAgent.getPassword())){
                        std::cout << "Login successful.\n";
                        return std::make_shared<BookingAgent>(bookingAgent);
                    }
                    else{
                        throw WrongPasswordException("Wrong Password");
                    }
                }
            }
            break;
        }
        default:
            std::cout << "Invalid role. Please try again.\n";
    }
    throw NonExistingUserException("User not found");
}

int UserManager::viewMenu()
{
    int choice;
    std::cout<<"--- Manage Users ---\n"
                "1. Add User\n"
                "2. Update User\n"
                "3. Delete User\n"
                "4. View Users\n"
                "5. Back to Main Menu\n"
                "Enter choice: ";
    choice = IOStreamHelper::InputNumeric();
    return choice;
}