#include "../../header/payment/CreditCard.hpp"
#include <iostream>
#include <string>
void CreditCard::pay(double amount, double &balance) {
    if (amount <= 0) {
        std::cout << "Invalid amount. Payment failed." << std::endl;
        return;
    }
    else if(balance - amount < 0) {
        std::cout << "Insufficient balance. Payment failed." << std::endl;
        return;
    }
    //enter card details
    std::cout << "Enter card number eg.(XXXX-XXXX-XXXX-1234): ";
    std::cin >> cardNumber;
    std::cout << "Enter card holder name: ";
    std::cin.ignore();
    std::getline(std::cin, cardHolderName);
    std::cout << "Enter CVV: ";
    std::cin >> cvv;

    balance -= amount;
    std::cout << "Payment of $" << amount << " made using credit card. Remaining balance: $" << balance << std::endl;
}
std::string CreditCard::getCardNumber() const {
    return cardNumber;
}

std::string CreditCard::getCardHolderName() const {
    return cardHolderName;
}

std::string CreditCard::getCVV() const {
    return cvv;
}

void CreditCard::setCardNumber(const std::string& cardNumber) {
    this->cardNumber = cardNumber;
}
void CreditCard::setCardHolderName(const std::string& cardHolderName) {
    this->cardHolderName = cardHolderName;
}
void CreditCard::setCVV(const std::string& cvv) {
    this->cvv = cvv;
}