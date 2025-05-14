#ifndef _DATE_HPP 
#define _DATE_HPP
#include <memory>
#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>
class Date {
    private:
    int day;
    int month;
    int year;
    int hour;
    int min;
    std::string fullDateText;
    friend std::ostream& operator <<(std::ostream& os, const Date & date);
    friend std::istream& operator >>(std::istream& is, Date & date);
    
    public:
    Date() = default;
    Date(const Date& other) = default;
    Date(Date &&other) = default;
    void from_string(std::string str);
    std::string to_string() const;
    void setDate(int day, int month, int year);
    void setTime(int hour, int min);
    int getDay() const ;
    int getMonth() const ;
    int getYear() const ;
    int getHour() const ;
    int getMin() const ;
    double differenceHoursMin(const Date &other) const;

};
using DatePtr = std::shared_ptr<Date>;

std::ostream& operator <<(std::ostream& os, const Date & date);
std::istream& operator >>(std::istream& is, Date & date);
#endif