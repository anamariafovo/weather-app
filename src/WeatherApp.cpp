#include <iostream>
#include <iomanip>
#include "WeatherApp.h"
#include "CandlestickCalculator.h"
#include "CandlestickPlotter.h"
#include "CandlestickFilter.h"
#include "TemperaturePredictor.h"

WeatherApp::WeatherApp(const std::string& filename)
    : weatherData(filename)
{}

void WeatherApp::init()
{
    std::cout << "WELCOME TO THE WEATHER APP!" << std::endl;

    while (true) {
        printMenu();
        int input = getUserOption();
        if (input == 0) {
            std::cout << "Goodbye!" << std::endl;
            break;
        }
        handleUserInput(input);
    }
}

void WeatherApp::printMenu()
{
    // print all the options
    std::cout << " " << std::endl;
    std::cout << "=============== Weather App Menu ==============" << std::endl;
    std::cout << "1: Compute temperature data" << std::endl;
    std::cout << "2: Plot candlesticks" << std::endl;
    std::cout << "3: Filter by date range" << std::endl;
    std::cout << "4: Filter by temperature range" << std::endl;
    std::cout << "5: Predict temperature for a future year" << std::endl;
    std::cout << "6: Print help " << std::endl;
    std::cout << "0: Exit" << std::endl;
}

int WeatherApp::getUserOption()
{
    int userOption = 0;
    std::cout << "Enter option: ";
    std::cin >> userOption;

    if (userOption < 0 || userOption > 6) {
        std::cout << "Invalid option!" << std::endl;
        return -1;
    }
    std::cout << "You chose: " << userOption << std::endl;
    return userOption;
}

int WeatherApp::getTimeIntervalOption()
{
    int timeOption = 0;

    std::cout << " " << std::endl;
    std::cout << "Choose the time interval:" << std::endl;
    std::cout << "1: Yearly" << std::endl;
    std::cout << "2: Monthly" << std::endl;
    std::cout << "3: Daily" << std::endl;
    std::cout << "Enter your option (1-3): ";
    std::cin >> timeOption;

    if (timeOption < 1 || timeOption > 3) {
        std::cout << "Invalid option! Returning to main menu.\n";
        return -1;
    }

    return timeOption;
}

void WeatherApp::handleUserInput(int input)
{
    // call the necessary functionality based on the user's input
    if (input >= 1 && input <= 4) {
        // check if user wants yearly, monthly or daily data
        int timeOption = getTimeIntervalOption();
        if (timeOption == -1) return;

        if (input == 1) {
            if (timeOption == 1) showYearlyData();
            else if (timeOption == 2) showMonthlyData();
            else showDailyData();
        }
        else if (input == 2) {
            if (timeOption == 1) plotYearlyCandlestick();
            else if (timeOption == 2) plotMonthlyCandlestick();
            else plotDailyCandlestick();
        }
        else if (input == 3) {
            if (timeOption == 1) filterByYearRange();
            else if (timeOption == 2) filterByMonthRange();
            else filterByDayRange();
        }
        else if (input == 4) {
            if (timeOption == 1) filterByYearlyTemperatureRange();
            else if (timeOption == 2) filterByMonthlyTemperatureRange();
            else filterByDailyTemperatureRange();
        }
    }

    else if (input == 5) {
        predictTemperature();
    }

    else if (input == 6) {
        printHelp();
    }

    else {
        std::cout << "Please choose a valid option (0 to 6): " << std::endl;
        return;
    }
}

void WeatherApp::showYearlyData()
{
    std::string country;
    std::cout << "Enter country name (e.g. GB_temperature): ";
    std::cin >> country;

    // get a vector of yearly data for the chosen country
    // read CSV data with weatherData.getData()
    // reading the CSV returns a WeatherDataEntry vector (timestamp, country, temperature)
    std::vector<Candlestick> candlesticks = CandlestickCalculator::computeYearlyCandlesticks(weatherData.getData(), country);

    printYearlyData(candlesticks);
}

void WeatherApp::showMonthlyData()
{
    std::string country;
    std::string year;

    std::cout << "Enter country name (e.g. GB_temperature): ";
    std::cin >> country;

    // get the chosen year from the user
    std::cout << "Enter the year (1980 to 2019): ";
    std::cin >> year;

    // get monthly data back for the chosen country and year
    std::vector<Candlestick> candlesticks = CandlestickCalculator::computeMonthlyCandlesticks(weatherData.getData(), country, year);

    printMonthlyData(candlesticks);
}

void WeatherApp::showDailyData()
{
    std::string country;
    std::string year;
    std::string month;

    std::cout << "Enter country name (e.g. GB_temperature): ";
    std::cin >> country;

    // get the year from the user
    std::cout << "Enter the year (1980 to 2019): ";
    std::cin >> year;

    // get the month from the user
    std::cout << "Enter the month (01 to 12): ";
    std::cin >> month;

    // get the data for the chosen country, year and month
    std::vector<Candlestick> candlesticks = CandlestickCalculator::computeDailyCandlesticks(weatherData.getData(), country, year, month);

    printDailyData(candlesticks);
}

void WeatherApp::plotYearlyCandlestick()
{
    std::string country;
    std::cout << "Enter country name (e.g. GB_temperature): ";
    std::cin >> country;

    std::vector<Candlestick> candlesticks = CandlestickCalculator::computeYearlyCandlesticks(weatherData.getData(), country);

    // create a plotter object with height 20
    CandlestickPlotter plotter(20);
    // plot all years
    plotter.plot(candlesticks);
}

void WeatherApp::plotMonthlyCandlestick()
{
    std::string country;
    std::string year;

    std::cout << "Enter country name (e.g. GB_temperature): ";
    std::cin >> country;

    // get the year from the user
    std::cout << "Enter the year (1980 to 2019): ";
    std::cin >> year;

    std::vector<Candlestick> candlesticks = CandlestickCalculator::computeMonthlyCandlesticks(weatherData.getData(), country, year);

    // create a plotter object with height 20
    CandlestickPlotter plotter(20);
    // plot all years
    plotter.plot(candlesticks, "monthly");
}

void WeatherApp::plotDailyCandlestick()
{
    std::string country;
    std::string year;
    std::string month;

    std::cout << "Enter country name (e.g. GB_temperature): ";
    std::cin >> country;

    // get the year from the user
    std::cout << "Enter the year (1980 to 2019): ";
    std::cin >> year;

    // get the month from the user
    std::cout << "Enter the month (01 to 12): ";
    std::cin >> month;

    std::vector<Candlestick> candlesticks = CandlestickCalculator::computeDailyCandlesticks(weatherData.getData(), country, year, month);

    // create a plotter object with height 20
    CandlestickPlotter plotter(20);
    // plot all years
    plotter.plot(candlesticks, "daily");
}

void WeatherApp::filterByYearRange()
{
    std::string country;
    int startYear, endYear, option;

    std::cout << "Choose plot (1) or raw data (2): ";
    std::cin >> option;

    std::cout << "Enter country name (e.g. GB_temperature): ";
    std::cin >> country;

    std::cout << "Enter start year (1980 to 2019): ";
    std::cin >> startYear;

    std::cout << "Enter end year (1980 to 2019): ";
    std::cin >> endYear;

    if (endYear < startYear) {
        std::cout << "End year cannot be earlier than start year! Returning to main menu." << std::endl;
        return;
    }

    std::vector<Candlestick> candlesticks = CandlestickCalculator::computeYearlyCandlesticks(weatherData.getData(), country);
    
    // filter candlesticks by chosen years
    std::vector<Candlestick> filtered = CandlestickFilter::filterByDateRange(candlesticks, "yearly", startYear, endYear);

    if (option == 1) {
        // create a plot object with height 20
        CandlestickPlotter plotter(30);
        // plot only filtered items
        plotter.plot(filtered);
    } 
    else if (option == 2) {
        printYearlyData(filtered);
    }
    else {
        std::cout << "Invalid option! Returning to main menu." << std::endl;
    }
}

void WeatherApp::filterByMonthRange()
{
    std::string country, year;
    int startMonth, endMonth, option;

    std::cout << "Choose plot (1) or raw data (2): ";
    std::cin >> option;

    std::cout << "Enter country name (e.g. GB_temperature): ";
    std::cin >> country;

    std::cout << "Enter the year (1980 to 2019): ";
    std::cin >> year;

    std::cout << "Enter start month (01 to 12): ";
    std::cin >> startMonth;

    std::cout << "Enter end month (01 to 12): ";
    std::cin >> endMonth;

    if (endMonth < startMonth) {
        std::cout << "End month cannot be earlier than start month! Returning to main menu." << std::endl;
        return;
    }

    std::vector<Candlestick> candlesticks = CandlestickCalculator::computeMonthlyCandlesticks(weatherData.getData(), country, year);
    
    // filter candlesticks by chosen years
    std::vector<Candlestick> filtered = CandlestickFilter::filterByDateRange(candlesticks, "monthly", startMonth, endMonth);

    if (option == 1) {
        // create a plot object with height 20
        CandlestickPlotter plotter(20);
        // plot only filtered items
        plotter.plot(filtered, "monthly");
    }
    else if (option == 2) {
        printMonthlyData(filtered);
    }
    else {
        std::cout << "Invalid option! Returning to main menu." << std::endl;
    }
}

void WeatherApp::filterByDayRange()
{
    std::string country, year, month;
    int startDay, endDay, option;

    std::cout << "Choose plot (1) or raw data (2): ";
    std::cin >> option;

    std::cout << "Enter country name (e.g. GB_temperature): ";
    std::cin >> country;

    std::cout << "Enter the year (1980 to 2019): ";
    std::cin >> year;

    std::cout << "Enter month (01 to 12): ";
    std::cin >> month;

    std::cout << "Enter start day (e.g. 03): ";
    std::cin >> startDay;

    std::cout << "Enter end day (e.g. 09): ";
    std::cin >> endDay;

    if (endDay < startDay) {
        std::cout << "End day cannot be earlier than start day! Returning to main menu." << std::endl;
        return;
    }

    std::vector<Candlestick> candlesticks = CandlestickCalculator::computeDailyCandlesticks(weatherData.getData(), country, year, month);
    
    // filter candlesticks by chosen years
    std::vector<Candlestick> filtered = CandlestickFilter::filterByDateRange(candlesticks, "daily", startDay, endDay);

    if (option == 1) {
        // create a plot object with height 20
        CandlestickPlotter plotter(20);
        // plot only filtered items
        plotter.plot(filtered, "daily");
    }
    else if (option == 2) {
        printDailyData(filtered);
    }
    else {
        std::cout << "Invalid option! Returning to main menu." << std::endl;
    }
}

void WeatherApp::printYearlyData(const std::vector<Candlestick>& candlesticks)
{
    if (candlesticks.empty()) {
        std::cout << "No data available for the selected dates." << std::endl;
        return;
    }

    // print data headers
    std::cout << "" << std::endl;
    std::cout << "Year |\tOpen\tHigh\tLow\tClose" << std::endl;
    std::cout << "" << std::endl;

    for (const Candlestick& candle : candlesticks) {
        // print data and add tab after all except for the last one
        std::cout << candle.getDate() << " |" << "\t"
                  << std::fixed << std::setprecision(2) << candle.getOpen() << "\t"
                  << std::fixed << std::setprecision(2) << candle.getHigh() << "\t"
                  << std::fixed << std::setprecision(2) << candle.getLow() << "\t"
                  << std::fixed << std::setprecision(2) << candle.getClose() << std::endl;
    }
}

void WeatherApp::printMonthlyData(const std::vector<Candlestick>& candlesticks)
{
    if (candlesticks.empty()) {
        std::cout << "No data available for the selected dates." << std::endl;
        return;
    }

    // print data headers
    std::cout << "" << std::endl;
    std::cout << "Month   |\tOpen\tHigh\tLow\tClose" << std::endl;
    std::cout << "" << std::endl;

    for (const Candlestick& candle : candlesticks) {
        // print data and add tab after all except for the last one
        std::cout << candle.getDate() << " |" << "\t"
                  << std::fixed << std::setprecision(2) << candle.getOpen() << "\t"
                  << std::fixed << std::setprecision(2) << candle.getHigh() << "\t"
                  << std::fixed << std::setprecision(2) << candle.getLow() << "\t"
                  << std::fixed << std::setprecision(2) << candle.getClose() << std::endl;
    }
}

void WeatherApp::printDailyData(const std::vector<Candlestick>& candlesticks)
{
    if (candlesticks.empty()) {
        std::cout << "No data available for the selected dates." << std::endl;
        return;
    }

    // headers
    std::cout << "" << std::endl;
    std::cout << "Date       |\tOpen\tHigh\tLow\tClose" << std::endl;
    std::cout << "" << std::endl;

    for (const Candlestick& candle : candlesticks) {
        // print all daily data for the chosen month
        std::cout << candle.getDate() << " |" << "\t"
                  << std::fixed << std::setprecision(2) << candle.getOpen() << "\t"
                  << std::fixed << std::setprecision(2) << candle.getHigh() << "\t"
                  << std::fixed << std::setprecision(2) << candle.getLow() << "\t"
                  << std::fixed << std::setprecision(2) << candle.getClose() << std::endl;
    }
}

void WeatherApp::filterByYearlyTemperatureRange()
{
    std::string country;
    double low, high, option;

    std::cout << "Choose plot (1) or raw data (2): ";
    std::cin >> option;

    std::cout << "Enter country name (e.g. GB_temperature): ";
    std::cin >> country;

    std::cout << "Enter maximum temperature: ";
    std::cin >> high;

    std::cout << "Enter minimum temperature: ";
    std::cin >> low;

    std::vector<Candlestick> candlesticks = CandlestickCalculator::computeYearlyCandlesticks(weatherData.getData(), country);
    // filter based on temperatures
    std::vector<Candlestick> filtered = CandlestickFilter::filterByTemperatureRange(candlesticks, high, low);

    if (option == 1) {
        // create a plot object with height 20
        CandlestickPlotter plotter(20);
        // plot only filtered items
        plotter.plot(filtered);
    }
    else if (option == 2) {
        printYearlyData(filtered);
    }
    else {
        std::cout << "Invalid option! Returning to main menu." << std::endl;
    }
}

void WeatherApp::filterByMonthlyTemperatureRange()
{
    std::string country, year;
    double low, high, option;

    std::cout << "Choose plot (1) or raw data (2): ";
    std::cin >> option;

    std::cout << "Enter country name (e.g. GB_temperature): ";
    std::cin >> country;

    std::cout << "Enter the year (1980 to 2019): ";
    std::cin >> year;

    std::cout << "Enter maximum temperature: ";
    std::cin >> high;

    std::cout << "Enter minimum temperature: ";
    std::cin >> low;

    std::vector<Candlestick> candlesticks = CandlestickCalculator::computeMonthlyCandlesticks(weatherData.getData(), country, year);
    // filter based on temperatures
    std::vector<Candlestick> filtered = CandlestickFilter::filterByTemperatureRange(candlesticks, high, low);

    if (option == 1) {
        // create a plot object with height 20
        CandlestickPlotter plotter(20);
        // plot only filtered items
        plotter.plot(filtered, "monthly");
    }
    else if (option == 2) {
        printMonthlyData(filtered);
    }
    else {
        std::cout << "Invalid option! Returning to main menu." << std::endl;
    }
}

void WeatherApp::filterByDailyTemperatureRange()
{
    std::string country, year, month;
    double low, high, option;

    std::cout << "Choose plot (1) or raw data (2): ";
    std::cin >> option;

    std::cout << "Enter country name (e.g. GB_temperature): ";
    std::cin >> country;

    std::cout << "Enter the year (1980 to 2019): ";
    std::cin >> year;

    std::cout << "Enter month (01 to 12): ";
    std::cin >> month;

    std::cout << "Enter maximum temperature: ";
    std::cin >> high;

    std::cout << "Enter minimum temperature: ";
    std::cin >> low;

    std::vector<Candlestick> candlesticks = CandlestickCalculator::computeDailyCandlesticks(weatherData.getData(), country, year, month);
    // filter based on temperatures
    std::vector<Candlestick> filtered = CandlestickFilter::filterByTemperatureRange(candlesticks, high, low);

    if (option == 1) {
        // create a plot object with height 20
        CandlestickPlotter plotter(20);
        // plot only filtered items
        plotter.plot(filtered, "daily");
    }
    else if (option == 2) {
        printDailyData(filtered);
    }
    else {
        std::cout << "Invalid option! Returning to main menu." << std::endl;
    }
}

void WeatherApp::predictTemperature()
{
    std::string country;
    int startYear, endYear, predictYear;

    std::cout << "Enter country name (e.g. GB_temperature): ";
    std::cin >> country;

    std::cout << "Enter start year for training: ";
    std::cin >> startYear;

    std::cout << "Enter end year for training: ";
    std::cin >> endYear;

    std::cout << "Enter year to predict: ";
    std::cin >> predictYear;

    std::vector<Candlestick> candlesticks = CandlestickCalculator::computeYearlyCandlesticks(weatherData.getData(), country);
    // call the predictor to predict the temperature (using linear regression)
    TemperaturePredictor::predict(candlesticks, startYear, endYear, predictYear);
}

void WeatherApp::printHelp()
{
    std::cout << "=============== Instructions ==============" << std::endl;
    std::cout << "This application analyzes weather data and provides a minimum, maximum, opening and closing temperature for each each from 1980 to 2019." << std::endl;
    std::cout << "There are multiple functionalities available: " << std::endl;
    std::cout << "1: Compute yearly, monthly or daily temperature data for a specific country." << std::endl;
    std::cout << "2: Plot candlesticks for all yearly, monthly or daily temperatures for a specific country." << std::endl;
    std::cout << "3: Filter candlesticks by a date range." << std::endl;
    std::cout << "4: Filter candlesticks by a temperature range (min, max)." << std::endl;
    std::cout << "5: Predict the temperature for a specific year using linear regression." << std::endl;
    std::cout << "0: Exit the application." << std::endl;
}
