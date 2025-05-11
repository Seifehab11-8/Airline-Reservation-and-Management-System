#include "../../../header/utils/exceptions/wrong_password_exception.hpp"
WrongPasswordException::WrongPasswordException(const std::string& msg) : message(msg) {}
const char* WrongPasswordException::what() const noexcept {
    return message.c_str();
}