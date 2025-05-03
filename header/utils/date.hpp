#ifndef _DATE_HPP 
#define _DATE_HPP
#include <memory>
#include <iostream>
#include <string>
#include <sstream>
class Date {
    private:
    int day;
    int month;
    int year;
    int hour;
    int min;
    friend std::ostream& operator <<(std::ostream& os, const Date & date);
    friend std::istream& operator >>(std::istream& is, Date & date);
    
    public:
    Date() = default;
    Date(const Date& other) = default;
    Date(Date &&other) = default;
};
using DatePtr = std::shared_ptr<Date>;

std::ostream& operator <<(std::ostream& os, const Date & date);
std::istream& operator >>(std::istream& is, Date & date);
#endif