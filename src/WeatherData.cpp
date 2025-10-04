#include "WeatherData.h"

WeatherData::WeatherData(const std::string& filename)
{
    data = CSVReader::readCSV(filename);
}

const std::vector<WeatherDataEntry>& WeatherData::getData() const
{
    return data;
}
