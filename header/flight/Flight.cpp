#include "Flight.hpp"

bool Flight::operator==(const Flight &other)
{
    return (flightNumber == other.flightNumber);
}