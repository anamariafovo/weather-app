#pragma once
#include <string>
#include "WeatherData.h"
#include "Candlestick.h"

/*
    Main controller: prints menu, handle input, triggers candlestick computation
*/
class WeatherApp
{
public:
    WeatherApp(const std::string& filename);
    void init();

private:
    int getUserOption();
    void printMenu();
    int getTimeIntervalOption();
    void handleUserInput(int input);
    void showYearlyData();
    void showMonthlyData();
    void showDailyData();
    void plotYearlyData();
    void plotYearlyCandlestick();
    void plotMonthlyCandlestick();
    void plotDailyCandlestick();
    void filterByYearRange();
    void filterByMonthRange();
    void filterByDayRange();
    void printYearlyData(const std::vector<Candlestick>& candlesticks);
    void printMonthlyData(const std::vector<Candlestick>& candlesticks);
    void printDailyData(const std::vector<Candlestick>& candlesticks);
    void filterByYearlyTemperatureRange();
    void filterByMonthlyTemperatureRange();
    void filterByDailyTemperatureRange();
    void predictTemperature();
    void printHelp();
    WeatherData weatherData;
};
