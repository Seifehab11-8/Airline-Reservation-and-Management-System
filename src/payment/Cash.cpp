#include "../../header/payment/Cash.hpp"
#include <iostream>
void Cash::pay(double amount, double &balance) {
    if (amount <= 0) {
        std::cout << "Invalid amount. Payment failed." << std::endl;
        return;
    }
    else if(balance - amount < 0) {
        std::cout << "Insufficient balance. Payment failed." << std::endl;
        return;
    }
    balance -= amount;
    std::cout << "Payment of $" << amount << " made in cash. Remaining balance: $" << balance << std::endl;
}