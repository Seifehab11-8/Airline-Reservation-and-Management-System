#ifndef IPAYMENT_HPP
#define IPAYMENT_HPP
#include <string>
#include <iostream>
#include <memory>
class IPayment
{
    public:
    IPayment() = default;
    virtual ~IPayment() = default;
    virtual void pay(double amount, double &balance) = 0;
};
#endif // IPAYMENT_HPP