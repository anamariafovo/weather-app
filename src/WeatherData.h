#pragma once
#include <string>
#include <vector>
#include "WeatherDataEntry.h"
#include "CSVReader.h"

/*
    Similar to an interface between WeatherApp and the data read by the CSV reader
    Wrapper for WeatherDataEntry
*/
class WeatherData
{
public:
    // constructor with dynamic filename
    WeatherData(const std::string& filename);
    const std::vector<WeatherDataEntry>& getData() const;

private:
    std::vector<WeatherDataEntry> data;
};
