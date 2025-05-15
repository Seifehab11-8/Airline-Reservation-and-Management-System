#include "../../header/utils/Date.hpp"
#include <iomanip>
#include <sstream>
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
DatePtr Date::processMonthYearFormat(const std::string &date)
{
    DatePtr datePtr = std::make_shared<Date>();
    std::string monthText;
    std::string yearText;
    std::stringstream dateStream(date);
    std::getline(dateStream, monthText, '-');
    std::getline(dateStream, yearText, '-');
    try{
        datePtr->month = std::stoi(monthText);
        datePtr->year = std::stoi(yearText);
    }
    catch(const std::exception &e) {
        std::cerr<<e.what()<<std::endl;
        datePtr->month = 0;
        datePtr->year = 0;
    }
    return datePtr;
}
DatePtr Date::processDateFormat(const std::string &date)
{
    DatePtr datePtr = std::make_shared<Date>();
    std::string dateText;
    std::stringstream dateStream(date);
    std::getline(dateStream, dateText, ' ');
    try{
        std::string line;
        std::stringstream dateStream(dateText);
        std::getline(dateStream, line, '-');
        datePtr->year = std::stoi(line);
    
        std::getline(dateStream, line, '-');
        datePtr->month = std::stoi(line);
    
        std::getline(dateStream, line, '-');
        datePtr->day = std::stoi(line);
    }
    catch(const std::exception &e) {
        std::cerr<<e.what()<<std::endl;
        datePtr->year = 0;
        datePtr->month = 0;
        datePtr->day = 0;
        datePtr->hour = 0;
        datePtr->min = 0;
    }
    return datePtr;
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
    std::ostringstream oss;
    oss << std::setw(4) << std::setfill('0') << year << "-"
        << std::setw(2) << std::setfill('0') << month << "-"
        << std::setw(2) << std::setfill('0') << day << " "
        << std::setw(2) << std::setfill('0') << hour << ":"
        << std::setw(2) << std::setfill('0') << min;
    return oss.str();
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
std::string Date::monthToText(int month)
{
    switch(month) {
        case 1: return "January";
        case 2: return "February";
        case 3: return "March";
        case 4: return "April";
        case 5: return "May";
        case 6: return "June";
        case 7: return "July";
        case 8: return "August";
        case 9: return "September";
        case 10: return "October";
        case 11: return "November";
        case 12: return "December";
        default: return "";
    }
}