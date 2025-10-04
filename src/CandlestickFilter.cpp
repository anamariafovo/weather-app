#include <iostream>
#include "CandlestickFilter.h"

std::vector<Candlestick> CandlestickFilter::filterByDateRange(
    const std::vector<Candlestick>& data,
    const std::string& type,
    int start,
    int end
) {
    std::vector<Candlestick> filtered;
    
    // loop through all candles
    for (const Candlestick& candle : data) {
        if (type == "monthly") {
            // get month as integer
            int month = std::stoi(candle.getDate().substr(5, 2));
            // filter by month
            if (month >= start && month <= end)
                filtered.push_back(candle);
        }
        else if (type == "daily") {
            // get day as integer
            int day = std::stoi(candle.getDate().substr(8, 2));
            // filter by day
            if (day >= start && day <= end)
                filtered.push_back(candle);
        } 
        else {
            // get year as integer
            int year = std::stoi(candle.getDate().substr(0, 4));
            // filter by year
            if (year >= start && year <= end)
                filtered.push_back(candle);
        }
    }
    return filtered;
}

std::vector<Candlestick> CandlestickFilter::filterByTemperatureRange(const std::vector<Candlestick>& data, double high, double low)
{
    std::vector<Candlestick> filtered;

    // loop through all candles
    for (const Candlestick& candle : data) {
        // filter by low and high
        if (candle.getHigh() <= high && candle.getLow() >= low)
            filtered.push_back(candle);
    }

    return filtered;
}
