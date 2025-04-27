#include "../../../header/utils/exceptions/Undefined_role_exception.hpp"

Undefined_role_exception::Undefined_role_exception(std::string message):msg(message)
{
}

const char* Undefined_role_exception::what() const noexcept{
    return msg.c_str();
}