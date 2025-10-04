#include <iostream>
#include <vector>
#include "TemperaturePredictor.h"

void TemperaturePredictor::predict(
    const std::vector<Candlestick>& data,
    int startYear,
    int endYear,
    int predictYear
) {
    std::vector<int> years;
    std::vector<double> temps;

    // get the data from the training interval
    for (const Candlestick& candle : data) {
        int year = std::stoi(candle.getDate());
        if (year >= startYear && year <= endYear) {
            years.push_back(year);
            temps.push_back(candle.getClose());
        }
    }

    if (years.size() < 2) {
        std::cout << "Not enough data for prediction.\n";
        return;
    }

    // linear regression for prediciton: temp = a * year + b
    double sumYears = 0, sumTemp = 0, sumYearsTemp = 0, sumYearsSquared = 0;
    int n = years.size();

    // adding all the necessary sums for the formula
    for (int i = 0; i < n; ++i) {
        // sum of all years
        sumYears += years[i];
        //sum of all closing temperatures
        sumTemp += temps[i];
        // sum up years and closing temperature
        sumYearsTemp += years[i] * temps[i];
        // sum squared years 
        sumYearsSquared += years[i] * years[i];
    }

    // starting to calculate the elements of the formula
    double denominator = n * sumYearsSquared - sumYears * sumYears;
    // check if denominator is 0 in order to prevent division by 0
    if (denominator == 0) {
        std::cout << "Regression failed (division by zero).\n";
        return;
    }

    // find the slope (yearly temperature change)
    double a = (n * sumYearsTemp - sumYears * sumTemp) / denominator;
    // find intercept
    double b = (sumTemp - a * sumYears) / n;

    // get the prediciton for chosen year
    double predictedTemp = a * predictYear + b;

    std::cout << "Predicted average temperature for year " << predictYear << " is " << predictedTemp << " degrees." << std::endl;
}
