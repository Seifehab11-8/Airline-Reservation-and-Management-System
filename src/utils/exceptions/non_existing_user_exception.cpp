#include "../../../header/utils/exceptions/non_existing_user_exception.hpp"

NonExistingUserException::NonExistingUserException(const std::string& msg) : message(msg) {}
const char* NonExistingUserException::what() const noexcept {
    return message.c_str();
}