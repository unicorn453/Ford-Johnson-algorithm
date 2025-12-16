#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
    loadData("data.csv");
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
    data = other.data;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
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

void BitcoinExchange::loadData(const std::string &filename)
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
std::map<std::string, double>::const_iterator BitcoinExchange::findClosestDate(const std::string &date) const
{
    std::map<std::string, double>::const_iterator it = data.lower_bound(date);

    if (it != data.cend() && it->first == date)
        return it;

    if (it == data.cbegin())
        return data.cend();

    --it;
    return it;
}

bool BitcoinExchange::isValidDate(const std::string &date) const
{
    int year = std::stoi(date.substr(0, 4));
    int month = std::stoi(date.substr(5, 2));
    int day = std::stoi(date.substr(8, 2));

    if (year < 2008 || year > 2023)
        return false;
    if (month < 1 || month > 12)
        return false;
    if (day < 1 || day > 31)
        return false;

    return true;
}

double BitcoinExchange::getExchangeRate(const std::string &date) const
{
    std::map<std::string, double>::const_iterator it = findClosestDate(date);
    if (it == data.cend())
    {
        throw std::runtime_error("No exchange rate available for the given date or earlier.");
    }
    return it->second;
}

double BitcoinExchange::computeValue(const std::string &date, double amount) const
{
    if (!isValidDate(date))
    {
        throw std::runtime_error("Invalid date format.");
    }
    if (amount < 0)
    {
        throw std::runtime_error("Amount cannot be negative.");
    }
    double rate = getExchangeRate(date);
    return amount * rate;
}

void BitcoinExchange::readInputFile(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Could not open input file.");
    }
    std::string line;
    getline(file, line);
    while (std::getline(file, line))
    {
        size_t pipePos = line.find('|');
        if (pipePos == std::string::npos)
        {
            std::cerr << "Error: Invalid input file format: " << line << std::endl;
            continue;
        }
        std::string date = line.substr(0, pipePos);
        std::string amountStr = line.substr(pipePos + 1);
        try
        {
            double amount = std::stod(amountStr);
            double value = computeValue(date, amount);
            std::cout << date << " => " << amount << " = " << value << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error processing line: " << line << " - " << e.what() << std::endl;
        }
    }
    file.close();
}