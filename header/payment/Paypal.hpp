#ifndef PAYPAL_HPP
#define PAYPAL_HPP
#include "IPayment.hpp"
class Paypal : public IPayment
{
    private:
    std::string email;
    std::string password;
    public:
    Paypal() = default;
    ~Paypal() = default;
    Paypal(const Paypal&) = default;
    Paypal(Paypal&&) = default;
    void pay(double amount, double &balance) override;
    std::string getEmail() const;
    std::string getPassword() const;
    void setEmail(const std::string& email);
    void setPassword(const std::string& password);
};
#endif