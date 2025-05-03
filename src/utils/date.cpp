#include "../../header/utils/Date.hpp"

std::ostream& operator <<(std::ostream& os, const Date & date)
{
    os<<date.year<<"-"<<date.month<<"-"<<date.day<<" "<<date.hour<<":"<<date.min<<std::endl;
    return os;
}
std::istream& operator >>(std::istream& is, Date & date)
{
    std::string dateText;
    std::string timeText;
    is>>dateText;
    is>>timeText;
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
    return is;
}