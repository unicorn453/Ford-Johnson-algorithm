#include <map>
#include <string>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <algorithm>


class BitcoinExchange
{
private:
    std::map<std::string, double> data;
    void loadData(const std::string& filename);
    std::map<std::string, double>::const_iterator findClosestDate(const std::string& date) const;
    bool isValidDate(const std::string& date) const;
    double getExchangeRate(const std::string& date) const;
public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);
    ~BitcoinExchange();
    double computeValue(const std::string& date, double amount) const;
};
