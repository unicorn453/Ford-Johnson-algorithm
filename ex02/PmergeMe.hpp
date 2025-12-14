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
    void rearrangeBlocksByLastElement(size_t pairSize);
    std::vector<int> vec;
    std::deque<int> deq;
    std::vector<int> pend;
    std::vector<int> smalls;
    std::vector<int> bigs;
    size_t binaryCompareVec(int value, int a, int b);
    int binaryCompareDeq(int value, int a, int b);
    void insertJacobsthal(
        size_t sizePairs
    );
    int _comparisons;
};
