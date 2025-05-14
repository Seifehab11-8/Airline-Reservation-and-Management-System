#include "../../header/payment/Paypal.hpp"
#include <iostream>
#include <string>
void Paypal::pay(double amount, double &balance) {
    if (amount <= 0) {
        std::cout << "Invalid amount. Payment failed." << std::endl;
        return;
    }
    else if(balance - amount < 0) {
        std::cout << "Insufficient balance. Payment failed." << std::endl;
        return;
    }
    std::cout << "Enter Payment Details eg. mike.paypal@example.com: ";
    std::cin >> email;
    std::cout << "Enter Password: ";
    std::cin >> password;
    balance -= amount;
    std::cout << "Payment of $" << amount << " made using PayPal. Remaining balance: $" << balance << std::endl;
}
std::string Paypal::getEmail() const {
    return email;
}
std::string Paypal::getPassword() const {
    return password;
}
void Paypal::setEmail(const std::string& email) {
    this->email = email;
}
void Paypal::setPassword(const std::string& password) {
    this->password = password;
}