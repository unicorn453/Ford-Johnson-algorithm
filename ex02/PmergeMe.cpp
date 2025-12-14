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
        size_t next = j1 + 2 * j0;
        if (next > n)
            break;
        jac.push_back(next);
        j0 = j1;
        j1 = next;
    }

    return jac;
}

void PmergeMe::insertJacobsthal(size_t sizePairs)
{

    size_t numPairs = smalls.size();
    std::vector<size_t> jac = generateJacobsthal(numPairs / 2);

    size_t vec_size = vec.size();
    size_t maxBlocks = vec_size / sizePairs;

    if (maxBlocks <= 2)
        return;

    std::vector<int> mainChain = bigs;

    std::vector<int> insertSmalls;
    insertSmalls.reserve(sizePairs);
    for (size_t i = 0; i < sizePairs && i < smalls.size(); ++i)
    {
        insertSmalls.push_back(smalls[i]);
    }
    for (size_t i = 0; i < sizePairs && !smalls.empty(); ++i)
    {
        smalls.erase(smalls.begin());
    }

    mainChain.insert(mainChain.begin(), insertSmalls.begin(), insertSmalls.end());

    insertSmalls.clear();
    insertSmalls.reserve(sizePairs);
    for (size_t i = 0; i < sizePairs && i < smalls.size(); ++i)
    {
        insertSmalls.push_back(smalls[i]);
    }
    for (size_t i = 0; i < sizePairs && !smalls.empty(); ++i)
    {
        smalls.erase(smalls.begin());
    }

    if (!insertSmalls.empty())
    {
        size_t val = insertSmalls[insertSmalls.size() - 1];
        size_t insertPos = 0;

        for (size_t i = 1; i < maxBlocks + 1; ++i)
        {
            size_t right = mainChain[(i * sizePairs) - 1];
            if (right > val)
            {
                insertPos = (i * sizePairs) - sizePairs;
                break;
            }
        }
        mainChain.insert(mainChain.begin() + insertPos, insertSmalls.begin(), insertSmalls.end());
        // remove them from small
        insertSmalls.clear();
    }

    std::vector<bool> inserted(numPairs, false);
    inserted[0] = true;

    for (size_t i = 1; i < jac.size() && jac[i] <= numPairs; ++i)
    {
        size_t jacobIndex = jac[i] - 1;
        size_t prevJacob = jac[i - 1] - 1;

        for (size_t k = jacobIndex; k > prevJacob && k < inserted.size(); k--)
        {
            if (!inserted[k])
            {

                size_t remaining_blocks = smalls.size() / sizePairs;
                if (k >= remaining_blocks)
                {
                    continue;
                }

                insertSmalls.clear();
                size_t start_idx = k * sizePairs;

                for (size_t s = 0; s < sizePairs && (start_idx + s) < smalls.size(); ++s)
                {
                    insertSmalls.push_back(smalls[start_idx + s]);
                }

                for (size_t i = 0; i < insertSmalls.size(); i++)
                    std::cout << insertSmalls[i] << " ";
                std::cout << std::endl;

                if (start_idx < smalls.size())
                {
                    size_t elements_to_remove = std::min(sizePairs, smalls.size() - start_idx);
                    smalls.erase(smalls.begin() + start_idx, smalls.begin() + start_idx + elements_to_remove);
                }

                if (!insertSmalls.empty())
                {
                    int val = insertSmalls[0];
                    size_t left = 0;
                    size_t right = mainChain.size();

                    while (left < right)
                    {
                        size_t mid = (left + right) / 2;
                        _comparisons++;
                        if (mainChain[mid] < val)
                            left = mid + 1;
                        else
                            right = mid;
                    }

                    mainChain.insert(mainChain.begin() + left, insertSmalls.begin(), insertSmalls.end());
                    inserted[k] = true;
                }
            }
        }
    }

    for (size_t i = 0; i < numPairs; ++i)
    {
        if (!inserted[i])
        {
            int val = smalls[i];
            size_t left = 0;
            size_t right = mainChain.size();

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
            inserted[i] = true;
        }
    }

    vec = mainChain;
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
    }

    vec.clear();
    for (size_t i = 0; i < smalls.size(); i++)
    {
        vec.push_back(smalls[i]);
        vec.push_back(bigs[i]);
    }
}

void PmergeMe::generatePairsVec(size_t pairSize)
{

    bigs.clear();
    smalls.clear();
    pend.clear();

    size_t size = vec.size();
    size_t blockSize = pairSize * 2;
    size_t maxBlockElements = (size / blockSize) * blockSize; // Total elements that can form complete blocks
    size_t pendsCount = size - maxBlockElements;

    for (size_t i = 0; i < maxBlockElements; i += blockSize)
    {

        std::vector<int> block1(vec.begin() + i, vec.begin() + i + pairSize);
        std::vector<int> block2(vec.begin() + i + pairSize, vec.begin() + i + blockSize);

        int max1 = *std::max_element(block1.begin(), block1.end());
        int max2 = *std::max_element(block2.begin(), block2.end());

        if (max1 <= max2)
        {
            for (size_t s = 0; s < pairSize; s++)
                smalls.push_back(block1[s]);
            for (size_t b = 0; b < pairSize; b++)
                bigs.push_back(block2[b]);
        }
        else
        {
            for (size_t s = 0; s < pairSize; s++)
                smalls.push_back(block2[s]);
            for (size_t b = 0; b < pairSize; b++)
                bigs.push_back(block1[b]);
        }
    }

    if (pendsCount > 0)
    {
        for (size_t i = maxBlockElements; i < size; i++)
        {
            pend.push_back(vec[i]);
        }
    }
}

void PmergeMe::vectorSort()
{
    if (vec.size() <= 1)
        return;

    mergeSortVec();

    size_t max_pair_size = find_max_iterations(vec.size());
    max_pair_size = max_pair_size - 1;

    for (size_t level = max_pair_size; level > 0; level--)
    {
        generatePairsVec(pow(2, level));
        insertJacobsthal(pow(2, level));
    }

    std::cout << "Vector sorted with " << _comparisons << " comparisons." << std::endl;
    std::cout << "Sorted vector: ";
    for (size_t i = 0; i < vec.size(); i++)
    {
        std::cout << vec[i] << " ";
    }
}
