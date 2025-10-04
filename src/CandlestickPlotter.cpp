#include <iostream>
#include <algorithm>
#include <iomanip>
#include "CandlestickPlotter.h"

CandlestickPlotter::CandlestickPlotter(int height) : plotHeight(height)
{}

// convert each temperature into a value for the plot
int CandlestickPlotter::scale(double value, double min, double max)
{
    // if min = max then return 0 directly
    if (max - min == 0)
        return 0;

    // else cast the result to an int and map it to a value based on the plot's height
    return static_cast<int>(((value - min) / (max - min)) * (plotHeight - 1));
}

void CandlestickPlotter::plot(const std::vector<Candlestick>& candlesticks, const std::string& type)
{
    // fail check if vector is empty
    if (candlesticks.empty()) {
        std::cout << "No candlestick data available to plot." << std::endl;
        return;
    }

    // global min and global max for plot scaling
    // starting with the first entry of the year
    double globalMin = candlesticks[0].getLow();
    double globalMax = candlesticks[0].getHigh();

    // loop trhough years find the min and max from all years
    // to settle the beginning and end of the plot
    for (const Candlestick& candle : candlesticks)
    {
        globalMin = std::min(globalMin, candle.getLow());
        globalMax = std::max(globalMax, candle.getHigh());
    }

    // save each line of the plot in a vector
    // plot is then built line by line from top to bottom
    std::vector<std::string> plotRows(plotHeight, "");

    for (const Candlestick& candle : candlesticks)
    {
        // highest temp
        int highPos = scale(candle.getHigh(), globalMin, globalMax);
        // lowest temp
        int lowPos = scale(candle.getLow(), globalMin, globalMax);
        // opening temp
        int openPos = scale(candle.getOpen(), globalMin, globalMax);
        // closing temp
        int closePos = scale(candle.getClose(), globalMin, globalMax);

        // chossing the biggest from opening and closing to get the top of the candle
        int topBody = std::max(openPos, closePos);
        // choosing the smallest value the same way
        int bottomBody = std::min(openPos, closePos);

        // building the plot vector line by line
        // making sure all lines have 3 characters
        for (int i = plotHeight - 1; i >= 0; --i)
        {
            std::string col;

            // draw highest or lowest temperature with the same characters
            if ((i == highPos && i >= topBody) || (i == lowPos && i <= bottomBody))
                col = "━│━";
            // draw the body of the candle
            // if opening temp is lower than closing temp, then the body is green
            // if the reverse is true, then the body is red
            else if (i <= topBody && i >= bottomBody) {
                if (candle.getClose() >= candle.getOpen())
                    // green
                    col = "\033[42m █ \033[0m";
                else
                    // red
                    col = "\033[41m █ \033[0m";
            }
            // candle line
            else if (i < highPos && i > lowPos)
                // if i is still in the range of the highest and lowest values, draw the line
                col = " │ ";
            else
                // otherwise, draw a space
                col = "   ";

            // add space between columns
            plotRows[plotHeight - 1 - i] += col + " ";
        }
    }

    // print the plot from top to bottom
    for (const std::string& row : plotRows)
        std::cout << row << std::endl;

    // add years, months or days under each candlestick (just the last two digits)
    if (type == "monthly") {
        for (const Candlestick& candle : candlesticks)
            std::cout << " " << candle.getDate().substr(5, 2) << " ";
    }
    else if (type == "daily") {
        for (const Candlestick& candle : candlesticks)
            std::cout << " " << candle.getDate().substr(8, 2) << " ";
    }
    else {
        for (const Candlestick& candle : candlesticks)
            std::cout << " " << candle.getDate().substr(2, 2) << " ";
    }
    std::cout << std::endl;
}
