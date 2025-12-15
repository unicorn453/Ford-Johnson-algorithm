#include "PmergeMe.hpp"
#include <algorithm>

size_t PmergeMe::binaryCompareDeq(int value, size_t a, size_t b, const std::deque<int>& container)
{
    while (a < b)
    {
        size_t mid = a + (b - a) / 2;

        ++_comparisonsDeq;
        if (container[mid] < value)
            a = mid + 1;
        else
            b = mid;
    }
    return a;
}

size_t find_max_iterations_deq(size_t size)
{

    size_t iterations = 0;
    while (size > 1)
    {
        size = size / 2;
        iterations++;
    }
    return iterations;
}

std::deque<size_t> generateJacobsthalDeq(size_t n)
{
    std::deque<size_t> jac;

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

void PmergeMe::insertJacobsthalDeq(size_t sizePairs)
{
    size_t originalNumPairs = smallsDeq.size() / sizePairs;
    std::deque<size_t> jac = generateJacobsthalDeq(originalNumPairs);

    size_t deq_size = deq.size();
    size_t maxBlocks = deq_size / sizePairs;

    if (maxBlocks <= 2)
        return;

    std::deque<int> mainChain = bigsDeq;

    std::deque<int> insertSmalls;
    for (size_t i = 0; i < sizePairs && i < smallsDeq.size(); ++i)
    {
        insertSmalls.push_back(smallsDeq[i]);
    }
    for (size_t i = 0; i < sizePairs && !smallsDeq.empty(); ++i)
    {
        smallsDeq.erase(smallsDeq.begin());
    }

    mainChain.insert(mainChain.begin(), insertSmalls.begin(), insertSmalls.end());

    insertSmalls.clear();

    for (size_t i = 0; i < sizePairs && i < smallsDeq.size(); ++i)
    {
        insertSmalls.push_back(smallsDeq[i]);
    }

    for (size_t i = 0; i < sizePairs && !smallsDeq.empty(); ++i)
    {
        smallsDeq.erase(smallsDeq.begin());
    }

    if (!insertSmalls.empty())
    {
        int val = insertSmalls[insertSmalls.size() - 1];
        size_t pos = binaryCompareDeq(val, 0, mainChain.size(), mainChain);

        mainChain.insert(mainChain.begin() + pos, insertSmalls.begin(), insertSmalls.end());

        insertSmalls.clear();
    }

    std::deque<bool> inserted(originalNumPairs, false);
    inserted[0] = true;

    for (size_t i = 1; i < jac.size() && jac[i] <= originalNumPairs; ++i)
    {
        size_t jacobIndex = jac[i] - 1;
        size_t prevJacob = jac[i - 1] - 1;

        for (size_t k = jacobIndex; k > prevJacob && k < inserted.size(); k--)
        {
            if (!inserted[k])
            {
                size_t remaining_blocks = smallsDeq.size() / sizePairs;
                if (k >= remaining_blocks)
                {
                    continue;
                }

                insertSmalls.clear();
                size_t start_idx = k * sizePairs;

                for (size_t s = 0; s < sizePairs && (start_idx + s) < smallsDeq.size(); ++s)
                {
                    insertSmalls.push_back(smallsDeq[start_idx + s]);
                }

                if (start_idx < smallsDeq.size())
                {
                    size_t elements_to_remove = std::min(sizePairs, smallsDeq.size() - start_idx);
                    smallsDeq.erase(smallsDeq.begin() + start_idx, smallsDeq.begin() + start_idx + elements_to_remove);
                }

                if (!insertSmalls.empty())
                {
                    int val = insertSmalls[0];
                    size_t pos = binaryCompareDeq(val, 0, mainChain.size(), mainChain);

                    mainChain.insert(mainChain.begin() + pos, insertSmalls.begin(), insertSmalls.end());

                    inserted[k] = true;
                }
            }
        }
    }

    while (!smallsDeq.empty())
    {
        int val = smallsDeq[0];
        size_t pos = binaryCompareDeq(val, 0, mainChain.size(), mainChain);

        mainChain.insert(mainChain.begin() + pos, val);
        smallsDeq.erase(smallsDeq.begin());
    }

    std::deque<int> tempPend = pendDeq;
    deq = mainChain;
    deq.insert(deq.end(), tempPend.begin(), tempPend.end());
}
void PmergeMe::mergeSortDeq()
{
    size_t size = deq.size();
    size_t pends = size % 2;
    size_t maxPairsElements = size - pends;

    for (size_t i = 0; i < maxPairsElements; i += 2)
    {
        if (deq[i] > deq[i + 1])
            std::swap(deq[i], deq[i + 1]);
    }

    bigsDeq.clear();
    smallsDeq.clear();
    pendDeq.clear();
    pairMaxDeq.clear();

    for (size_t i = 0; i < maxPairsElements; i += 2)
    {
        smallsDeq.push_back(deq[i]);
        bigsDeq.push_back(deq[i + 1]);
    }

    size_t numPairs = bigsDeq.size();
    size_t max_iterations = find_max_iterations_deq(numPairs);

    for (size_t level = 0; level < max_iterations; level++)
    {
        size_t block = 1 << level;

        for (size_t i = 0; i + 2 * block <= numPairs; i += 2 * block)
        {
            size_t L = i;
            size_t R = i + block;

            _comparisonsDeq++;
            if (bigsDeq[L + block - 1] > bigsDeq[R + block - 1])
            {
                for (size_t i = L; i < R; i++)
                {
                    std::swap(smallsDeq[i], smallsDeq[i + (R - L)]);
                    std::swap(bigsDeq[i], bigsDeq[i + (R - L)]);
                }
            }
        }
    }

    deq.clear();
    for (size_t i = 0; i < smallsDeq.size(); i++)
    {
        deq.push_back(smallsDeq[i]);
        deq.push_back(bigsDeq[i]);
    }
}


void PmergeMe::generatePairsDeq(size_t pairSize)
{
    bigsDeq.clear();
    smallsDeq.clear();
    pendDeq.clear();
    pairMaxDeq.clear();

    size_t mainChainSize = deq.size() - pendDeq.size();
    size_t blockSize = pairSize * 2;
    size_t maxBlockElements = (mainChainSize / blockSize) * blockSize;

    for (size_t i = 0; i < maxBlockElements; i += blockSize)
    {
        std::deque<int> block1(deq.begin() + i, deq.begin() + i + pairSize);
        std::deque<int> block2(deq.begin() + i + pairSize, deq.begin() + i + blockSize);

        int max1 = *std::max_element(block1.begin(), block1.end());
        int max2 = *std::max_element(block2.begin(), block2.end());

        if (max1 <= max2)
        {
            for (size_t s = 0; s < pairSize; s++)
                smallsDeq.push_back(block1[s]);
            for (size_t b = 0; b < pairSize; b++)
                bigsDeq.push_back(block2[b]);
        }
        else
        {
            for (size_t s = 0; s < pairSize; s++)
                smallsDeq.push_back(block2[s]);
            for (size_t b = 0; b < pairSize; b++)
                bigsDeq.push_back(block1[b]);
        }
    }

    for (size_t i = maxBlockElements; i < mainChainSize; i++)
    {
        pendDeq.push_back(deq[i]);
        if (i >= pairSize && (i - pairSize) / (pairSize * 2) * (pairSize * 2) + pairSize <= i)
        {
            size_t blockIndex = i / (pairSize * 2);
            if (blockIndex < bigsDeq.size() / pairSize)
            {
                pairMaxDeq.push_back(bigsDeq[blockIndex * pairSize + (pairSize - 1)]);
            }
            else
            {
                pairMaxDeq.push_back(INT_MAX);
            }
        }
        else
        {
            pairMaxDeq.push_back(INT_MAX);
        }
    }
}


void PmergeMe::rearrangeBlocksByLastElementDeq(size_t pairSize)
{
    if (deq.size() < pairSize * 2)
        return;

    size_t mainChainSize = deq.size() - pendDeq.size();
    size_t numCompleteBlocks = mainChainSize / pairSize;

    std::deque<std::pair<int, size_t> > blockInfo;
    for (size_t i = 0; i < numCompleteBlocks; i++)
    {
        size_t lastElementIdx = (i + 1) * pairSize - 1;
        if (lastElementIdx < mainChainSize)
        {
            int lastElement = deq[lastElementIdx];
            blockInfo.push_back(std::make_pair(lastElement, i));
        }
    }

    std::sort(blockInfo.begin(), blockInfo.end());

    std::deque<int> tempDeq;

    for (size_t i = 0; i < blockInfo.size(); i++)
    {
        size_t blockIdx = blockInfo[i].second;
        size_t startIdx = blockIdx * pairSize;

        for (size_t j = 0; j < pairSize && (startIdx + j) < mainChainSize; j++)
        {
            tempDeq.push_back(deq[startIdx + j]);
        }
    }

    size_t remainingStart = numCompleteBlocks * pairSize;
    if (remainingStart < mainChainSize)
    {
        for (size_t i = remainingStart; i < mainChainSize; i++)
        {
            tempDeq.push_back(deq[i]);
        }
    }

    for (size_t i = 0; i < pendDeq.size(); i++)
    {
        tempDeq.push_back(pendDeq[i]);
    }

    deq = tempDeq;
}

size_t PmergeMe::findPairedPositionDeq(size_t pendIndex)
{
    int pairedValue = pairMaxDeq[pendIndex];

    return std::lower_bound(
               deq.begin(),
               deq.end(),
               pairedValue) -
           deq.begin();
}

void PmergeMe::sortRemainingElementsDeq(int valueOdd)
{
    if (pendDeq.empty() && valueOdd == -1)
        return;

    std::deque<size_t> jac = generateJacobsthalDeq(pendDeq.size());

    size_t sortedSize = deq.size() - pendDeq.size();
    deq.resize(sortedSize);

    if (valueOdd != -1)
    {
        size_t pos = binaryCompareDeq(valueOdd, 0, deq.size(), deq);
        deq.insert(deq.begin() + pos, valueOdd);
    }

    if (pendDeq.empty())
        return;

    std::deque<bool> inserted(pendDeq.size(), false);

    {
        size_t upper = findPairedPositionDeq(0);
        size_t pos = binaryCompareDeq(pendDeq[0], 0, std::min(upper, deq.size()), deq);
        deq.insert(deq.begin() + pos, pendDeq[0]);
        inserted[0] = true;
    }

    for (size_t j = 1; j < jac.size(); ++j)
    {
        size_t start = jac[j - 1];
        size_t end   = jac[j];

        if (end > pendDeq.size())
            end = pendDeq.size();

        for (size_t i = end; i-- > start;)
        {
            if (inserted[i])
                continue;

            size_t upper = findPairedPositionDeq(i);
            size_t searchStart = 0;
            if (i > 0 && inserted[i-1]) {
                for (size_t k = 0; k < deq.size(); ++k) {
                    if (deq[k] == pendDeq[i-1]) {
                        searchStart = k + 1;
                        break;
                    }
                }
            }
            
            size_t pos = binaryCompareDeq(pendDeq[i], searchStart, std::min(upper, deq.size()), deq);
            deq.insert(deq.begin() + pos, pendDeq[i]);
            inserted[i] = true;
        }
    }

    for (size_t i = pendDeq.size(); i-- > 0;)
    {
        if (!inserted[i])
        {
            size_t upper = findPairedPositionDeq(i);
            size_t pos = binaryCompareDeq(pendDeq[i], 0, std::min(upper, deq.size()), deq);
            deq.insert(deq.begin() + pos, pendDeq[i]);
        }
    }
    
    pendDeq.clear();
}


void PmergeMe::dequeSort()
{
    if (deq.size() <= 1)
        return;

    size_t original_size = deq.size();
    bool has_odd = (original_size % 2 != 0);
    int last_element = -1;
     if (has_odd)
    {
        last_element = deq[original_size - 1];
        deq.pop_back();
    }
   
    mergeSortDeq();

    size_t max_pair_size = find_max_iterations_deq(deq.size());
    max_pair_size = max_pair_size - 1;

    for (size_t level = max_pair_size; level > 0; level--)
    {
        size_t pairSize = 1 << level;
        generatePairsDeq(pairSize);
        insertJacobsthalDeq(pairSize);
        rearrangeBlocksByLastElementDeq(pairSize);
    }

    generatePairsDeq(1);
    insertJacobsthalDeq(1);
    rearrangeBlocksByLastElementDeq(1);
    sortRemainingElementsDeq(last_element);
}