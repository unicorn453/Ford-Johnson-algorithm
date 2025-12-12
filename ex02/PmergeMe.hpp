#include <vector>
#include <deque>
#include <string>
#include <iostream>

typedef struct {
    int *a;
    int *b;
    int iterations;
    int pair_size;
} Pair;


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
    void generatePairsVec(size_t pairSize);
    void mergeSortVec();
    std::vector<int> vec;
    std::deque<int> deq;
    std::vector<int> pend;
    std::vector<int> smalls;
    std::vector<int> bigs;
    size_t binaryCompareVec(int value, int a, int b);
    int binaryCompareDeq(int value, int a, int b);
    std::vector<int> insertJacobsthal(
        const std::vector<int>& bigs,
        const std::vector<int>& smalls);
    int _comparisons;
};
