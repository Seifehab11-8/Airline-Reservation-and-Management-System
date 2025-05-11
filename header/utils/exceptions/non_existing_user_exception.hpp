#ifndef NON_EXISTING_USER_EXCEPTION_HPP
#define NON_EXISTING_USER_EXCEPTION_HPP
#include <exception>
#include <string>
class NonExistingUserException : public std::exception {
    private:
        std::string message;
    public:
        NonExistingUserException(const std::string& msg);
        const char* what() const noexcept override;
};
#endif // NON_EXISTING_USER_EXCEPTION_HPP