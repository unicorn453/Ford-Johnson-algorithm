#include <vector>
#include <deque>
#include <string>
#include <iostream>
#include <cmath>

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
    size_t findPairedPosition(size_t pendIndex);
    void rearrangeBlocksByLastElement(size_t pairSize);
    void sortRemainingElements(int valueOdd);
    std::vector<int> vec;
    std::deque<int> deq;
    std::vector<int> pend;
    std::vector<int> smalls;
    std::vector<int> bigs;
    size_t binaryCompareVec(int value, size_t a, size_t b);
    int binaryCompareDeq(int value, int a, int b);
    void insertJacobsthal(
        size_t sizePairs
    );
    int _comparisons;
    std::vector<int> pairMax;  // Store paired values for pending elements
};
