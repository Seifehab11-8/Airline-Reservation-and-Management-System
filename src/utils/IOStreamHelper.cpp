#include "../../header/utils/IOStreamHelper.hpp"
#include <iostream>

int IOStreamHelper::InputNumeric()
{
    int userInput;
    while (!(std::cin >> userInput)) { // Check if input is invalid
        std::cin.clear(); // Clear error flag
        std::cin.ignore(1000, '\n'); // Ignore incorrect input upto 1000 char or delimiter /n
        std::cout << "Invalid input! Please enter an integer: ";
    }
    return userInput;
}
