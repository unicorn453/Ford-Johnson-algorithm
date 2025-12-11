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
    // Pair* createPairsVec();
    void mergeSortVec();
    Pair* createPairsDeq(std::deque<int> &arr, int size);
    std::vector<int> vec;
    std::deque<int> deq;
    int binaryCompareVec(int value, int a, int b);
    int binaryCompareDeq(int value, int a, int b);
    int _comparisons;
};
