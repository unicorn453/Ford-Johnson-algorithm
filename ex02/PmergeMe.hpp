#include <vector>
#include <deque>
#include <string>
#include <iostream>


class PmergeMe {
public:
    PmergeMe();
    PmergeMe(std::string input);
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();

    void vectorSort();
    void dequeSort();
private:
    std::vector<int> vec;
    std::deque<int> deq;
    int binaryCompareVec(int value, int a, int b);
    int binaryCompareDeq(int value, int a, int b);
    int _comparisons;
};
