#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}
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
}

PmergeMe::PmergeMe(const PmergeMe& other) : vec(other.vec), deq(other.deq) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
    if (this != &other) {
        *this = other;
    }
    return *this;
}