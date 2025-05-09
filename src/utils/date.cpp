#include "../../header/utils/Date.hpp"
#include <format>
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
}

std::string Date::to_string() const
{
    return fullDateText;
}
