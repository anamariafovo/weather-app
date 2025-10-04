#pragma once
#include "Candlestick.h"
#include <vector>

class TemperaturePredictor
{
public:
    static void predict(const std::vector<Candlestick>& data, int startYear, int endYear, int predictYear);
};
