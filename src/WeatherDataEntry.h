#pragma once
#include <string>

/*
    Weather Data Entry model:
    - timestamp (full date and time)
    - country
    - temperature
*/
class WeatherDataEntry
{
public:
    WeatherDataEntry(std::string timestamp, std::string country, double temperature);

    std::string getTimestamp() const;
    std::string getCountry() const;
    double getTemperature() const;

private:
    std::string timestamp;
    std::string country;
    double temperature;
};
