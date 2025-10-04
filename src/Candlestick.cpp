#include "Candlestick.h"

Candlestick::Candlestick(std::string date, double open, double high, double low, double close)
    : date(date), open(open), high(high), low(low), close(close)
{}

std::string Candlestick::getDate() const
{
    return date;
}

double Candlestick::getOpen() const
{
    return open;
}

double Candlestick::getHigh() const
{
    return high;
}

double Candlestick::getLow() const
{
    return low;
}

double Candlestick::getClose() const
{
    return close;
}
