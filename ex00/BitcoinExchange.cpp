#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
    loadData("data.csv");
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
    data = other.data;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
    if (this != &other)
    {
        data = other.data;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange()
{
}

void BitcoinExchange::loadData(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Could not open data file.");
    }
    if (file.peek() == std::ifstream::traits_type::eof())
    {
        throw std::runtime_error("Data file is empty.");
    }
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line))
    {
        size_t commaPos = line.find(',');
        if (commaPos != std::string::npos)
        {
            std::string date = line.substr(0, commaPos);
            double rate = std::stod(line.substr(commaPos + 1));
            data[date] = rate;
        }
    }
    file.close();
}
std::map<std::string, double>::const_iterator BitcoinExchange::findClosestDate(const std::string& date) const
{
    std::map<std::string, double>::const_iterator it = data.lower_bound(date);

    if (it != data.cend() && it->first == date)
        return it;

    if (it == data.cbegin())
        return data.cend();

    --it;
    return it;
}

