#include <vector>
#include <deque>
#include <string>
#include <iostream>
#include <cmath>
#include <climits>

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
    std::vector<int> getVec() const { return vec; }
    std::deque<int> getDeq() const { return deq; }
private:
    // Vector methods
    void generatePairsVec(size_t pairSize);
    void mergeSortVec();
    size_t findPairedPositionVec(size_t pendIndex);
    void rearrangeBlocksByLastElementVec(size_t pairSize);
    void sortRemainingElementsVec(int valueOdd);
    void insertJacobsthalVec(size_t sizePairs);
    size_t binaryCompareVec(int value, size_t a, size_t b);

    // Deque methods
    void generatePairsDeq(size_t pairSize);
    void mergeSortDeq();
    size_t findPairedPositionDeq(size_t pendIndex);
    void rearrangeBlocksByLastElementDeq(size_t pairSize);
    void sortRemainingElementsDeq(int valueOdd);
    void insertJacobsthalDeq(size_t sizePairs);
    size_t binaryCompareDeq(int value, size_t a, size_t b, const std::deque<int>& container);

    std::vector<int> vec;
    std::deque<int> deq;
    std::vector<int> pend;
    std::vector<int> smalls;
    std::vector<int> bigs;
    std::deque<int> pendDeq;
    std::deque<int> smallsDeq;
    std::deque<int> bigsDeq;
    
    int _comparisons;
    int _comparisonsDeq;
    std::vector<int> pairMax;  // Store paired values for pending elements
    std::deque<int> pairMaxDeq;
};
