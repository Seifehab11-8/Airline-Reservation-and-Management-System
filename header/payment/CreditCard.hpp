#ifndef CREDITCARD_HPP
#define CREDITCARD_HPP

#include "IPayment.hpp"

class CreditCard : public IPayment
{
    private:
    std::string cardNumber;
    std::string cardHolderName;
    std::string cvv;
    public:
    CreditCard() = default;
    ~CreditCard() = default;
    CreditCard(const CreditCard&) = default;
    CreditCard(CreditCard&&) = default;
    void pay(double amount, double &balance) override;
    std::string getCardNumber() const;
    std::string getCardHolderName() const;
    std::string getCVV() const;
    void setCardNumber(const std::string& cardNumber);
    void setCardHolderName(const std::string& cardHolderName);
    void setCVV(const std::string& cvv);
};

#endif