#ifndef CASH_HPP
#define CASH_HPP
#include "IPayment.hpp"
class Cash : public IPayment
{
    public:
    Cash() = default;
    ~Cash() = default;
    Cash(const Cash&) = default;
    Cash(Cash&&) = default;
    void pay(double amount, double &balance) override;
};

#endif