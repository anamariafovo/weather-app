#pragma once
#include <string>

/*
    Candlestick model:
    - date
    - open
    - high
    - low
    -close
*/
class Candlestick
{
public:
    Candlestick(std::string date, double open, double high, double low, double close);

    std::string getDate() const;
    double getOpen() const;
    double getHigh() const;
    double getLow() const;
    double getClose() const;

private:
    std::string date;
    double open;
    double high;
    double low;
    double close;
};
