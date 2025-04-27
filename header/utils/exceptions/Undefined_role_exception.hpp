#include <stdexcept>
#include <string>

class Undefined_role_exception : public std::exception{
    private:
    std::string msg;
    public:
    Undefined_role_exception(std::string message);
    Undefined_role_exception() = delete;
    Undefined_role_exception(const Undefined_role_exception& other) = default;
    Undefined_role_exception(Undefined_role_exception&&other) = default;
    const char* what() const noexcept override;
};