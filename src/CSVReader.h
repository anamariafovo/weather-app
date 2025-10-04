#pragma once
#include <string>
#include <vector>
#include "WeatherDataEntry.h"

/*
    Read data from CSV
*/
class CSVReader
{
public:
    // return a WeatherDataEntry vector
    static std::vector<WeatherDataEntry> readCSV(const std::string& filename);

private:
    // separate results
    static std::vector<std::string> tokenise(const std::string& csvLine, char separator);
};
