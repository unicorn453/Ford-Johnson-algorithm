#include "PmergeMe.hpp"

PmergeMe::PmergeMe() : _comparisons(0) {}
PmergeMe::PmergeMe(std::string input) {
    size_t pos = 0;
    std::string token;
    while ((pos = input.find(" ")) != std::string::npos) {
        token = input.substr(0, pos);
        vec.push_back(std::stoi(token));
        deq.push_back(std::stoi(token));
        input.erase(0, pos + 1);
    }
    if (!input.empty()) {
        vec.push_back(std::stoi(input));
        deq.push_back(std::stoi(input));
    }
    _comparisons = 0;
}

PmergeMe::PmergeMe(const PmergeMe& other) : vec(other.vec), deq(other.deq), _comparisons(other._comparisons) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
    if (this != &other) {
        *this = other;
    }
    return *this;
}


PmergeMe::~PmergeMe() {}

int PmergeMe::binaryCompareDeq(int value, int a, int b) {
    while (a <= b) {
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

int PmergeMe::binaryCompareVec(int value, int a, int b) {
    while (a <= b) {
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


void PmergeMe::vectorSort() {
    std::vector<int> sorted;
    for (size_t i = 0; i < vec.size(); i++) {
        int pos = binaryCompareVec(vec[i], 0, sorted.size() - 1);
        sorted.insert(sorted.begin() + pos, vec[i]);
    }
    std::cout << "Sorted vector: ";
    for (size_t i = 0; i < sorted.size(); i++) {
        std::cout << sorted[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Vector comparisons: " << _comparisons << std::endl;
    _comparisons = 0;
}

void PmergeMe::dequeSort() {
    std::deque<int> sorted;
    for (size_t i = 0; i < deq.size(); i++) {
        int pos = binaryCompareDeq(deq[i], 0, sorted.size() - 1);
        sorted.insert(sorted.begin() + pos, deq[i]);
    }
    std::cout << "Sorted deque: ";
    for (size_t i = 0; i < sorted.size(); i++) {
        std::cout << sorted[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Deque comparisons: " << _comparisons << std::endl;
    _comparisons = 0;
}