#pragma once
#include "Candlestick.h"
#include <vector>

class CandlestickFilter
{
public:
    static std::vector<Candlestick> filterByDateRange(
        const std::vector<Candlestick>& data,
        const std::string& type,
        int startYear,
        int endYear
    );
    static std::vector<Candlestick> filterByTemperatureRange(
        const std::vector<Candlestick>& data,
        double high,
        double low
    );
};
