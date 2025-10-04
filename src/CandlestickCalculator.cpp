#include <map>
#include <algorithm>
#include <numeric>
#include "CandlestickCalculator.h"

std::vector<Candlestick> CandlestickCalculator::computeYearlyCandlesticks(
    const std::vector<WeatherDataEntry>& data, const std::string& country
) {
    // computation returns a vector of Candlesticks
    std::vector<Candlestick> result;
    // store temperatures grouped by year
    std::map<std::string, std::vector<double>> yearToTemps;

    // loop through the entries (timestamp, country, temperature)
    for (const WeatherDataEntry& entry : data) {
        // skip all the entries that don't have the chosen country
        if (entry.getCountry() != country)
            continue;

        // remove timestamp and date from the year with substr(0, 4)
        std::string year = entry.getTimestamp().substr(0, 4);
        // group all the temperatures for the same year
        yearToTemps[year].push_back(entry.getTemperature());
    }

    return getCandlesticks(yearToTemps);
}

std::vector<Candlestick> CandlestickCalculator::computeMonthlyCandlesticks(
    const std::vector<WeatherDataEntry>& data, const std::string& country, const std::string& year
) {
    // store temperatures grouped by month
    std::map<std::string, std::vector<double>> monthToTemps;

    // loop through the entries (timestamp, country, temperature)
    for (const WeatherDataEntry& entry : data) {
        // skip all the entries that don't have the chosen country
        if (entry.getCountry() != country)
            continue;

        // get the year and month from the timestamp (YYYY-MM-DD)
        std::string entryYear = entry.getTimestamp().substr(0, 4);
        std::string entryMonth = entry.getTimestamp().substr(5, 2);
        
        // get only data for the selected year
        if (entryYear != year)
            continue;
        
        // group all the temperatures for the same year and month
        std::string month = entryYear + "-" + entryMonth;
        monthToTemps[month].push_back(entry.getTemperature());
    }

    return getCandlesticks(monthToTemps);
}

std::vector<Candlestick> CandlestickCalculator::computeDailyCandlesticks(
    const std::vector<WeatherDataEntry>& data, const std::string& country, const std::string& year, const std::string& month
) {
    // Computation returns a vector of Candlesticks
    std::vector<Candlestick> result;
    std::map<std::string, std::vector<double>> dayToTemps;  // To store temperatures grouped by day

    // Loop through the entries (timestamp, country, temperature)
    for (const WeatherDataEntry& entry : data) {
        // skip all the entries that don't have the chosen country
        if (entry.getCountry() != country)
            continue;

        // get the year, month, and day from the timestamp (YYYY-MM-DD)
        std::string entryYear = entry.getTimestamp().substr(0, 4);
        std::string entryMonth = entry.getTimestamp().substr(5, 2);
        std::string entryDay = entry.getTimestamp().substr(8, 2);
        
        // get only data for the selected year and month
        if (entryYear != year || entryMonth != month)
            continue;
        
        // group all temperatures for the same day
        std::string yearMonthDay = entryYear + "-" + entryMonth + "-" + entryDay;  // "YYYY-MM-DD"
        dayToTemps[yearMonthDay].push_back(entry.getTemperature());
    }

    return getCandlesticks(dayToTemps);
}

std::vector<Candlestick> CandlestickCalculator::getCandlesticks(const std::map<std::string, std::vector<double>>& data) 
{
    std::vector<Candlestick> candlesticks;
    double previousClose = 0.0;

    for (const auto& pair : data) {
        const std::string& date = pair.first;
        const auto& temps = pair.second;

        // get the highest temperature for the month
        double high = *std::max_element(temps.begin(), temps.end());
        
        // get the lowest temperature for the month
        double low = *std::min_element(temps.begin(), temps.end());
        
        // calculate the average temperature (close) for the month
        double close = std::accumulate(temps.begin(), temps.end(), 0.0) / temps.size();
        
        // the opening temperature for the month is the closing temperature of the previous month
        double open = previousClose;

        // create a candlestick object for this month
        Candlestick candle(date, open, high, low, close);

        // add it to the result vector
        candlesticks.push_back(candle);

        // update the previous close for the next iteration
        previousClose = close;
    }

    return candlesticks;
}
