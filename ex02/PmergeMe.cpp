#include "PmergeMe.hpp"
#include <algorithm>

PmergeMe::PmergeMe() : _comparisons(0), _comparisonsDeq(0)
{
    bigs.clear();
    smalls.clear();
    pend.clear();
    pairMax.clear();
    bigsDeq.clear();
    smallsDeq.clear();
    pendDeq.clear();
    pairMaxDeq.clear();
}

PmergeMe::PmergeMe(std::string input) : _comparisons(0), _comparisonsDeq(0)
{
    bigs.clear();
    smalls.clear();
    pend.clear();
    pairMax.clear();
    bigsDeq.clear();
    smallsDeq.clear();
    pendDeq.clear();
    pairMaxDeq.clear();

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

PmergeMe::PmergeMe(const PmergeMe &other) : vec(other.vec), deq(other.deq), pend(other.pend), smalls(other.smalls), bigs(other.bigs), pendDeq(other.pendDeq), smallsDeq(other.smallsDeq), bigsDeq(other.bigsDeq), _comparisons(other._comparisons), _comparisonsDeq(other._comparisonsDeq), pairMax(other.pairMax), pairMaxDeq(other.pairMaxDeq) {}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        vec = other.vec;
        deq = other.deq;
        _comparisons = other._comparisons;
        _comparisonsDeq = other._comparisonsDeq;
        bigs = other.bigs;
        smalls = other.smalls;
        pend = other.pend;
        bigsDeq = other.bigsDeq;
        smallsDeq = other.smallsDeq;
        pendDeq = other.pendDeq;
        pairMax = other.pairMax;
        pairMaxDeq = other.pairMaxDeq;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}


size_t PmergeMe::binaryCompareVec(int value, size_t a, size_t b)
{
    while (a < b)
    {
        size_t mid = a + (b - a) / 2;

        ++_comparisons;
        if (vec[mid] < value)
            a = mid + 1;
        else
            b = mid;
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
    {
        return jac;
    }

    size_t j0 = 1;
    size_t j1 = 3;

    jac.push_back(1);

    if (n >= 2 && j1 <= n)
    {
        jac.push_back(j1);
    }

    while (true)
    {
        size_t next = j1 + 2 * j0;

        if (next > n)
        {
            break;
        }

        jac.push_back(next);

        j0 = j1;
        j1 = next;
    }

    return jac;
}

void PmergeMe::insertJacobsthalVec(size_t sizePairs)
{

    size_t originalNumPairs = smalls.size() / sizePairs;
    std::vector<size_t> jac = generateJacobsthal(originalNumPairs);

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
        int val = insertSmalls[insertSmalls.size() - 1];
        size_t pos = binaryCompareVec(val, 0, mainChain.size());

        mainChain.insert(mainChain.begin() + pos, insertSmalls.begin(), insertSmalls.end());

        insertSmalls.clear();
    }

    std::vector<bool> inserted(originalNumPairs, false);
    inserted[0] = true;

    for (size_t i = 1; i < jac.size() && jac[i] <= originalNumPairs; ++i)
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

                if (start_idx < smalls.size())
                {
                    size_t elements_to_remove = std::min(sizePairs, smalls.size() - start_idx);
                    smalls.erase(smalls.begin() + start_idx, smalls.begin() + start_idx + elements_to_remove);
                }

                if (!insertSmalls.empty())
                {
                    int val = insertSmalls[0];
                    size_t pos = binaryCompareVec(val, 0, mainChain.size());

                    mainChain.insert(mainChain.begin() + pos, insertSmalls.begin(), insertSmalls.end());

                    inserted[k] = true;
                }
            }
        }
    }

    while (!smalls.empty())
    {
        int val = smalls[0];
        size_t pos = binaryCompareVec(val, 0, mainChain.size());

        mainChain.insert(mainChain.begin() + pos, val);
        smalls.erase(smalls.begin());
    }

    std::vector<int> tempPend = pend;
    vec = mainChain;
    vec.insert(vec.end(), tempPend.begin(), tempPend.end());
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
    pairMax.clear();

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

            _comparisons++;
            if (bigs[L + block - 1] > bigs[R + block - 1])
            {
                for (size_t i = L; i < R; i++)
                {
                    std::swap(smalls[i], smalls[i + (R - L)]);
                    std::swap(bigs[i], bigs[i + (R - L)]);
                }
            }
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
    pairMax.clear();

    size_t mainChainSize = vec.size() - pend.size();
    size_t blockSize = pairSize * 2;
    size_t maxBlockElements = (mainChainSize / blockSize) * blockSize;

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

    for (size_t i = maxBlockElements; i < mainChainSize; i++)
    {
        pend.push_back(vec[i]);
        if (i >= pairSize && (i - pairSize) / (pairSize * 2) * (pairSize * 2) + pairSize <= i)
        {
            size_t blockIndex = i / (pairSize * 2);
            if (blockIndex < bigs.size() / pairSize)
            {
                pairMax.push_back(bigs[blockIndex * pairSize + (pairSize - 1)]);
            }
            else
            {
                pairMax.push_back(INT_MAX);
            }
        }
        else
        {
            pairMax.push_back(INT_MAX);
        }
    }
}

void PmergeMe::rearrangeBlocksByLastElementVec(size_t pairSize)
{
    if (vec.size() < pairSize * 2)
        return;

    size_t mainChainSize = vec.size() - pend.size();
    size_t numCompleteBlocks = mainChainSize / pairSize;

    std::vector<std::pair<int, size_t> > blockInfo;
    for (size_t i = 0; i < numCompleteBlocks; i++)
    {
        size_t lastElementIdx = (i + 1) * pairSize - 1;
        if (lastElementIdx < mainChainSize)
        {
            int lastElement = vec[lastElementIdx];
            blockInfo.push_back(std::make_pair(lastElement, i));
        }
    }

    std::sort(blockInfo.begin(), blockInfo.end());

    std::vector<int> tempVec;
    tempVec.reserve(vec.size());

    for (size_t i = 0; i < blockInfo.size(); i++)
    {
        size_t blockIdx = blockInfo[i].second;
        size_t startIdx = blockIdx * pairSize;

        for (size_t j = 0; j < pairSize && (startIdx + j) < mainChainSize; j++)
        {
            tempVec.push_back(vec[startIdx + j]);
        }
    }

    size_t remainingStart = numCompleteBlocks * pairSize;
    if (remainingStart < mainChainSize)
    {
        for (size_t i = remainingStart; i < mainChainSize; i++)
        {
            tempVec.push_back(vec[i]);
        }
    }

    for (size_t i = 0; i < pend.size(); i++)
    {
        tempVec.push_back(pend[i]);
    }

    vec = tempVec;
}

size_t PmergeMe::findPairedPositionVec(size_t pendIndex)
{
    int pairedValue = pairMax[pendIndex];

    return std::lower_bound(
               vec.begin(),
               vec.end(),
               pairedValue) -
           vec.begin();
}

void PmergeMe::sortRemainingElementsVec(int valueOdd)
{
    if (pend.empty() && valueOdd == -1)
        return;

    std::vector<size_t> jac = generateJacobsthal(pend.size());

    size_t sortedSize = vec.size() - pend.size();
    vec.resize(sortedSize);

    if (valueOdd != -1)
    {
        size_t pos = binaryCompareVec(valueOdd, 0, vec.size());
        vec.insert(vec.begin() + pos, valueOdd);
    }

    if (pend.empty())
        return;

    std::vector<bool> inserted(pend.size(), false);

    {
        size_t upper = findPairedPositionVec(0);
        size_t pos = binaryCompareVec(pend[0], 0, std::min(upper, vec.size()));
        vec.insert(vec.begin() + pos, pend[0]);
        inserted[0] = true;
    }

    for (size_t j = 1; j < jac.size(); ++j)
    {
        size_t start = jac[j - 1];
        size_t end   = jac[j];

        if (end > pend.size())
            end = pend.size();

        for (size_t i = end; i-- > start;)
        {
            if (inserted[i])
                continue;

            size_t upper = findPairedPositionVec(i);
            size_t searchStart = 0;
            if (i > 0 && inserted[i-1]) {
                for (size_t k = 0; k < vec.size(); ++k) {
                    if (vec[k] == pend[i-1]) {
                        searchStart = k + 1;
                        break;
                    }
                }
            }
            size_t pos = binaryCompareVec(pend[i], searchStart, std::min(upper, vec.size()));

            vec.insert(vec.begin() + pos, pend[i]);
            inserted[i] = true;
        }
    }

    for (size_t i = pend.size(); i-- > 0;)
    {
        if (!inserted[i])
        {
            size_t upper = findPairedPositionVec(i);
            size_t pos = binaryCompareVec(pend[i], 0, std::min(upper, vec.size()));
            vec.insert(vec.begin() + pos, pend[i]);
        }
    }
    pend.clear();
}


void PmergeMe::vectorSort()
{
    if (vec.size() <= 1)
        return;

    size_t original_size = vec.size();
    bool has_odd = (original_size % 2 != 0);
    int last_element = -1;
    if (has_odd)
    {
        last_element = vec[original_size - 1];
        vec.pop_back();
    }
    mergeSortVec();

    size_t max_pair_size = find_max_iterations(vec.size());
    max_pair_size = max_pair_size - 1;

    for (size_t level = max_pair_size; level > 0; level--)
    {
        size_t pairSize = 1 << level;
        generatePairsVec(pairSize);
        insertJacobsthalVec(pairSize);
        rearrangeBlocksByLastElementVec(pairSize);
    }

    generatePairsVec(1);
    insertJacobsthalVec(1);
    rearrangeBlocksByLastElementVec(1);
    sortRemainingElementsVec(last_element);
}