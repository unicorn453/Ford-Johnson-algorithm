#include "PmergeMe.hpp"
#include <algorithm>

PmergeMe::PmergeMe() : _comparisons(0) {}
PmergeMe::PmergeMe(std::string input)
{
    size_t pos = 0;
    std::string token;
    while ((pos = input.find(" ")) != std::string::npos)
    {
        token = input.substr(0, pos);
        vec.push_back(std::stoi(token));
        deq.push_back(std::stoi(token));
        input.erase(0, pos + 1);
    }
    if (!input.empty())
    {
        vec.push_back(std::stoi(input));
        deq.push_back(std::stoi(input));
    }
    _comparisons = 0;
}

PmergeMe::PmergeMe(const PmergeMe &other) : vec(other.vec), deq(other.deq), _comparisons(other._comparisons) {}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        *this = other;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

int PmergeMe::binaryCompareDeq(int value, int a, int b)
{
    while (a <= b)
    {
        int mid = a + (b - a) / 2;
        if (deq[mid] == value)
        {
            return mid + 1;
            _comparisons++;
        }
        else if (deq[mid] < value)
        {
            _comparisons++;
            a = mid + 1;
        }
        else
        {
            b = mid - 1;
            _comparisons++;
        }
    }
    return a;
}

int PmergeMe::binaryCompareVec(int value, int a, int b)
{
    while (a <= b)
    {
        int mid = a + (b - a) / 2;
        if (vec[mid] == value)
        {
            return mid + 1;
            _comparisons++;
        }
        else if (vec[mid] < value)
        {
            _comparisons++;
            a = mid + 1;
        }
        else
        {
            b = mid - 1;
            _comparisons++;
        }
    }
    return a;
}

size_t find_max_iterations(size_t size)
{

    size_t iterations = 0;
    while (size > 1)
    {
        size = size / 2;
        iterations++;
    }
    return iterations;
}

void PmergeMe::mergeSortVec()
{

    size_t size = vec.size();
    size_t pends = size % 4;
    size_t maxPairsElements = size - pends;

    size_t max_iterations = find_max_iterations(maxPairsElements);

    for (size_t i = 0; i < maxPairsElements + 1; i += 2)
    {
        if (vec[i] > vec[i + 1])
        {
            std::swap(vec[i], vec[i + 1]);
        }
    }

    for (size_t i = 1; i < max_iterations; i++)
    {
        size_t pair_size = 1 << i; // 2^i
        for (size_t j = 1; j < maxPairsElements + 1; j += pair_size)
        {
            size_t a = j;
            size_t b = j + pair_size;

            size_t left = a;
            size_t right = b;
            if (vec[left] < vec[right])
            {
                std::rotate(vec.begin(),
                            vec.begin() + left + 1,
                            vec.begin() + right + 1);
            }
            _comparisons++;
        }
    }
}

void PmergeMe::vectorSort()
{
    // std::vector<int> sorted;

    // for (size_t i = 0; i < vec.size(); i++) {
    //     int pos = binaryCompareVec(vec[i], 0, sorted.size() - 1);
    //     sorted.insert(sorted.begin() + pos, vec[i]);
    // }
    mergeSortVec();
    std::cout << "Sorted vector: ";
    for (size_t i = 0; i < vec.size(); i++)
    {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Vector comparisons: " << _comparisons << std::endl;
    _comparisons = 0;
}

void PmergeMe::dequeSort()
{
    std::deque<int> sorted;
    for (size_t i = 0; i < deq.size(); i++)
    {
        int pos = binaryCompareDeq(deq[i], 0, sorted.size() - 1);
        sorted.insert(sorted.begin() + pos, deq[i]);
    }
    std::cout << "Sorted deque: ";
    for (size_t i = 0; i < sorted.size(); i++)
    {
        std::cout << sorted[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Deque comparisons: " << _comparisons << std::endl;
    _comparisons = 0;
}