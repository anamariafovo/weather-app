#pragma once
#include "Candlestick.h"
#include <vector>
#include <string>

/*
    Plot creation for low, high, open and close temperature data
*/
class CandlestickPlotter
{
public:
    // optional constructor for setting the plot's height
    CandlestickPlotter(int height = 10);

    // drawing function
    void plot(const std::vector<Candlestick>& candlesticks, const std::string& type = "yearly");

private:
    int plotHeight;
    // scale values to adapt them for the plot's height
    int scale(double value, double min, double max);
};
