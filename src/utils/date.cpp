#include "../../header/utils/Date.hpp"
#include <format>
#include <iostream>
void Date::setDate(int day, int month, int year)
{
    this->day = day;
    this->month = month;
    this->year = year;
}
void Date::setTime(int hour, int min)
{
    this->hour = hour;
    this->min = min;
}
int Date::getDay() const 
{
    return day;
}
int Date::getMonth() const 
{
    return month;
}
int Date::getYear() const 
{
    return year;
}
int Date::getHour() const 
{
    return hour;
}
int Date::getMin() const 
{
    return min;
}
std::ostream& operator <<(std::ostream& os, const Date & date)
{
    os<<date.year<<"-"<<date.month<<"-"<<date.day<<" "<<date.hour<<":"<<date.min;
    return os;
}
std::istream& operator >>(std::istream& is, Date & date)
{
    std::string dateText;
    std::string timeText;
    is>>dateText;
    is>>timeText;

    date.fullDateText = dateText + " " + timeText;
    try{
        std::string line;
        std::stringstream dateStream(dateText);
        std::getline(dateStream, line, '-');
        date.year = std::stoi(line);
    
        std::getline(dateStream, line, '-');
        date.month = std::stoi(line);
    
        std::getline(dateStream, line, '-');
        date.day = std::stoi(line);
    
        std::stringstream timeStream(timeText);
        std::getline(timeStream, line, ':');
        date.hour = std::stoi(line);
    
        std::getline(timeStream, line, ':');
        date.min = std::stoi(line);
    }
    catch(const std::exception &e) {
        std::cerr<<e.what()<<std::endl;
        date.year = 0;
        date.month = 0;
        date.day = 0;
        date.hour = 0;
        date.min = 0;
    }

    // Validate month
    if (date.month < 1 || date.month > 12) {
        std::cerr << "Invalid month: " << date.month << std::endl;
        date.month = 1; // fallback
    }

    // Validate day (simple check only)
    if (date.day < 1 || date.day > 31) {
        std::cerr << "Invalid day: " << date.day << std::endl;
        date.day = 1; // fallback
    }

    // Validate hour
    if (date.hour < 0 || date.hour > 23) {
        std::cerr << "Invalid hour: " << date.hour << std::endl;
        date.hour = 0; // fallback
    }

    // Validate minute
    if (date.min < 0 || date.min > 59) {
        std::cerr << "Invalid minute: " << date.min << std::endl;
        date.min = 0; // fallback
    }

    return is;
}
void Date::from_string(std::string str) 
{
    fullDateText = str;
    std::string dateText;
    std::string timeText;
    std::stringstream fullDateStream(str);
    std::getline(fullDateStream, dateText, ' ');
    std::getline(fullDateStream, timeText, ' ');
    try{
        std::string line;
        std::stringstream dateStream(dateText);
        std::getline(dateStream, line, '-');
        year = std::stoi(line);
    
        std::getline(dateStream, line, '-');
        month = std::stoi(line);
    
        std::getline(dateStream, line, '-');
        day = std::stoi(line);
    
        std::stringstream timeStream(timeText);
        std::getline(timeStream, line, ':');
        hour = std::stoi(line);
    
        std::getline(timeStream, line, ':');
        min = std::stoi(line);
    }
    catch(const std::exception &e) {
        std::cerr<<e.what()<<std::endl;
        year = 0;
        month = 0;
        day = 0;
        hour = 0;
        min = 0;
    }

    // Validate month
    if (month < 1 || month > 12) {
        std::cerr << "Invalid month: " << month << std::endl;
        month = 1; // fallback
    }

    // Validate day
    if (day < 1 || day > 31) {
        std::cerr << "Invalid day: " << day << std::endl;
        day = 1; // fallback
    }

    // Validate hour
    if (hour < 0 || hour > 23) {
        std::cerr << "Invalid hour: " << hour << std::endl;
        hour = 0; // fallback
    }

    // Validate minute
    if (min < 0 || min > 59) {
        std::cerr << "Invalid minute: " << min << std::endl;
        min = 0; // fallback
    }
}

std::string Date::to_string() const
{
    return fullDateText;
}
double Date::differenceHoursMin(const Date &other) const
{
    // Convert each Date's hours/minutes into total minutes
    int totalThis = (hour * 60) + min;
    int totalOther = (other.hour * 60) + other.min;

    // Calculate difference (in minutes) and convert to hours
    double diffMinutes = static_cast<double>(totalThis - totalOther);
    return diffMinutes / 60.0;
}
