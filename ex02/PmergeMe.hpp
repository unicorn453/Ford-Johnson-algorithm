#include <vector>
#include <deque>


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
   
};