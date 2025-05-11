#ifndef WRONG_PASSWORD_EXCEPTION_HPP
#define WRONG_PASSWORD_EXCEPTION_HPP
#include <exception>
#include <string>
class WrongPasswordException : public std::exception {
    private:
        std::string message;
    public:
        WrongPasswordException(const std::string& msg);
        const char* what() const noexcept override;
};
#endif // WRONG_PASSWORD_EXCEPTION_HPP