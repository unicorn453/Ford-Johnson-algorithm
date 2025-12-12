#include "PmergeMe.hpp"
#include <algorithm>

PmergeMe::PmergeMe() : _comparisons(0)
{
    bigs.clear();
    smalls.clear();
    pend.clear();
}

PmergeMe::PmergeMe(std::string input) : _comparisons(0)
{
    bigs.clear();
    smalls.clear();
    pend.clear();

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
}

PmergeMe::PmergeMe(const PmergeMe &other) : vec(other.vec), deq(other.deq), pend(other.pend), smalls(other.smalls), bigs(other.bigs), _comparisons(other._comparisons) {}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        vec = other.vec;
        deq = other.deq;
        _comparisons = other._comparisons;
        bigs = other.bigs;
        smalls = other.smalls;
        pend = other.pend;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

int PmergeMe::binaryCompareDeq(int value, int a, int b)
{
    while (a <= b)
    {
        int mid = a + (b - a) / 2;
        _comparisons++;
        if (deq[mid] == value)
        {
            return mid + 1;
        }
        else if (deq[mid] < value)
        {
            a = mid + 1;
        }
        else
        {
            b = mid - 1;
        }
    }
    return a;
}

size_t PmergeMe::binaryCompareVec(int value, int a, int b)
{
    while (a <= b)
    {
        int mid = a + (b - a) / 2;
        _comparisons++;
        if (vec[mid] == value)
        {
            return mid + 1;
        }
        else if (vec[mid] < value)
        {
            a = mid + 1;
        }
        else
        {
            b = mid - 1;
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

std::vector<size_t> generateJacobsthal(size_t n)
{
    std::vector<size_t> jac;
    if (n == 0)
        return jac;

    size_t j0 = 1;
    size_t j1 = 3;

    jac.push_back(1);
    if (j1 <= n)
        jac.push_back(j1);

    while (true)
    {
        size_t next = j1 + 2 * j0; // J(n) = J(n-1) + 2J(n-2)

        if (next > n)
            break;

        jac.push_back(next);

        j0 = j1;
        j1 = next;
    }
    return jac;
}

std::vector<int> PmergeMe::insertJacobsthal(
    const std::vector<int> &bigs,
    const std::vector<int> &smalls)
{
    size_t numPairs = smalls.size();
    if (numPairs == 0)
        return bigs;

    std::vector<size_t> jac = generateJacobsthal(numPairs);

    // main chain starts with sorted bigs
    std::vector<int> mainChain = bigs;

    // Insert first small at the beginning
    mainChain.insert(mainChain.begin(), smalls[0]);

    // Keep track of which elements we've inserted
    std::vector<bool> inserted(numPairs, false);
    inserted[0] = true;

    // Insert the rest in Jacobsthal order
    for (size_t i = 1; i < jac.size() && jac[i] <= numPairs; ++i)
    {
        size_t jacobIndex = jac[i] - 1; // Convert to 0-based index
        size_t prevJacob = jac[i - 1] - 1;

        // Insert elements in reverse order from current Jacobsthal number down to previous + 1
        for (size_t k = jacobIndex; k > prevJacob; k--)
        {
            if (k < numPairs && !inserted[k])
            {
                int val = smalls[k];

                // binary search for insertion position with upper bound limit
                size_t left = 0;
                size_t right = k + 1; // limit search range
                if (right > mainChain.size())
                    right = mainChain.size();

                while (left < right)
                {
                    size_t mid = (left + right) / 2;
                    _comparisons++;
                    if (mainChain[mid] < val)
                        left = mid + 1;
                    else
                        right = mid;
                }
                mainChain.insert(mainChain.begin() + left, val);
                inserted[k] = true;
            }
        }
    }

    pend.clear();
    for (size_t i = 0; i < numPairs; ++i)
    {
        if (!inserted[i])
        {
            pend.push_back(smalls[i]);
        }
    }

    return mainChain;
}

void PmergeMe::mergeSortVec()
{
    size_t size = vec.size();
    size_t pends = size % 2;
    size_t maxPairsElements = size - pends;

    for (size_t i = 0; i < maxPairsElements; i += 2)
    {
        if (vec[i] > vec[i + 1])
            std::swap(vec[i], vec[i + 1]);
    }

    bigs.clear();
    smalls.clear();
    pend.clear();

    for (size_t i = 0; i < maxPairsElements; i += 2)
    {
        smalls.push_back(vec[i]);
        bigs.push_back(vec[i + 1]);
    }

    size_t numPairs = bigs.size();
    size_t max_iterations = find_max_iterations(numPairs);

    for (size_t level = 0; level < max_iterations; level++)
    {
        size_t block = 1 << level;
        std::cout << "block size: " << block << std::endl;
        std::cout << "Level " << level + 1 << std::endl;

        for (size_t i = 0; i + 2 * block <= numPairs; i += 2 * block)
        {
            size_t L = i;
            size_t R = i + block;

            if (bigs[L + block - 1] > bigs[R + block - 1])
            {
                for (size_t i = L; i < R; i++)
                {
                    std::swap(smalls[i], smalls[i + (R - L)]);
                    std::swap(bigs[i], bigs[i + (R - L)]);
                }
            }
            _comparisons++;
        }

        //         for (size_t i = 0; i < numPairs; i += 2 * block)
        // {
        //     size_t L = i;
        //     size_t R = i + block;

        //     if (R >= numPairs)
        //         break;

        //     size_t end = std::min(i + 2 * block, numPairs);

        //     size_t leftEnd  = R - 1;
        //     size_t rightEnd = end - 1;

        //     if (leftEnd - L != rightEnd - R)
        //         continue;

        //     _comparisons++;

        //     if (bigs[leftEnd] > bigs[rightEnd])
        //     {

        //         std::rotate(bigs.begin() + L, bigs.begin() + R, bigs.begin() + end);
        //         std::rotate(smalls.begin() + L, smalls.begin() + R, smalls.begin() + end);
        //     }
        // }
    }

    vec.clear();
    for (size_t i = 0; i < smalls.size(); i++)
    {
        vec.push_back(smalls[i]);
        vec.push_back(bigs[i]);
    }

    std::cout << std::endl;
}

void PmergeMe::generatePairsVec(size_t pairSize)
{
    bigs.clear();
    smalls.clear();

    size_t size = vec.size();
    size_t blockSize = pairSize * 2;

    size_t pendsCount = size % blockSize;
    size_t maxBlockElements = size - pendsCount;

    for (size_t i = 0; i < maxBlockElements; i += blockSize)
    {

        for (size_t s = 0; s < pairSize; s++)
            smalls.push_back(vec[i + s]);

        for (size_t b = 0; b < pairSize; b++)
            bigs.push_back(vec[i + pairSize + b]);
    }

}

void PmergeMe::vectorSort()
{
    if (vec.size() <= 1)
        return;

    mergeSortVec();

    for (size_t i = 0; i < vec.size(); i++)
    {
        std::cout << vec[i] << " ";
    }

    size_t max_iterations = find_max_iterations(vec.size());

    for (size_t level = max_iterations; level > 0; level--)
    {
        size_t groupSize = 1 << (level);
        std::cout << "Jacobsthal Level " << level << ", Group Size: " << groupSize << std::endl;

        generatePairsVec(level);

        std::vector<int> vec = insertJacobsthal(smalls, bigs);
    }

    vec = insertJacobsthal(bigs, smalls);

    std::cout << "Sorted vector: ";
    for (size_t i = 0; i < vec.size(); i++)
    {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Vector comparisons: " << _comparisons << std::endl;
    _comparisons = 0;
}
