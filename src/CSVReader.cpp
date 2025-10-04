#include <fstream>
#include <sstream>
#include <iostream>
#include "CSVReader.h"

// similar to OrderBookEntry returned in the Merklerex project
std::vector<WeatherDataEntry> CSVReader::readCSV(const std::string& filename)
{
    std::vector<WeatherDataEntry> data;
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return data;
    }

    // read the first line (header)
    std::getline(file, line);
    // tokenise headers based on separator
    std::vector<std::string> headers = tokenise(line, ',');

    // get the other data
    while (std::getline(file, line)) {
        std::vector<std::string> tokens = tokenise(line, ',');

        // if a missing entry is found continue and skip that line
        if (tokens.size() != headers.size())
            continue;

        // save timestamp data (first entry)
        std::string timestamp = tokens[0];

        // save the rest of the fields
        for (size_t i = 1; i < tokens.size(); ++i) {
            try {
                double temperature = std::stod(tokens[i]);
                std::string country = headers[i];

                // create weather data entry with timestamp, country, and temperature
                WeatherDataEntry entry(timestamp, country, temperature);
                data.push_back(entry);
            } catch (const std::exception& e) {
                std::cout << "CSVReader::readCSV bad data!" << std::endl;
            }
        }
    }

    // return a vector of WeatherDataEntries
    return data;
}

std::vector<std::string> CSVReader::tokenise(const std::string& csvLine, char separator)
{
    std::vector<std::string> tokens;
    std::string token;
    signed int start, end;

    start = csvLine.find_first_not_of(separator, 0);

    do {
        end = csvLine.find_first_of(separator, start);
        if (start == csvLine.length() || start == end) break;
        if (end >= 0) token = csvLine.substr(start, end - start);
        else token = csvLine.substr(start, csvLine.length() - start);
        tokens.push_back(token);
        start = end + 1;
    } while (end > 0);

    return tokens;
}
