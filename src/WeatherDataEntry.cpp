#include "WeatherDataEntry.h"

WeatherDataEntry::WeatherDataEntry(
    std::string timestamp,
    std::string country,
    double temperature
) : timestamp(timestamp), country(country), temperature(temperature)
{}

std::string WeatherDataEntry::getTimestamp() const
{
    return timestamp;
}

std::string WeatherDataEntry::getCountry() const
{
    return country;
}

double WeatherDataEntry::getTemperature() const
{
    return temperature;
}
