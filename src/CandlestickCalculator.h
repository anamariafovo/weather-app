#pragma once
#include <vector>
#include <string>
#include <map>
#include "WeatherDataEntry.h"
#include "Candlestick.h"

/*
    Computes candlesticks
*/
class CandlestickCalculator
{
public:
    static std::vector<Candlestick> computeYearlyCandlesticks(
        const std::vector<WeatherDataEntry>& data,
        const std::string& country
    );
    static std::vector<Candlestick> computeMonthlyCandlesticks(
        const std::vector<WeatherDataEntry>& data,
        const std::string& country,
        const std::string& year
    );
    static std::vector<Candlestick> computeDailyCandlesticks(
        const std::vector<WeatherDataEntry>& data,
        const std::string& country,
        const std::string& year,
        const std::string& month
    );
    static std::vector<Candlestick> getCandlesticks(const std::map<std::string, std::vector<double>>& data);
};
